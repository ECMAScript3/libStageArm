#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <atomic>
#include <unistd.h>
#include "hack.h"
#include "window.h"









int main(int argc, char* argv[]) {
  // a.out #threads #accounts_per_thread username password

  if (argc == 5) {
    //spawnThreads(atoi(argv[1]), atoi(argv[2]));
  } else {
    beginGUI();
  }
  return 0;
};
