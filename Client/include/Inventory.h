//
// Created by leviinba@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3_INVENTORY_H
#define ASSIGNMENT3_INVENTORY_H
#include <string>
#include <map>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include "Book.h"
#include "User.h"

using namespace std;

class Inventory {
public:
    Inventory();

    void addSubsMap(string name, string topic, int sub);
    void addRecMap(string name, int rec, string command);
    map<string, map<string,int>> getSUbMap();
    map<string, map<int,string>> getRecMap();

    void insertBook(string topic, Book toInsert);
    void startTopic(string topic, string name);
    void addKeeper(string topic , string user,  Book toinsert);
    void removeKeeper(string topic, string user, string bookname);
    vector<Book> getVectorBook(string topic);
    vector<Book> getVecByName(string topic, string name);
    void eraseBook(string owner, string topic, string bookname);
    void addUser(string name, User* u);
    map<string, vector<Book>> getAllBook();
    void addBookTop(string topic, Book b);
    void eraseSub(string user, string des);
    map<string,int> getSubMap(string name);
    map<int,string> getspeRec(string name);
    map<int,string> getReciptIdMap(string user);

    map <string,int> getMySubscriptions(string user);
    map<pair<string,string>, vector<Book>> getKeepersMap();
    void updateMySubscriptions(string user, string topic, int sub);

    void updateReceiptIdMap (string user, int id, string task);

    void addHist(string s, string k);
    string getPrev(string book);
    void eraseBook(string s);

    map<string,vector<string>> getHistory();

    vector<string> static splitString(string s, char c);



private:
    map<string, vector<Book>> allBooksInTopic;
    map<pair<string,string>, vector<Book>> bookKeepers;
    map<string,  User*> UserMap;
    map<string, map<string,int>> mapMySubscriptions;
    map<string, map<int,string>> receiptIdMap;
    map<string, vector<string>>history;



};


#endif //ASSIGNMENT3_INVENTORY_H
