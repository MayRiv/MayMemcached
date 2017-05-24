/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebThread.hpp
 * Author: i.maydanovskiy
 *
 * Created on 17 марта 2017 г., 13:49
 */

#ifndef WEBTHREAD_HPP
#define WEBTHREAD_HPP
#include "thread.hpp"
#include "socket.hpp"

class WebThread:public lb::Thread {
public:
    WebThread(class WebThreadManager* mngr, class lb::SocketClient* serv);
protected:
    class WebThreadManager *mngr;
    class lb::SocketClient* serv;
    virtual void run();
};

#endif /* WEBTHREAD_HPP */

