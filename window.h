#include "hack.h"
#include <ncurses.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <atomic>
#include <sys/socket.h>
#include <stdatomic.h>
#include <unistd.h>
#pragma once
using namespace std;
string genCmd;
void beginGUI();
void takeInput();