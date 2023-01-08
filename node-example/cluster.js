import cluster from "cluster"; // Multiprocessing package
import http from "http";
import os from "os";

const port = 8888;
const processors = os.cpus();

if (cluster.isPrimary) {
  console.log(`Listening on port ${port}`);
  console.log(`Processor count: ${processors.length}`);

  // Fork un worker par processeur
  processors.forEach((processor) => cluster.fork());
  cluster.on("exit", (worker, code, signal) => cluster.fork()); // si un worker s'arrête, en créer un autre
} else {
  // Un serveur par processeur
  http
    .createServer((req, res) => {
      res.writeHead(200);
      res.end(`Echoeing request URI: " ${req.url} \n`);
    })
    .listen(port);
}
