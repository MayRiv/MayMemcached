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
#include <mutex>
using namespace std;
StoredValue::StoredValue(string value, unsigned int secondsExpires) {
    _value = value;
    if (secondsExpires > 0)
    {
        auto now = std::chrono::system_clock::now();
        expiresTime =  now  + std::chrono::seconds(secondsExpires);
        eternal = false;
    }
    else eternal = true;
}

StoredValue::StoredValue(string value, chrono::time_point<chrono::system_clock> momentExpires, bool isEternal) {
    _value = value;
    expiresTime =  momentExpires;
    eternal = isEternal;
}
/*StoredValue::StoredValue(const StoredValue& orig) {
}*/

StoredValue::~StoredValue() {
}

