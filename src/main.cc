#include "utils.h"
#include "system/wsgi.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// global variables
WSGI *server = nullptr;

// prototype declare cleanup function
void cleanup(int s);

// main function to run all services of server
int main(int argc, char *argv[])
{
  // initialize and create services
  InitUtils();
  server = new WSGI();
  if (!server->build()) return 1;

  // handle exit events
  struct sigaction sighandler;
  sighandler.sa_handler = cleanup;
  sigemptyset(&sighandler.sa_mask);
  sighandler.sa_flags = 0;
  sigaction(SIGINT, &sighandler, NULL);

  // start/run services
  server->start();
  return 0;
}

// external, main cleanup function
void cleanup(int s)
{
  server->cleanup();
  exit(1);
}