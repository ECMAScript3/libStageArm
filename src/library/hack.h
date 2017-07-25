#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdatomic.h>
#include <unistd.h>
#pragma once
void* createUsers(void* completion);
void spawnThreads(int threadCount, int accountCount);
