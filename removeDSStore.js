let fs = require('fs')
let path = '/Users/'
let deep = 8
let readdir = (path, n=0)=>{
    fs.readdir(path,(err, file)=>{
        if(!file || n > deep) return;
        file.forEach(val=>{
            fs.stat(path+val,(err, stats)=>{
                if(err) return;
                if(stats.isDirectory()){
                    readdir(path+val+'/', n+1)
                }
                else if(val == '.DS_Store'){
                    console.log(path+val)
                    fs.unlink(path+val,(err)=>{
                        if(err) console.log(err)
                    })
                }
            })
        })
    })
}
readdir(path)
