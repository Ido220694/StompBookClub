//
// Created by leviinba@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef ASSIGNMENT3_STOMPBOOKCLUBCLIENT_H
#define ASSIGNMENT3_STOMPBOOKCLUBCLIENT_H

#include "Frame.h"
#include "Inventory.h"
#include "connectionHandler.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


class ProtocolImpl {
public:
    ProtocolImpl(Inventory &inv, User &u, ConnectionHandler &handler);
    ProtocolImpl(const ProtocolImpl& pt);
    ProtocolImpl& operator=(const ProtocolImpl& pt);
    void run();
    void processIn(string str);
    static string transformSendTostring(Send fr);

    static vector<string> splitString(string s, char c);

private:

    string name;
    ConnectionHandler *handler;
    Inventory *inventory;
    string wishToBorrow;
    User *IAM;
    bool running;
};


#endif //ASSIGNMENT3_STOMPBOOKCLUBCLIENT_H
