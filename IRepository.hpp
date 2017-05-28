/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IRepository.hpp
 * Author: i.maydanovskiy
 *
 * Created on 26 мая 2017 г., 14:22
 */

#ifndef IREPOSITORY_HPP
#define IREPOSITORY_HPP
#include <string>
#include <memory>
#include "StoredValue.hpp"
class IRepository {
public:
    IRepository();
    IRepository(const IRepository& orig);
    virtual ~IRepository();
    virtual bool sync(map<string, std::unique_ptr<StoredValue> >& storedValues) = 0;
    virtual bool load(map<string, std::unique_ptr<StoredValue> >& storedValues) = 0;
private:

};

#endif /* IREPOSITORY_HPP */

