var net = require('net');

var clients = [];

Array.prototype.remove = function(e) {
  for (var i = 0; i < this.length; i++) {
    if (e == this[i]) { return this.splice(i, 1); }
  }
};


var netServer = net.createServer(function (stream) {
  stream.setTimeout(0);
  stream.setEncoding("utf8");
  console.log("New Client online\n");
  clients.push(stream);
  
  stream.addListener("data", function (data) {
      clients.forEach(function(c) {
        try {
		console.log ("one");
                if (c != stream) {
			c.write(data)			
		}
        }
        catch(error) {
                console.log("Error: "+error);log("Error: "+error);
        }
     });

      console.log("Data: " + data);
  });

  stream.addListener("end", function() {
    console.log("client is disconnected");
    clients.remove(stream);
    stream.end();
  });

});

netServer.listen(1338);

