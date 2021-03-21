////
//// Created by leviinba@wincs.cs.bgu.ac.il on 11/01/2020.
////
#include <string>
#include <iostream>

#include "Inventory.h"
#include "connectionHandler.h"
#include "ProtocolImpl.h"
#include "User.h"
#include "ReadFromKeyboard.h"
#include <thread>

using namespace std;


int main(int argc, char *argv[]) {

    Inventory inventory = Inventory();

    bool running = true;
    string host;
    string port;
    vector<string> newVec;

    while (running) {

        const short bufsize = 1024;

        char buf[bufsize];

        cin.getline(buf, bufsize);

        string line(buf);

        newVec = inventory.splitString(line, ' ');

        if(newVec.at(0) == "login"){
            vector<string> v = inventory.splitString(newVec.at(1), ':');
            host = v.at(0);
            port = v.at(1);
            running = false;
        }
    }


    int po = stoi(port);
    short t = po;
    ConnectionHandler connectionHandler(host, t);
    User u = User();

    ReadFromKeyBoard readFromKeyBoard(connectionHandler, u, inventory, newVec);
    ProtocolImpl stompBookClubClient1(inventory, u, connectionHandler);

    if(u.isOnline()){
        std::thread threadsocket(&ProtocolImpl::run, stompBookClubClient1);
        std::thread threadKeyBoard(&ReadFromKeyBoard::run, readFromKeyBoard);
        threadKeyBoard.join();
        threadsocket.join();
    }




    return 0;



}

