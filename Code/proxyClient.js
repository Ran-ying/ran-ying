const
    VERSION = 0,
    COMMAND = 1,
    RSV = 2,
    ADDRESS_TYPE = 3,
    DOMAIN_LEN = 4,
    METHODS_COUNT = 1,
    METHODS = 2;
const
    SOCKS5 = 0x05,
    INDEX = 0x00,
    NO_AUTH = 0x00,
    NO_ACCEPT = 0xFF,
    CONNECT = 0x01,
    BIND = 0x02,
    UDP = 0x03,
    IPV4 = 0x01,
    DOMAIN_NAME = 0x03,
    IPV6 = 0x04;
const
    columnFirst = 15,
    columnSecond = 25;
let clientConfig = {
    "unsafeSSL": true,
    "SERVERS": {
        "Ying": {
            "URL": "PROXY/",
            "SECRET": "97442cd1-9532-4566-8901-416d6d2b549b",
            "SERVER": "ws://127.0.0.1/"
        }
    },
    "CLIENT_LISTEN": {
        "localhost": {
            "PORT": 7000,
            "HOST": "127.0.0.1"
        }
    }
}
const rules = {
    "Ying": [
        "twitter.com",
        "twimg.com",
        "t.co"
    ]
}

var SERVERS = clientConfig.SERVERS;
var CLIENT_LISTEN = clientConfig.CLIENT_LISTEN;
var FindProxyForURL = require('./pac.js').FindProxyForURL;
const server = require('net');
const net = require('net');
const ws = require("ws");
const fs = require('fs');
if (clientConfig.unsafeSSL)
    process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;

var index = 0;

var serversWS = {}
var serversWStryconnect = {}
var socks5con = {}

