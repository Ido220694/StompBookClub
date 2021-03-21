//
// Created by leviinba@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "Inventory.h"
#include <string>
#include "Book.h"

#include <vector>
#include <sstream>
#include <mutex>

using namespace std;
std::mutex m2;

Inventory::Inventory(): allBooksInTopic(), bookKeepers(),UserMap(), mapMySubscriptions(), receiptIdMap(), history() {

}


void Inventory::insertBook(string topic, Book toInsert) {
    m2.lock();
    auto search = allBooksInTopic.find(topic);
    if (search == allBooksInTopic.end()) {
        vector<Book> newvec;
        newvec.push_back(toInsert);
        allBooksInTopic.insert(make_pair(topic, newvec));
    } else {
        vector<Book> tmp = allBooksInTopic.at(topic);
        tmp.push_back(toInsert);
        search->second = tmp;
    }
    m2.unlock();
}


void Inventory::addKeeper(string topic, string user, Book toinsert) {
    m2.lock();
    auto search = bookKeepers.find(make_pair(topic, user));
    if (search == bookKeepers.end()) {
        vector<Book> booklist;
        booklist.push_back(toinsert);
        bookKeepers.insert(make_pair(make_pair(topic, user), booklist));
    } else {
        vector<Book> tmp = bookKeepers.at(make_pair(topic, user));
        tmp.push_back(toinsert);
        search->second = tmp;
    }
    m2.unlock();
}


void Inventory::removeKeeper(string topic, string user, string bookname) {
    m2.lock();
    int j = bookKeepers.at(make_pair(topic, user)).size();
    for (int i = 0; i < j; ++i) {
        if (bookKeepers.at(make_pair(topic, user)).at(i).getBookName() == bookname) {
            bookKeepers.at(make_pair(topic, user)).erase(bookKeepers.at(make_pair(topic, user)).begin() + i);
        }
    }
    m2.unlock();
}

//Book Inventory::getBook(string topic, string Username, string bookName) {
//
//    Book tosend = Book(bookName);
//    vector<Book> tmp = bookKeepers.at(make_pair(topic, Username));
//    for (int i = 0; i < tmp.size(); i++) {
//        if (tmp.at(i).getBookName() == bookName) {
//            return tmp.at(i);
//        }
//    }
//    return tosend ;
//}


vector<Book> Inventory::getVectorBook(string topic) {
    return allBooksInTopic.at(topic);
}

vector<Book> Inventory::getVecByName(string topic, string name) {
    return bookKeepers.at(make_pair(topic, name));
}

//User *Inventory::getUser(string name) {
//    User *u = UserMap.at(name);
//    return u;
//}

void Inventory::eraseBook(string owner, string topic, string bookname) {
    m2.lock();
    bool deleted = false;
    int j = allBooksInTopic.at(topic).size();
    for (int i = 0; i < j && !deleted; ++i) {
        if (allBooksInTopic.at(topic).at(i).getBookName() == bookname && allBooksInTopic.at(topic).at(i).getOwner() == owner) {
            allBooksInTopic.at(topic).erase(allBooksInTopic.at(topic).begin() + i);
            deleted = true;
        }
    }
    m2.unlock();
}

void Inventory::addUser(string name, User *u) {
    m2.lock();
    UserMap.insert(make_pair(name, u));
    m2.unlock();
}

map<int, string> Inventory::getReciptIdMap(string user) {
    return receiptIdMap.at(user);
}

map<string, int> Inventory::getMySubscriptions(string user) {
    return mapMySubscriptions.at(user);
}

void Inventory::updateReceiptIdMap(string user, int id, string task) {
    m2.lock();
    receiptIdMap.at(user).insert(make_pair(id, task));
    m2.unlock();

}

void Inventory::updateMySubscriptions(string user, string topic, int sub) {
    m2.lock();
    mapMySubscriptions.at(user).insert(make_pair(topic, sub));
    m2.unlock();
}

