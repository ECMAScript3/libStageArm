#include "hack.h"

void* createUsers(void* completion) {

  return 0;
};



void spawnThreads(int threadCount, int accountCount) {
  pthread_t* threads[threadCount];
  for (int i=0;i<threadCount;i++) {
    unsigned char* p = malloc(sizeof(unsigned char));
    pthread_create(threads[i], NULL, createUsers, (void*)(p));
  }
};
