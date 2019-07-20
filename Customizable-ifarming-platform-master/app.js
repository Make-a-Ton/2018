const net = require("net");

let server = net.createServer(socket=>{
    console.log("inside the server");
    console.log("socket: ", socket);
    socket.write('Echo server\r\n');
    socket.pipe(socket);
});

server.listen(4000, '0.0.0.0');
