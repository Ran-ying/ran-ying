let ws = require('ws');
let net = require('net')
let server;
let secret;
let listens;
let clientConfig = {
    "secret":"63ae26e2-cf73-4b72-8ed5-44c476105609",
    "server":"ws://127.0.0.1:6000/",
    "LISTENS":{
        "0":{
            "remotePort" : 10003,
            "clientIP": "127.0.0.1",
            "clientPort": 4000
        },
        "1":{
            "remotePort" : 10002,
            "clientIP": "127.0.0.1",
            "clientPort": 4000
        }
    }
}
const open = ()=>{
    server = clientConfig.server;
    secret = clientConfig.secret;
    listens = clientConfig.LISTENS
    let client = new ws(`${server}${secret}`);
    client.on('open',()=>{
        client.send(JSON.stringify(listens))
        for(let i in listens){
            connectServer(server, secret, i)
        }
    })
}
open();
let connectServer = (server, secret, index)=>{
    let url = `${server}${secret}/${index}`
    let connect = new ws(url);
    let ReqArr = {}
    connect.on('open',()=>{
        console.log(`${server} is opening!`)
    })
    connect.on('message',(data)=>{
        let ReqIndex = data.readInt32BE();
        let ReqBuf = data.subarray(0,4);
        if(!ReqArr[ReqIndex]){
            let local = net.connect(listens[index].clientPort, listens[index].clientIP, () => {
                local.on('data', (data) => {
                    connect.send(Buffer.concat([ReqBuf, data]));
                })
            });
            local.on('error', () => { });
            ReqArr[ReqIndex] = local
        }
        ReqArr[ReqIndex].write(data.subarray(4))
    })
    connect.on('close',()=>{
        console.log(`${server} is closed, reconnecting...`)
        connectServer(server, secret, index);
    })
}