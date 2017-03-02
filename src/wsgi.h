#ifndef WSGI_H
#define WSGI_H

#include "utils.h"
#include "errors.h"
#include "handle.h"
#include <string>
#include <thread>
#include <memory>
#include <vector>
#include <exception>

class WSGI
{
public:
  WSGI();
  ~WSGI();

  bool build();
  void start();
  void cleanup();
  void handleExit(UWebSock<UServer>, int, std::string);

private:
  JSON conf;
  int ncores;
  bool debug;
  bool isClosed = false;
  void load();
  UHub mainThread;
  std::vector<std::shared_ptr<UHub>> connPool;
};

/* Constructor */
WSGI::WSGI()
{
  debug = true; // false = less prints
  load();       // on creation, load data
}

/* Destructor */
WSGI::~WSGI()
{
  cleanup();
}

/* Handle program exit */
void WSGI::cleanup()
{
  if (isClosed) return;
  Log("\n[*] Cleaning up program...");
  connPool.clear();
  isClosed = true;
}

/* Preload any data necessary */
void WSGI::load()
{
  if (debug)
    Log("[*] Reading config file...");
  conf.Parse(readFile("config.json").c_str());
}

bool WSGI::build()
{
  try
  {
    // decide how many threads to spawn based on num of cores
    ncores = (signed int)std::thread::hardware_concurrency();
    if (debug)
      Log("[*] Spawning", ncores, "threads");

    for (int i = 0; i < ncores; i++)
    {
      // create a thread to handle the clients
      new std::thread([&, i]()
      {
        // create threaded server
        std::shared_ptr<UHub> hub(new UHub());

        // bind threaded server actions
        hub->onDisconnection([&, i]
        (UWebSock<UServer> ws, int code, char *reason, size_t len){
          if (debug)
            Log("[*] Client exit on thread", i);
          handleExit(ws, code, std::string(reason, len));
        });
        hub->onMessage([&, i]
        (UWebSock<UServer> ws, char *msg, size_t len, UOpCode op){
          WSPacket packet = {ws, std::string(), op};
          if (!len || len == 0)
            return DataNullError(packet);
          try {
            packet.content = std::string(msg, len);
            if (debug)
              Log("[*] Message on thread", i, packet.content);
            handlePacket(packet);
          } catch (std::exception &ex) {
            ExceptionError(packet, ex);
          }
        });

        // start threaded server
        hub->getDefaultGroup<UServer>().addAsync();
        connPool.push_back(hub);
        hub->run();
      });
    }

    // bind main thread connect and port
    mainThread.onConnection([&](UWebSock<UServer> ws, UHttpReq req)
    {
      int t = rand() % ncores;
      if (debug)
        Log("[*] Routing connection to thread", t);
      ws.transfer(&connPool[t]->getDefaultGroup<UServer>());
    });
    mainThread.getDefaultGroup<UServer>().addAsync();
    if (!conf.HasMember("port")) {
      Log("[x] No port binding found in config.json!");
      return false;
    }
    mainThread.listen(conf["port"].GetInt());
    return true;

  // catch and handle any errors
  } catch (...) {
    Log("[x] Unknown Error creating threads!");
  }
  return false;
}

/* Start and run the server */
void WSGI::start()
{
  Log("[*] Server starting 0.0.0.0 on port", conf["port"].GetInt());
  mainThread.run();
}

/* Handle clients disconnecting */
void WSGI::handleExit
(UWebSock<UServer> ws, int code, std::string reason)
{

}

#endif