const newWSConnect = (serverName) => {
    if (!serversWStryconnect[serverName]) serversWStryconnect[serverName] = 0;
    serversWS[serverName] = new ws(`${SERVERS[serverName].SERVER}${SERVERS[serverName].URL}${SERVERS[serverName].SECRET}`);
    serversWS[serverName].on('open', () => {
        console.log(`${serverName.padEnd(columnFirst)}${SERVERS[serverName].SERVER.padEnd(columnSecond)}is connected!`);
        serversWStryconnect[serverName] = 0;
    })
    serversWS[serverName].on('error', (error) => {
        console.log(`${serverName} Error: ${error}`);
    })
    serversWS[serverName].on('close', () => {
        console.log(`${serverName} close`)
        if (serversWStryconnect[serverName] < 10)
            setTimeout(() => {
                console.log(`${serverName} ${serversWStryconnect[serverName]++} reconnecting...`)
                newWSConnect(serverName);
            }, 1000 * Math.pow(serversWStryconnect[serverName], 2))
        else {
            console.log(`${serverName} cannot connect!`);
        }
    })
    serversWS[serverName].on('message', (data) => {
        let indexBuf, indexNum;
        switch (data[VERSION]) {
            case SOCKS5:
                indexBuf = data.subarray(-2);
                indexNum = indexBuf.readUInt16BE();
                //console.log("RECEIVE INDEX: "+message.slice(-2).readUInt16BE());
                socks5con[indexNum].write(data.subarray(0, -2));
                break;
            case INDEX:
                indexBuf = data.subarray(1, 3)
                indexNum = indexBuf.readUInt16BE();
                socks5con[indexNum].write(data.subarray(3));
                break;
        }
    })
}
for (let serverName in SERVERS) {
    newWSConnect(serverName)
}
for (let listen in CLIENT_LISTEN) {
    server.createServer((con) => {
        con.once('data', (data) => {
            if (!data || data[VERSION] != SOCKS5) {
                console.log("NO SOCKS5");
                return;
            }
            let METHODS_ENABLE = false;
            for (let i = METHODS; i < METHODS + data[METHODS_COUNT]; i++) {
                if (data[i] == NO_AUTH) {
                    i = METHODS + data[METHODS_COUNT];
                    METHODS_ENABLE = true;
                    con.write(Buffer.from([SOCKS5, NO_AUTH]), () => {
                        con.once('data', (data, req) => {
                            if (data[VERSION] != SOCKS5) {
                                console.log("NO SOCKS5");
                                return;
                            }
                            switch (data[COMMAND]) {
                                case CONNECT:
                                    let remotePort = data.readUInt16BE(data.length - 2);
                                    let remoteAddr;
                                    switch (data[ADDRESS_TYPE]) {
                                        case IPV4:
                                            remoteAddr = data.subarray(3, 7).join('.');
                                            break;
                                        case DOMAIN_NAME:
                                            let domain_len = data[DOMAIN_LEN];
                                            remoteAddr = data.subarray(5, 5 + domain_len).toString("binary");
                                            break;
                                        case IPV6:
                                            for (let i = 3; i < 3 + 16; i += 2)
                                                remoteAddr += data[i].toString() + data[i + 1].toString() + ":";
                                            remoteAddr = remoteAddr.subarray(0, -1);
                                            break;
                                        default:
                                            return;
                                    }
                                    let serverName = FindProxyForURL(remoteAddr, remotePort);
                                    let indexBuf = Buffer.alloc(2);
                                    let indexNum = index++ % 65535;
                                    indexBuf.writeUint16BE(indexNum);
                                    if (serverName != "DIRECT") {
                                        socks5con[indexNum] = con;
                                        data = Buffer.concat([data, indexBuf])
                                        if (!serversWS[serverName]) {
                                            console.log(`${serverName} error: cannot connect\t${remoteAddr}:${remotePort}`);
                                            con.write(Buffer.from([0x05, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]));
                                            return;
                                        }
                                        else {
                                            var send = () => {
                                                if (serversWS[serverName].readyState != ws.OPEN) {
                                                    setTimeout(() => {
                                                        send();
                                                    }, 1000);
                                                    return;
                                                };
                                                serversWS[serverName].send(data);
                                                con.on('data', (data) => {
                                                    serversWS[serverName].send(Buffer.concat([Buffer.from([INDEX]), indexBuf, data]));
                                                })
                                                console.log(`${serverName.padEnd(columnFirst)}${`${con.remoteAddress}:${con.remotePort}`.padEnd(columnSecond)}${remoteAddr}:${remotePort}`);
                                            }
                                            send();
                                        }
                                    }
                                    else {
                                        let remote = net.connect(remotePort, remoteAddr, () => {
                                            con.write(Buffer.from([0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), () => {
                                                console.log(`${`DIRECT`.padEnd(columnFirst)}${`${con.remoteAddress}:${con.remotePort}`.padEnd(columnSecond)}${remoteAddr}:${remotePort}`);
                                                con.on('data', (data) => {
                                                    remote.write(data);
                                                })
                                                remote.on('data', (data) => {
                                                    con.write(data);
                                                })
                                            });
                                        });
                                        remote.on('error', () => { });
                                    };
                                case UDP:
                                    break;
                                case BIND:
                                    break;
                                default:
                                    return;
                            }
                        })
                    })
                }
            };
            if (!METHODS_ENABLE) {
                con.write(Buffer.from([SOCKS5, NO_ACCEPT]));
            }
        })
        con.on('error', () => { })
    }).listen(CLIENT_LISTEN[listen]["PORT"], CLIENT_LISTEN[listen]["HOST"]).on('listening', () => {
        console.log(`${listen.padEnd(columnFirst)}${`${CLIENT_LISTEN[listen]["HOST"]}:${CLIENT_LISTEN[listen]["PORT"]}`.padEnd(columnSecond)}is listening!`);
    });
};

let FindProxyForURL = (url, host) => {
    for (let serverName in SERVERS) {
        for (let host in rules[serverName]) {
            if (url.endsWith(rules[serverName][host])) {
                return serverName;
            }
        }
    }
    return "DIRECT";
}