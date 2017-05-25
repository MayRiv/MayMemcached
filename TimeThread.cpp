/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeThread.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 25 мая 2017 г., 12:05
 */

#include "TimeThread.hpp"
#include <chrono>
#include <ctime>
#include <unistd.h>
#include "StoredValue.hpp"
#include <iostream>
using namespace std;
TimeThread::TimeThread() {
    SetDetachState();
    if (int ret = Create())
    {
        //LOG PANIC
    }
}

TimeThread::TimeThread(const TimeThread& orig) {
}

TimeThread::~TimeThread() {
}

void TimeThread::run()
{
    const int PULSE_TIME = 1;
    cout << "TimeThread started" <<endl;
    while(1)
    {
        
        
        sleep(PULSE_TIME * 60);
        chrono::time_point<chrono::system_clock> now = std::chrono::system_clock::now();
        sleep(1);
        chrono::time_point<chrono::system_clock> now2 = std::chrono::system_clock::now();

        
        for(auto it = StoredValue::storedValues.begin(); it != StoredValue::storedValues.end(); ) {
            if (!it->second->isEternal() && it->second->getExpiresTime() < now) {
                cout << "VALUE " << it->second->getValue();
                std::time_t t = chrono::system_clock::to_time_t(it->second->getExpiresTime());
                std::cout << "expires " << std::ctime(&t) << std::endl;
                
                std::time_t t2 = chrono::system_clock::to_time_t(now);
                std::cout << "now " << std::ctime(&t2) << std::endl;
                it = StoredValue::storedValues.erase(it);
                cout << "ERASED WAHAHA" <<endl;
            } else {
                ++it;
            }
        }
    }
}