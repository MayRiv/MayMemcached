/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemCachedStorage.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 26 мая 2017 г., 13:03
 */

#include "MemCachedStorage.hpp"
#include <mutex>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;
MemCachedStorage::MemCachedStorage() {
    repository = 0;
}



MemCachedStorage::~MemCachedStorage() {
}

bool MemCachedStorage::logToFile()
{
    try
    {
        lock_guard<std::mutex> lock(storedValuesMutex);
        ofstream out("/tmp/log.txt",fstream::out); 
        std::for_each(this->storedValues.begin(), this->storedValues.end(),[&out](map<string, std::unique_ptr<StoredValue> >::value_type &v)
        {
            out << v.first << " -> " << v.second->getValue() << endl;
        });
        out.close();
    }
    catch (...)
    {
        cout << "Can't write to /tmp/log.txt" << endl;
        return false;
    }
    return true;
}

