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
MemCachedStorage::MemCachedStorage() {
    repository = 0;
}



MemCachedStorage::~MemCachedStorage() {
}



