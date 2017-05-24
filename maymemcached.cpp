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
#include <unistd.h>
#include "socket.hpp"
#include "WebThreadManager.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    lb::SocketClient server;
    server.InitServer(4000, "192.168.0.31");
    WebThreadManager manager;
    for (int i = 0; i < 10; i++)
    {
		manager.NewTask(&server);
                printf("Task launched\n");
    }
    printf("All tasks launched\n");
    while(1)
        sleep(1);
}