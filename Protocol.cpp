/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Protocol.cpp
 * Author: mayriv
 * 
 * Created on 24 мая 2017 г., 16:34
 */

#include "Protocol.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "StoredValue.hpp"
#include <utility>  
using namespace std;
Protocol::Protocol() {
}

Protocol::Protocol(const Protocol& orig) {
}

Protocol::~Protocol() {
}
vector<string> split(const string &s, char delim) {
  stringstream ss(s);
  
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(move(item));
  }
  return elems;
}
void removeSubstrs(string& s, string p) { 
  string::size_type n = p.length();
  for (string::size_type i = s.find(p);
      i != string::npos;
      i = s.find(p))
      s.erase(i, n);
}
bool Protocol::processCmd(string cmd,  string& output) /// TODO: CATCH EXCEPTION OF BAD SYNTAX, DONT BE LAZY
//                                                       MUTEXES
{
    removeSubstrs(cmd,string("\r\n"));   
    auto tokens = split(cmd, ' ');
    if (tokens.size() < 2)
    {
        output = "Bad syntax\n";
        return false;
    }
    if (!tokens[0].compare("get"))
    {
        auto it = StoredValue::storedValues.find(tokens[1]);
        if (it == StoredValue::storedValues.end())
        {
            output = "VALUE MISSED\n";
        }
        else
        {
            output = "VALUE " + it->second->getValue() + "\n";
        }
    }
    else if (!tokens[0].compare("set"))
    {
        
        if (tokens.size() < 3)
        {
            output = "Bad syntax\n";
            return false;
        }
        string key = tokens[1];
        string value = tokens[2];
        
        int expires = 0;
        if (tokens.size() > 3)
            expires = std::stoi(tokens[3]);
        
        //unique_ptr<StoredValue> p(new StoredValue(value, expires));
        //StoredValue::storedValues[key] = p;
        StoredValue::storedValues.insert(std::make_pair(key, unique_ptr<StoredValue>(new StoredValue(value, expires))));
        //int k =StoredValue::storedValues.size();
        output = "OK\n";
    }
    else if (!tokens[0].compare("delete"))
    {
        StoredValue::storedValues.erase(tokens[1]);
        output = "OK\n";
    }
        
    return true;
}