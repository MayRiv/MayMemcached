/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeThread.hpp
 * Author: i.maydanovskiy
 *
 * Created on 25 мая 2017 г., 12:05
 */

#ifndef TIMETHREAD_HPP
#define TIMETHREAD_HPP
#include "thread.hpp"
#include "socket.hpp"
class TimeThread:public lb::Thread {
public:
    TimeThread();
    TimeThread(const TimeThread& orig);
    virtual ~TimeThread();
protected:
    virtual void run();

};

#endif /* TIMETHREAD_HPP */