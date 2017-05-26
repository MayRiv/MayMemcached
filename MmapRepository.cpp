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
using namespace std;
MmapRepository::MmapRepository(string file):IRepository() {
    const char* c = file.c_str();
    int fd = open(file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if (fd < 0)
    {
        close(fd);
        throw true;
    }
    struct stat st;
    if(fstat(fd, &st) < 0) {
        close(fd);
        throw true;
    }
    size = (size_t)st.st_size;
    data = (unsigned char*)mmap(0, size, PROT_READ | PROT_WRITE,
                                              MAP_SHARED, fd, 0);
    if(data == MAP_FAILED) {
        close(fd);
        throw true;
    }
}


MmapRepository::~MmapRepository() {
    munmap(data, size);
    close(fd);
}

bool MmapRepository::sync(map<string, std::unique_ptr<StoredValue> >& storedValues)
{
    auto size = std::accumulate(storedValues.begin(), storedValues.end(), 0, [](int value, map<string, std::unique_ptr<StoredValue> >::value_type& t)
    {
        return value + t.first.length() + 1 + t.second->getValue().length() + 1  + sizeof(chrono::time_point<chrono::system_clock>) + sizeof(bool);
    });
    cout << "Size is  " << size << endl;
    for(auto& it: storedValues)
    {
        //std::copy(data,)
    }
    return true;
}