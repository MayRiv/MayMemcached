/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebThreadManager.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 17 марта 2017 г., 13:35
 */

#include "WebThreadManager.hpp"
#include "WebThread.hpp"
WebThreadManager::WebThreadManager() {
}


WebThreadManager::~WebThreadManager() {
}

void WebThreadManager::NewTask(class lb::SocketClient *client){
    new WebThread(this,client);
}