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
using namespace std;
map<string, std::unique_ptr<StoredValue> > StoredValue::storedValues;
StoredValue::StoredValue(string value, int secondsExpires) {
    _value = value;
    if (secondsExpires > 0)
    {
        expiresTime =  std::chrono::system_clock::now() + std::chrono::seconds(secondsExpires);
        eternal = false;
    }
    else eternal = true;
}

/*StoredValue::StoredValue(const StoredValue& orig) {
}*/

StoredValue::~StoredValue() {
}

