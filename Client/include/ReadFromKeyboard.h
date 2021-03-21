//
// Created by leviinba@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef ASSIGNMENT3_READFROMKEYBOARD_H
#define ASSIGNMENT3_READFROMKEYBOARD_H

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "connectionHandler.h"
#include "ProtocolImpl.h"

using namespace std;

class ReadFromKeyBoard {
public:
    ReadFromKeyBoard(ConnectionHandler &connectionHandler, User &u,Inventory &inv, vector<string> s);
    ~ReadFromKeyBoard();
    ReadFromKeyBoard(const ReadFromKeyBoard& re);
    ReadFromKeyBoard& operator=(const ReadFromKeyBoard& re);

    void processOut(vector<string> s);
    void run();

    string static transformConnectTostring(Connect fr);

    string static transformSubscribeTostring(Subscribe fr);

    string static transformUnsubscribeTostring(Unsubscribe fr);

    string static transformDisconnectTostring(Disconnect fr);

    string static transformSendTostring(Send fr);

private:
    vector<string> static splitString(string s, char c);
    ConnectionHandler *_connectionHandler;
    User *IAM;
    string name;
    Inventory *inventory;
    int countSubId;
    int countRec;
    bool running;
    vector<string> start;

};


#endif //ASSIGNMENT3_READFROMKEYBOARD_H