map<string, map<string, int>> Inventory::getSUbMap() {
    return mapMySubscriptions;

}

map<string, map<int, string>> Inventory::getRecMap() {
    return receiptIdMap;
}

void Inventory::addSubsMap(string name, string topic, int sub) {
    m2.lock();
    map<string,int> s;
    s.insert(make_pair(topic,sub));
    mapMySubscriptions.insert(make_pair(name, s));
    m2.unlock();
}

void Inventory::addRecMap(string name, int rec, string command) {
    m2.lock();
    map<int,string> a;
    a.insert(make_pair(rec,command));
    receiptIdMap.insert(make_pair(name,a));
    m2.unlock();
}

map<string, vector<Book>> Inventory::getAllBook() {
    return allBooksInTopic;
}

void Inventory::addBookTop(string topic, Book b) {
    m2.lock();
    auto search = allBooksInTopic.find(topic);
    if (search == allBooksInTopic.end()) {
        vector<Book> booklist;
        booklist.push_back(b);
        allBooksInTopic.insert(make_pair(topic, booklist));
    } else {
        vector<Book> t = allBooksInTopic.at(topic);
        t.push_back(b);
        search->second = t;
    }
    m2.unlock();
}

void Inventory::eraseSub(string user, string des) {
    m2.lock();
    map<string, map<string,int>>::iterator it;
    it = mapMySubscriptions.find(user);
    if(!mapMySubscriptions.empty() && it!=mapMySubscriptions.end()){
        mapMySubscriptions.at(user).erase(des);
    }
    m2.unlock();
}

void Inventory::startTopic(string topic, string name) {
    m2.lock();
    vector<Book> v;
    map<string, vector<Book>>::iterator it;
    it =allBooksInTopic.find(topic);
    if(it== allBooksInTopic.end() || allBooksInTopic.empty()){
        allBooksInTopic.insert(make_pair(topic,v));
    }
    else{
        v = getVectorBook(topic);
        int j = v.size();
        for(int i =0; i<j; i++){
            addKeeper(topic, name, v.at(i));
        }
    }
    m2.unlock();
}

map<string, int> Inventory::getSubMap(string name) {
    return mapMySubscriptions.at(name);
}

map<int, string> Inventory::getspeRec(string name) {
    return receiptIdMap.at(name);
}

void Inventory::addHist(string book, string owner) {
    m2.lock();
    map<string, vector<string>>::iterator it;
    it = history.find(book);

    if(it == history.end() || history.at(book).empty()){
        vector<string> owners;
        owners.push_back(owner);
        history.insert(make_pair(book,owners));
    }
    else{
        history.at(book).push_back(owner);
    }
    m2.unlock();
}

string Inventory::getPrev(string book) {
    m2.lock();
    vector<string> j = history.at(book);
    string o;
    bool got = false;

    for(int i=j.size()-1 ; !got && i>=0; i--){
        if(j.at(i)!=""){
            o = j.at(i);
            got = true;
        }
    }
    m2.unlock();
    return o;
}

void Inventory::eraseBook(string book) {
    m2.lock();
    map<string,vector<string>>::iterator it;
    bool era = false;
    for(it = history.begin(); it!=history.end() && !era; it++){
        if(it->first == book){
            vector<string>::iterator it1;
            int k= history.at(book).size();
            bool ko = false;
            for(int i=0; !ko && i<k-1; i++){
                if(history.at(book).at(i)!=""){
                    history.at(book).at(i).erase();
                    ko = true;
                    era = true;
                }
            }
        }
    }
    m2.unlock();
}

map<pair<string, string>, vector<Book>> Inventory::getKeepersMap() {
    return bookKeepers;
}

map<string, vector<string>> Inventory::getHistory() {
    return history;
}


vector<string> Inventory::splitString(string s, char c) {
    m2.lock();
    stringstream str1(s);
    string tmp;
    vector<string> newOne;
    while (getline(str1, tmp, c)) {
        newOne.push_back(tmp);
    }
    m2.unlock();
    return newOne;
}


