//
// Created by leviinba@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "Frame.h"
#include <string>

using namespace std;

Frame::Frame() {}




Frame::~Frame() {

}


// Connect

Connect::Connect() : host(), passcode(), login() {
}

void Connect::setLogin(string name) {
//    fields.insert(make_pair(login, name));
    login = name;
}

void Connect::setPasscode(string password) {
//    fields.insert(make_pair(passcode, password));

    passcode = password;
}

void Connect::setHost(string Host) {
//    fields.insert(make_pair(host,Host));

    host = Host;
}


string Connect::getHost() {
    return host;
}

string Connect::getpasscode() {
    return passcode;
}

string Connect::getlogin() {
    return login;
}

Connect::~Connect() {

}


// Connected

Connected::Connected():version(1.2) {}

Connected::~Connected() {

}




// Subscribe

Subscribe::Subscribe() : destination(), id(), receipt(){

}

void Subscribe::setId(int subId) {
//    char * intStr = itoa(subId);
//    string str = (string)subId;
//    fields.insert(make_pair(id, ));
//    fields.insert(make_pair(to_string(id),to_string(subId)));

    id = subId;
}

void Subscribe::setRecId(int RecId) {
//    fields.insert(make_pair(to_string(receipt),to_string(RecId)));

    receipt = RecId;
}

void Subscribe::setDestination(string dest) {
//    fields.insert(make_pair(destination, dest));
destination = dest;
}


string Subscribe::getDesti() {
    return destination;
}

int Subscribe::getId() {
    return id;
}

int Subscribe::getRec() {
    return receipt;
}

Subscribe::~Subscribe() {

}

// Unsubscribe


Unsubscribe::Unsubscribe() : id(), receipt(){

}

void Unsubscribe::setId(int id1) {
//    fields.insert(make_pair(to_string(id),to_string(id1)));
    id = id1;
}

void Unsubscribe::setRecId(int recId) {
//    fields.insert(make_pair(to_string(receipt),to_string(recId)));
    receipt = recId;
}


int Unsubscribe::getId() {
    return id;
}

int Unsubscribe::getRec() {
    return receipt;
}

Unsubscribe::~Unsubscribe() {

}

// Disconnect


Disconnect::Disconnect() : receipt() {

}

void Disconnect::setRecId(int RecId) {
//    fields.insert(make_pair(to_string(receipt),to_string(RecId)));
    receipt = RecId;
}


int Disconnect::getRec() {
    return receipt;
}

Disconnect::~Disconnect() {

}


// Message


Message::Message() : destination(), body(){

}


string Message::getDestination() {
    return destination;
}

string Message::getBody() {
    return body;
}


void Message::setBody(string bo) {
//    fields.insert(make_pair(body, bo));
    body= bo;
}

void Message::setDest(string desti) {
//    fields.insert(make_pair(destination, desti));
    destination = desti;
}

Message::~Message() {

}



// Send


Send::Send() : destination(), body() {

}

void Send::setDestination(string desti) {
//    fields.insert(make_pair(destination, desti));
    destination = desti;
}

void Send::setBody(string bo) {
//    fields.insert(make_pair(body, bo));

    body = bo;
}


string Send::getDesti() {
    return destination;
}

string Send::getBody() {
    return body;
}

Send::~Send() {

}

// Receipt


Receipt::Receipt() : receipt_id() {

}

int Receipt::getRecId() {
    return receipt_id;
}


void Receipt::setRec(int rec) {
//    fields.insert(make_pair(to_string(receipt_id), to_string(rec)));
    receipt_id = rec;
}

Receipt::~Receipt() {

}

Error::Error(): body() {

}


string Error::getBody() {
    return body;
}


void Error::setBody(string s) {
//    fields.insert(make_pair(body,s));
    body = s;
}

Error::~Error() {

}
