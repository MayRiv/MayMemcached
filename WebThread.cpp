/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebThread.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 17 марта 2017 г., 13:49
 */

#include "WebThread.hpp"
#include "WebThreadManager.hpp"
#include "socket.hpp"
#include <stdio.h>
#include "Protocol.hpp"
#include <string>
#include <iostream>
using namespace lb;
using namespace std;
WebThread::WebThread(WebThreadManager* mngr, SocketClient* serv) {
    this->mngr = mngr;
    this->serv = serv;
    SetDetachState();
    if (int ret = Create())
    {
        //LOG PANIC
    }
}

void WebThread::run()
{
    mngr->Add(this);
    const int WEB_BUF_SIZE=2000;
    char buf[WEB_BUF_SIZE]; //requests
    
    while(1)
    {
        mngr->AddWaitThread();
        SocketClient* client = serv->GetConnection();
        mngr->RemWaitThread();
        if (!client)
        {
            delete client;
            continue;
        }
        try
        {
            string output;
            
            bool isContinue = true;
            while (isContinue)
            {
                if (client->Read(buf,WEB_BUF_SIZE,0,10) <= 0)
                    throw true;
                isContinue = Protocol::processCmd(string(buf),output);
                if (client->Send(output.c_str(), output.length()) < 0)
                    throw true;
                    
                memset(buf,0,WEB_BUF_SIZE);
            }
            delete client;
            client = 0;
        }
        catch (...)
        {
            cout << "Exception" << endl;
            delete client;
            client = 0;
        }
    }
}