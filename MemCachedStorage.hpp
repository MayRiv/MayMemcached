/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemCachedStorage.hpp
 * Author: i.maydanovskiy
 *
 * Created on 26 мая 2017 г., 13:03
 */

#ifndef MEMCACHEDSTORAGE_HPP
#define MEMCACHEDSTORAGE_HPP
#include <map>
#include "StoredValue.hpp"
#include <memory>
#include <string>
#include "IRepository.hpp"
class MemCachedStorage {
public:
    static MemCachedStorage& Instance()
    {
        static MemCachedStorage s;
        return s;
    }
    bool Init(IRepository* repository)
    {
        this->repository = repository;
    }
    virtual ~MemCachedStorage();
    map<string, std::unique_ptr<StoredValue> > storedValues;
    
    MemCachedStorage(MemCachedStorage const&) = delete;
    MemCachedStorage& operator= (MemCachedStorage const&) = delete;
    mutex storedValuesMutex;
    bool sync(map<string, std::unique_ptr<StoredValue> >& storedValues)
    {
        if (repository)
            return repository->sync(storedValues);
        return false;
    }
private:
    MemCachedStorage();
    IRepository* repository;
};

#endif /* MEMCACHEDSTORAGE_HPP */

