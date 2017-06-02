/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoredValue.hpp
 * Author: mayriv
 *
 * Created on 24 мая 2017 г., 17:29
 */

#ifndef STOREDVALUE_HPP
#define STOREDVALUE_HPP
#include <memory>
#include <map>
#include <chrono>
#include <string>
#include <thread>
#include <mutex>
//#include <ctime>
using namespace std;
class StoredValue {
public:
    StoredValue(string value, unsigned int secondsExpires);
    StoredValue(string value, chrono::system_clock::time_point momentExpires, bool isEternal);
    StoredValue(const StoredValue& orig) = delete;
    StoredValue(const StoredValue&& orig) = delete;
    
    StoredValue& operator=(const StoredValue& ) = delete;
    StoredValue& operator=(const StoredValue&& ) = delete;

    virtual ~StoredValue();
    
    const string& getValue(){
        return _value;
    }
    bool isEternal(){
        return eternal;
    }
    const chrono::time_point<chrono::system_clock>& getExpiresTime(){
        return expiresTime;
    }
    
private:
    string _value;
    chrono::time_point<chrono::system_clock> expiresTime;
    bool eternal = false;
};

#endif /* STOREDVALUE_HPP */

