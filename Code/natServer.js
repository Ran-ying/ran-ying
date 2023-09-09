let serverConfig = {
    "secret":"cb1cc77a-bbd1-48af-a6a7-5f969e62058b",
    "IP":"127.0.0.1",
    "PORT":6000
}
var IP = serverConfig.IP;
var PORT = serverConfig.PORT;
var ws = require('ws').Server;
var server = new ws({
    ip: IP,
    port: PORT
})
var listens = {}
var listenTCP = {}
var ReqIndex = 0;
var ReqArr = {}
server.on('connection', (ws, req) => {
    var url = req.url.split('/');
    var clientSECRET = url[1];
    if(clientSECRET != serverConfig.secret) return;
    if(url.length == 2){
        console.log(`client ${clientSECRET} connect!`)
        ws.on('message',(data)=>{
            for(let i in listenTCP[clientSECRET]){
                listenTCP[clientSECRET][i].close();
            }
            listenTCP[clientSECRET] = {}
            listens[clientSECRET] = JSON.parse(data.toString())
            if(!ReqArr[clientSECRET]) ReqArr[clientSECRET] = {}
            for(let i in listens[clientSECRET]){
                listenTCP[clientSECRET][i] = require("net").createServer(con =>{
                    var index = ReqIndex++;
                    ReqArr[clientSECRET][index] = con;
                    var indexBuf = Buffer.alloc(4);
                    indexBuf.writeUInt32BE(index);
                    con.on('data',(data)=>{
                        listens[clientSECRET][i]["ws"].send(Buffer.concat([indexBuf, data]) );
                    })
                }).listen(listens[clientSECRET][i]["remotePort"], IP, ()=>{
                    console.log(`${IP}:${listens[clientSECRET][i]["remotePort"]} is listening!`)
                })
            }
        })
        ws.on('close',()=>{
        })
    }
    else{
        var i = url[2];
        listens[clientSECRET][i]["ws"] = ws;
        ws.on('message',(data)=>{
            let index = data.readInt32BE();
            //if(ReqArr[clientSECRET][ReqIndex])
                ReqArr[clientSECRET][index].write(data.subarray(4))
        })
    }
});
server.on('close',()=>{

})