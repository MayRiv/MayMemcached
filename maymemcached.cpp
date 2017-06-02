/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   maymemcached.cpp
 * Author: i.Maydanovskiy
 *
 * Created on 24 мая 2017 г., 10:43
 */

#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "socket.hpp"
#include "WebThreadManager.hpp"
#include "TimeThread.hpp"
#include "MemCachedStorage.hpp"
#include "MmapRepository.hpp"
using namespace std;

/*
 * 
 */

void signalHandler(int signo)
{
    MemCachedStorage::Instance().logToFile();
}
void initSignals(){
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = signalHandler;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGUSR1); 
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, 0);
}
int main(int argc, char** argv) {

    MmapRepository rep("storage.bin");
    MemCachedStorage::Instance().Init(&rep);
    lb::SocketClient server;
    server.InitServer(4000, "127.0.0.1");
    WebThreadManager manager;
    for (int i = 0; i < 10; i++)
    {
		manager.NewTask(&server);
                printf("Task launched\n");
    }
    TimeThread timeThread;
    
    initSignals();
    while(1)
        sleep(1);
    
    
}