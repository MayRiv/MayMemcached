/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Protocol.hpp
 * Author: mayriv
 *
 * Created on 24 мая 2017 г., 16:34
 */

#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include <string>
using namespace std;
class Protocol {
public:
    static bool processCmd(string cmd, string& output);
private:
    Protocol();
    Protocol(const Protocol& orig);
    virtual ~Protocol();

};

#endif /* PROTOCOL_HPP */

