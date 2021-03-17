const fs = require("fs");
const exec = require("child_process").exec;
var express = require("express");
const body_parser = require("body-parser");

const app = express();
const port = process.env.PORT || 8000;

app.use(express.static(__dirname + '/public'));
app.use(body_parser.urlencoded());
app.use(body_parser.json());

app.listen(port, () => console.log(`Listening on port ${port}...`));

app.get('/', function(req, res) {
  res.sendFile(path.join(__dirname + '/public/index.html'));  // send index.html
});

app.post('/get_path', function(req, res) {
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
