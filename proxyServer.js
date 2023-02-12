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
    columnFirst = 25,
    columnSecond = 25;
var serverIndex = 0;

var CONFIG = {
    "URL": "PROXY/",
    "SECRET": "cb1cc77a-bbd1-48af-a6a7-5f969e62058b",
    "SERVER_LISTEN": {
        "0":{
            "ip": "127.0.0.1",
            "port": 12001
        },
        "1":{
            "ip": "192.168.0.11",
            "port": 10001,
            "key": "./key.pem",
            "cert": "./cert.pem"
        }
    }
};
const WebSocketServer = require('ws').Server;
const net = require('net');
const fs = require('fs')
const httpsMessage = (req, res)=>{
    res.setHeader('Content-Type',"text/html");
    let path = `fake/${req.url}${req.url.endsWith('/')?'index.html':''}`;
    if(!fs.existsSync(path)){
        path = "fake/404.html"
    }
    fs.readFile(path,(err,data)=>{
        res.end(data);
    })
}
for(let Listen in CONFIG.SERVER_LISTEN){
    
var https;
if(Object.keys(CONFIG.SERVER_LISTEN[Listen]).indexOf("key")!=Object.keys(CONFIG.SERVER_LISTEN[Listen]).indexOf("cert")){
    https = require('https').createServer({
        key: fs.readFileSync(CONFIG.SERVER_LISTEN[Listen].key),
        cert: fs.readFileSync(CONFIG.SERVER_LISTEN[Listen].cert),
    },httpsMessage).listen(CONFIG.SERVER_LISTEN[Listen].port, CONFIG.SERVER_LISTEN[Listen].ip);
}
else{
    https = require('http').createServer(httpsMessage).listen(CONFIG.SERVER_LISTEN[Listen].port, CONFIG.SERVER_LISTEN[Listen].ip);
}

const wss = new WebSocketServer({
    server: https
});
console.log(`${`${CONFIG.SERVER_LISTEN[Listen].ip}:${CONFIG.SERVER_LISTEN[Listen].port}`.padEnd(columnFirst)}is listening!`)

wss.on('connection', (ws, req) => {
    var clientSECRET = req.url.split(`/${CONFIG.URL}`)[1];
    var remotes = {}
    ws.on('message', (data) => {
        if (clientSECRET != CONFIG.SECRET || !data) {
            console.log(`AUTH ERROR`)
            return;
        }
        let remotePort;
        let remoteAddr;
        switch (data[VERSION]) {
            case SOCKS5:
                switch (data[COMMAND]) {
                    case CONNECT:
                        let clientIndexBuf = data.slice(-2);
                        let clientIndexNum = clientIndexBuf.readUInt16BE();
                        data = data.slice(0, -2)
                        switch (data[ADDRESS_TYPE]) {
                            case IPV4:
                                remoteAddr = data.slice(3, 7).join('.');
                                break;
                            case DOMAIN_NAME:
                                let domain_len = data[DOMAIN_LEN];
                                remoteAddr = data.slice(5, 5 + domain_len).toString("binary");
                                break;
                            case IPV6:
                                ws.send(Buffer.concat([Buffer.from([0x05, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), Buffer.from([0, 0])]));
                                //不支持 IPV6
                                break;
                            default:
                                return;
                        }
                        remotePort = data.readUInt16BE(data.length - 2)
                        remotes[clientIndexNum] = net.connect(remotePort, remoteAddr, function () {
                            console.log(`${`${CONFIG.SERVER_LISTEN[Listen].ip}:${CONFIG.SERVER_LISTEN[Listen].port}`.padEnd(columnFirst)}${remoteAddr}:${remotePort}`);
                            ws.send(Buffer.concat([Buffer.from([0x05, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), clientIndexBuf]));
                        });
                        remotes[clientIndexNum].on('data', (data) => {
                            ws.send(Buffer.concat([Buffer.from([INDEX]), clientIndexBuf, data]));
                        })
                        remotes[clientIndexNum].on('error', () => { });
                        break;
                    case BIND:
                        break;
                    case UDP:
                        break;
                    default:
                        return;
                }
                break;
            case INDEX:
                let clientIndexNum = data.slice(1, 3).readUInt16BE();
                try {
                    remotes[clientIndexNum].write(data.slice(3));
                }
                catch {
                    ws.send(Buffer.concat([Buffer.from([0x05, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]), Buffer.from([0, 0])]));
                }
                break;
        }
    });
    ws.on('error', () => { })
})
}