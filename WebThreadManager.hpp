/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebThreadManager.hpp
 * Author: i.maydanovskiy
 *
 * Created on 17 марта 2017 г., 13:35
 */

#ifndef WEBTHREADMANAGER_HPP
#define WEBTHREADMANAGER_HPP
#include "threadman.hpp"
#include "socket.hpp"
using namespace lb;
class WebThreadManager:public ThreadManager {
public:
    WebThreadManager();    
    void AddWaitThread()
    {
        LockData();
    }
    void RemWaitThread()
    {
        UnLockData();
    }
    virtual ~WebThreadManager();
    void NewTask(class lb::SocketClient *client);

};

#endif /* WEBTHREADMANAGER_HPP */

