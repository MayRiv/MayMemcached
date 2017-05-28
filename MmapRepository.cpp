/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MmapRepository.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 26 мая 2017 г., 14:24
 */

#include "MmapRepository.hpp"
#include <functional>
#include <numeric>

#include <cstdlib>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fstream>
#include <memory>
#include <algorithm>
#include <unistd.h>

#include <errno.h>
#include <string.h>
using namespace std;
MmapRepository::MmapRepository(string file):IRepository() {
    const char* c = file.c_str();
    int fd = open(file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        cout << "ERROR: " <<  strerror(errno) << endl;
        close(fd);
        throw true;
    }
    struct stat st;
    if(fstat(fd, &st) < 0) {
        cout << "ERROR fstat: " <<  strerror(errno) << endl;
        close(fd);
        throw true;
    }
    size = (size_t)st.st_size;
    if (!size)
        size = 1024;/* * 1024;*/
    ftruncate(fd, size);
    /*if (ftruncate(fd, size) == -1)
    {
        cout << "ERROR ftruncate: " <<  strerror(errno) << endl;
        close(fd);
        throw true;
    }*/
    data = (unsigned char*)mmap(0, size, PROT_READ | PROT_WRITE,
                                              MAP_SHARED, fd, 0);
    if(data == MAP_FAILED) {
        close(fd);
        cout << "ERROR mmap: " <<  strerror(errno) << endl;
        throw true;
    }
}


MmapRepository::~MmapRepository() {
    munmap(data, size);
    close(fd);
}

bool MmapRepository::sync(map<string, std::unique_ptr<StoredValue> >& storedValues)
{
    auto neededSize = std::accumulate(storedValues.begin(), storedValues.end(), 0, [](int value, map<string, std::unique_ptr<StoredValue> >::value_type& t)
    {
        return value + t.first.length() + 1 + t.second->getValue().length() + 1  + sizeof(chrono::time_point<chrono::system_clock>) + sizeof(bool);
    });
    cout << "Size is  " << neededSize << endl;
    if (neededSize < size)
    {
        //ftrunct shit
    }
    size_t offset = 0;
    auto temp_data = data;
    for(auto& it: storedValues)
    {  
        //it.first.copy(data+offset,it.first.length(),0);
        memcpy(temp_data, (unsigned char*) it.first.c_str(),it.first.length());
        temp_data[it.first.length()] = 0;
        temp_data += it.first.length() + 1;
        //it.second->getValue().copy(data+offset,it.second->getValue().length(),0);
        memcpy(temp_data, (unsigned char*) it.second->getValue().c_str(),it.second->getValue().length());
        //*(temp_data + it.second->getValue().length()) = 0;
        temp_data[it.second->getValue().length()] = 0;
        temp_data += it.second->getValue().length() + 1;
        //memcpy(temp_data, it.second->getExpiresTime(),sizeof(chrono::time_point<chrono::system_clock>));
        //temp_data += sizeof(chrono::time_point<chrono::system_clock>);
        unsigned int epoch = it.second->getExpiresTime().time_since_epoch().count();
        //memcpy(temp_data, &epoch, sizeof(unsigned int));
        *(temp_data) = epoch;
        temp_data += sizeof(unsigned int);
        //memcpy(temp_data, (unsigned char*)it.second->isEternal(), sizeof(bool));
        *(temp_data ) = it.second->isEternal();
        temp_data += sizeof(bool);
    }
    return true;
}
bool MmapRepository::load(map<string, std::unique_ptr<StoredValue> >& storedValues)
{
    size_t offset = 0;
    auto temp_data = data;
    while(/*offset*/ (temp_data - data) <= size)
    {
        
        char* key_s= (char*)(temp_data);
        string key;
        key.assign(key_s);
        temp_data += key.length() + 1;
        //string value(const char*(temp_data));
        string value;
        value.assign((char*)(temp_data));
        temp_data += value.length() + 1;
        //chrono::time_point<chrono::system_clock> time =  st;atic_cast<chrono::time_point<chrono::system_clock> >*(temp_data);
        //temp_data += sizeof(chrono::time_point<chrono::system_clock>);
        //unsigned int epoch = *(data offset);
        //chrono::time_point<chrono::system_clock> time(epoch);
        //memcpy(&time, temp_data, sizeof(chrono::time_point<chrono::system_clock>));
        unsigned int epoch = *temp_data;
        //chrono::time_point<chrono::system_clock> time(epoch);
        chrono::time_point<chrono::system_clock> time = std::chrono::system_clock::from_time_t(epoch);
        //temp_data += sizeof(unsigned int);
        //temp_data += sizeof(chrono::time_point<chrono::system_clock>);
        temp_data += sizeof(unsigned int);
        bool isEternal = (*temp_data);
        temp_data += sizeof(bool);
            
        storedValues.insert(std::make_pair(key, unique_ptr<StoredValue>(new StoredValue(value, time, isEternal))));
    }
    
    
    cout << "Ready" << endl;
}