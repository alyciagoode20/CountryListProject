const fs = require("fs");
const exec = require("child_process").exec;
var express = require("express");
const body_parser = require("body-parser");
var cluster = require('cluster');
var cpus = require('os').cpus().length;  // get the number of available logical cpu cores.

if (cluster.isMaster) {
  for (var i = 0; i < cpus; i++) {
    cluster.fork();  // make a new process for each cpu.
  }

  cluster.on('online', function(worker) {
    console.log(worker.process.pid + "is online");
  });
  cluster.on("exit", function(worker, code, signal) {
    console.log("Worker" + worker.process.pid + " is dead");
  });

} else {
  var supervisor = require('supervisor');
  const app = express();
  const port = process.env.PORT || 8000;

  app.use(express.static(__dirname + '/public'));
  app.use(body_parser.urlencoded());
  app.use(body_parser.json());

  var server = app.listen(port, () => console.log(`Listening on port ${port}...`));

  app.get('/', function(req, res) {
    process.on('uncaughtException', function(err) {
      console.error(err);
      process.exit(1);
      server.close();  // stop taking requests.
      cluster.worker.disconnect();  // Tell master worker is dead and needs replacing.
      res.statusCode = 500;
      res.setHeader('content-type', 'text-plain');
      res.end("Sorry, there was a problem");
    });
    res.sendFile(path.join(__dirname + '/public/index.html'));  // send index.html
  });

  app.post('/get_path', function(req, res) {
    process.on('uncaughtException', function(err) {
      console.error(err);
      process.exit(1);
      server.close();  // stop taking requests.
      cluster.worker.disconnect();  // Tell master worker is dead and needs replacing.
      res.statusCode = 500;
      res.setHeader('content-type', 'text-plain');
      res.end("Sorry, there was a problem");
    });
    // console.log("REQUEST: " + req.body.name);
    const script = exec('./a.out');  // run a.out executable.

    script.stdin.setEncoding('utf-8');
    // script.stdout.pipe(process.stdout);  //

    script.stdin.write(req.body.name);  // write the Country Name from input to Dijkstra's

    script.stdin.end();  // Stop writing.

    // script.stdout.pipe(process.stdout);  // sends the child process output to terminal
    script.stdout.on('data', (data)=>{
        res.send(data);
    });
    script.stderr.on('data', (data)=>{
        console.error(data);
    });
  });
}
