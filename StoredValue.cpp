/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoredValue.cpp
 * Author: mayriv
 * 
 * Created on 24 мая 2017 г., 17:29
 */

#include "StoredValue.hpp"
#include <map>
#include <memory>
#include <iostream>
#include <ctime>
using namespace std;
map<string, std::unique_ptr<StoredValue> > StoredValue::storedValues;
StoredValue::StoredValue(string value, int secondsExpires) {
    _value = value;
    if (secondsExpires > 0)
    {
        auto now = std::chrono::system_clock::now();
        expiresTime =  now  + std::chrono::seconds(secondsExpires);
        eternal = false;
        std::time_t t = chrono::system_clock::to_time_t(expiresTime);
        std::cout << "expires " << std::ctime(&t) << std::endl;
        
        std::time_t t2 = chrono::system_clock::to_time_t(now);
        std::cout << "now " << std::ctime(&t2) << std::endl;
    }
    else eternal = true;
}

/*StoredValue::StoredValue(const StoredValue& orig) {
}*/

StoredValue::~StoredValue() {
}

