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
    StoredValue(string value, int secondsExpires);
    StoredValue(const StoredValue& orig) = delete;
        StoredValue& operator=(const StoredValue& ) = delete;

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
    //static map<string, std::unique_ptr<StoredValue> > storedValues;
    //static mutex storedValuesMutex;
private:
    string _value;
    chrono::time_point<chrono::system_clock> expiresTime;
    bool eternal;
};

#endif /* STOREDVALUE_HPP */

