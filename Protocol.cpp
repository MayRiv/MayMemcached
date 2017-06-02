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
#include <mutex>
#include "MemCachedStorage.hpp"
#include <iostream>
using namespace std;
Protocol::Protocol() {
}

Protocol::Protocol(const Protocol& orig) {
}

Protocol::~Protocol() {
}
void removeSubstrs(string& s, string p) { 
  string::size_type n = p.length();
  for (string::size_type i = s.find(p);
      i != string::npos;
      i = s.find(p))
      s.erase(i, n);
}
bool parse(string cmd, vector<string>& out)
{
    bool line = false;
    vector<string> res;
    string word;
    for(auto ch = cmd.begin(); ch != cmd.end(); ch++){
        if (*ch == ' ' && !line)
        {
            res.push_back(word);
            word.clear();
        }
        else if (*ch == '"')
        {
            line = !line;
        }
        else
        {
            word.push_back(*ch);
        }
    }
    res.push_back(word);
    out=res;
    return !line;
}
bool Protocol::processCmd(string cmd,  string& output)
{
    lock_guard<std::mutex> lock(MemCachedStorage::Instance().storedValuesMutex);
    removeSubstrs(cmd,string("\r\n"));
    vector<string> tokens;
    auto res = parse(cmd, tokens);
    if (!tokens[0].compare("quit"))
    {
        output = "OK\n";
        return false;
    }
    if (tokens.size() < 2 || !res)
    {
        output = "Bad syntax\n";    
        return false;
    }
    else if (!tokens[0].compare("get"))
    {
        auto it = MemCachedStorage::Instance().storedValues.find(tokens[1]);
        if (it == MemCachedStorage::Instance().storedValues.end())
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
        
        unsigned int expires = 0;
        if (tokens.size() > 3)
            expires = std::stol(tokens[3]);
        
        MemCachedStorage::Instance().storedValues.insert(std::make_pair(key, unique_ptr<StoredValue>(new StoredValue(value, expires))));
        output = "OK\n";
    }
    else if (!tokens[0].compare("delete"))
    {
        MemCachedStorage::Instance().Instance().storedValues.erase(tokens[1]);
        output = "OK\n";
    }
        
    return true;
}