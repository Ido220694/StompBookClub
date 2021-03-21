//
// Created by leviinba@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3_FRAME_H
#define ASSIGNMENT3_FRAME_H
#include<string>
#include <iostream>
#include <map>

using namespace std;


class Frame {
public:
    Frame();
    ~Frame();
};

class Connect  : public Frame{
public:
    Connect();
    ~Connect();
    void setLogin(string name);
    void setPasscode(string passcode);
    void setHost(string host);
    string getHost();
    string getpasscode();
    string getlogin();

private:
    string host;
    string passcode;
    string login;
};

class Connected  : public Frame{
public:
    Connected();
    ~Connected();


private:
    double version;

};

class Subscribe  : public Frame{
public:
    Subscribe();
    ~Subscribe();
    void setId(int subId);
    void setRecId(int RecId);
    void setDestination(string dest);
    string getDesti();
    int getId();
    int getRec();



private:
    string destination;
    int id;
    int receipt;

};

class Unsubscribe  : public Frame{
public:
    Unsubscribe();
    ~Unsubscribe();
    void setId(int id1);
    void setRecId(int recId);
    int getId();
    int getRec();


private:
    int id;
    int receipt;

};

class Disconnect  : public Frame{
public:
    Disconnect();
    ~Disconnect();
    void setRecId(int RecId);
    int getRec();

private:
    int receipt;

};

class Message  : public Frame{
public:
    Message();
    ~Message();
    string getDestination();
    string getBody();
    void setBody(string body);
    void setDest(string destination);

private:
    string destination;
    string body;

};

class Send  : public Frame{
public:
    Send();
    ~Send();
    void setDestination(string desti);
    void setBody(string bo);
    string getDesti();
    string getBody();


private:
    string destination;
    string body;


};

class Receipt  : public Frame{
public:
    Receipt();
    ~Receipt();
    int getRecId();
    void setRec(int rec);
private:
    int receipt_id;

};

class Error : public Frame{
public:
    Error();
    ~Error();
    string getBody();
    void setBody(string s);

private:
    string body;
};









#endif //ASSIGNMENT3_FRAME_H
