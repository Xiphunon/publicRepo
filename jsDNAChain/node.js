var http = require("http");
var url = require('url');
var fs = require('fs');

var server = http.createServer(function(request, response) {
    var path = url.parse(request.url).pathname;
    switch (path) {
        case "/":
            fs.readFile(__dirname + "/index.html", function(error, data) {
                if (error) {
                    response.writeHead(404);
                    response.write(error);
                    response.end();
                } else {
                    response.writeHead(200, {
                        'Content-Type': 'text/html'
                    });
                    response.write(data);
                    response.end();
                }
            });
            break;
        case "/style.css":
            fs.readFile(__dirname + '/style.css', function(error, data) {
                if (error) {
                    response.writeHead(404);
                    response.write(error);
                    response.end();
                } else {
                    response.writeHead(200, {
                        'Content-Type': 'text/css'
                    });
                    response.write(data);
                    response.end();
                }

            });
            break;
        case "/main.js":
            fs.readFile(__dirname + '/main.js', function(error, data) {
                if (error) {
                    response.writeHead(404);
                    response.write(error);
                    response.end();
                } else {
                    response.writeHead(200, {
                        'Content-Type': 'text/javascript'
                    });
                    response.write(data);
                    response.end();
                }

            });
            break;
        default:
            response.writeHead(404);
            response.write("opps this doesn't exist - 404");
            response.end();
            break;
    }

});

server.listen(8080);