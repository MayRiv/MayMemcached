/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MmapRepository.hpp
 * Author: i.maydanovskiy
 *
 * Created on 26 мая 2017 г., 14:24
 */

#ifndef MMAPREPOSITORY_HPP
#define MMAPREPOSITORY_HPP
#include "IRepository.hpp"
class MmapRepository: public IRepository {
public:
    MmapRepository(string file);
    MmapRepository(const MmapRepository& orig) = delete;
    MmapRepository(const MmapRepository&& orig) = delete;
    MmapRepository& operator= (MmapRepository const&) = delete;
    MmapRepository& operator= (MmapRepository const&&) = delete;
    bool sync(map<string, std::unique_ptr<StoredValue> >& storedValues);
    bool load(map<string, std::unique_ptr<StoredValue> >& storedValues);
    virtual ~MmapRepository();
private:
    unsigned char* data;
    size_t size;
    int fd;
};

#endif /* MMAPREPOSITORY_HPP */

