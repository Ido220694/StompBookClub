//
// Created by leviinba@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "ProtocolImpl.h"
#include "Frame.h"
#include "Inventory.h"
#include "Book.h"


#include <string>
#include <iostream>
#include <vector>


using namespace std;
ProtocolImpl::ProtocolImpl(Inventory &inv, User &u, ConnectionHandler &handler1) :name(), handler(&handler1), inventory(&inv),wishToBorrow() , IAM(&u), running(
        true) {
}

void ProtocolImpl::run() {
    while (running) {
        string line;
        if(handler->isConnected()) {
            if (handler->getFrame(line)) {
                processIn(line);
            }
        }

    }

}




void ProtocolImpl::processIn(string str) {
        string s;
        int j = str.length();
        for (int i=0;i<j;i++) {
            if (str.at(i) == '\r') {
                cout << s << endl;
                s = "";
            } else {
                s += str.at(i);
            }
        }
        cout<<s<<endl;

        int sign =0;
    Connected connected = Connected();
    Receipt receipt = Receipt();
    Message msg = Message();
    Error err = Error();


    vector<string> vec = splitString(str, '\r');
        if(vec.at(0) == "CONNECTED") {
            sign =1;
//            connected.SetType("Connected");
        }
        else if(vec.at(0) =="RECEIPT"){
            sign=2;
            int t = stoi(vec.at(1).substr(11));
            receipt.setRec(t);
//            receipt.SetType("Receipt");
        }
        else if(vec.at(0) =="MESSAGE"){
            sign=3;
            msg.setBody(vec.at(5));
            msg.setDest(vec.at(3).substr(12));
            string i = vec.at(2).substr(11);
            string sili = vec.at(1).substr(13);
//            msg.SetType("Message");
        } else if(vec.at(0) =="ERROR"){
            sign=4;
            err.setBody(vec.at(11));
//            err.SetType("Error");
        }



    if (sign == 1) {
        name = IAM->getUserName();
        cout << "login successful" << endl;

    } else if (sign ==2) {

        int rec = receipt.getRecId();
        map<string, map<int, string>>::iterator it;
        it = inventory->getRecMap().find(name);

        if (inventory->getRecMap().empty() || it == inventory->getRecMap().end()) {
            cout << "Error" << endl;
        } else {
            map<int, string> nan = inventory->getspeRec(name);
            map<int, string>::iterator it1;
            it1 = nan.find(rec);
            if (it1 == nan.end()) {
                cout << "Error: wrong recId" << endl;
            } else {

                string didid = inventory->getReciptIdMap(name).at(rec);
                vector<string> v = splitString(didid, ' ');

                if (v.at(0) == "disconnect") {
                    map<string, map<string, int>>::iterator itr;

                    if(!inventory->getSUbMap().empty()) {


                        itr = inventory->getSUbMap().find(name);

                        if (itr == inventory->getSUbMap().end()) {
                            cout << "Error" << endl;
                        } else {
                            map<string, int> lama = inventory->getMySubscriptions(name);
                            map<string, int>::iterator it3;
                            vector<string> topics;
                            for (it3 = lama.begin(); it3 != lama.end(); ++it3) {
                                topics.push_back(it3->first);
                            }
                            int k = topics.size();
                            for (int i = 0; i < k; i++) {
                                vector<Book> books = inventory->getVecByName(topics.at(i), name);
                                int y = books.size();
                                for (int j = 0; j < y; j++) {
                                    inventory->removeKeeper(books.at(j).getGenere(), name, books.at(j).getBookName());
                                    inventory->eraseBook(books.at(j).getOwner(), books.at(j).getGenere(),
                                                         books.at(j).getBookName());
                                }
                            }
                        }
                    }
                    IAM->setOffline();
                    running = false;

                } else if (v.at(0) == "subscribe") {
                    cout << "Joined club " + v.at(1) << endl;
                } else if (v.at(0) == "unsubscribe") {
                    map<string, map<string, int>>::iterator it4;
                    it4 = inventory->getSUbMap().find(name);
                    if (inventory->getSUbMap().empty() || it4 == inventory->getSUbMap().end()) {
                        cout << "Error: you tried to exit topic you dindn't subscribe" << endl;
                    } else {
                        int subid1 = inventory->getMySubscriptions(name).at(v.at(1));
                        bool e = false;
                        map<string,int> nana = inventory->getMySubscriptions(name);

                        for (auto it5 = nana.begin(); it5 != nana.end() && !e; it5++) {
                            if (it5->second == subid1) {
                                inventory->eraseSub(name, it5->first);
                                e = true;
                            }
                        }
                        if (!e) {
                            cout << "Error: you tried to exit topic you dindn't subscribe" << endl;
                        }
                        cout << "Exited club " << v.at(1) << endl;

                    }

                }
            }
        }

    } else if (sign==3) {
        string body = msg.getBody();
        vector<string> content = splitString(body, ' ');
        string desName = msg.getDestination();

        if (content.at(1) == "wish") {
            stringstream book;
            int j = content.size();
            for (int i = 4; i < j - 1; i++) {
                book << content.at(i) << " ";
            }
            book << content.at(content.size() - 1);
            string bookName = book.str();

            if (content.at(0) == name) {
                wishToBorrow = bookName;
            }
            else {
                bool hasIt = false;
                map<string, map<string, int>> na1 = inventory->getSUbMap();
                map<string, map<string, int>>::iterator it;
                it = na1.find(name);
                if (it == na1.end()) {
                    cout << "error" << endl;
                } else {
                    map<string, int> na = inventory->getSubMap(name);
                    map<string, int>::iterator it2;
                    it2 = na.find(desName);
                    if (it2 == na.end()) {
                        cout << "Error: I'm not subscribing this topic.." << endl;
                    } else {
                        map<pair<string, string>, vector<Book>>::iterator it3;
                        map<pair<string, string>, vector<Book>> ma = inventory->getKeepersMap();
                        it3 = ma.find(make_pair(desName, name));
                        if (it3 != ma.end()) {
                            vector<Book> v = inventory->getVecByName(desName, name);
                            int r = v.size();
                            for (int i = 0; i < r; i++) {
                                if (v.at(i).getBookName() == bookName) {
                                    hasIt = true;
                                }
                            }
                        }
                    }
                }
                if (hasIt) {
                    Send send = Send();
                    send.setDestination(desName);
                    send.setBody(name + " has " + bookName);
                    string toServer = transformSendTostring(send);
                    handler->sendFrame(toServer);
                }
            }

        } else if (content.at(1) == "has" && content.at(2) != "added") {
            stringstream book;
            int w = content.size();
            for (int i = 2; i < w - 1; i++) {
                book << content.at(i) << " ";
            }
            book << content.at(content.size() - 1);
            string bookName = book.str();


            if (wishToBorrow == bookName) {
                Send send = Send();
                send.setDestination(msg.getDestination());
                send.setBody("Taking " + wishToBorrow + " from " + content.at(0));
                Book take= Book(bookName);



                inventory->addKeeper(desName,name, take);
                inventory->addBookTop(desName, take);
                inventory->addHist(bookName, content.at(0));
                wishToBorrow = "";

                string toServer = transformSendTostring(send);
                handler->sendFrame(toServer);
            }
        } else if (content.at(0) == "Taking") {
            if (content.at(content.size() - 1) == name) {

                stringstream book;
                int t = content.size();
                for (int i = 1; i < t - 3; i++) {
                    book << content.at(i) << " ";
                }
                book << content.at(content.size() - 3);
                string bookName = book.str();
                inventory->removeKeeper(msg.getDestination(), name, bookName);

            }

        } else if (content.at(0) == "Returning") {
            if (content.at(content.size() - 1) == name) {
                string topic = msg.getDestination();

                stringstream book;
                int g = content.size();
                for (int i = 1; i < g - 3; i++) {
                    book << content.at(i) << " ";
                }
                book << content.at(content.size() - 3);
                string bookName = book.str();
                string owner = inventory->getPrev(bookName);
                Book b = Book(bookName);
                b.setGenere(topic);
                b.setOwner(owner);
                b.addNewKeeper(name); //im not sure if its true.
                //here problem
                inventory->addKeeper(topic, name, b);
            }
            } else if (content.at(0) == "book") {
                string topic = msg.getDestination();
                stringstream toSend;
                toSend << name << ":";

                map<pair<string,string>,vector<Book>>::iterator it;
                map<pair<string,string>,vector<Book>> banana = inventory->getKeepersMap();

                it = banana.find(make_pair(topic,name));

                if(it != banana.end() && !inventory->getVecByName(topic,name).empty()){
                    vector<Book> tmp = inventory->getVecByName(topic, name);
                    int l = tmp.size();
                    for (int i = 0; i < l - 1; i++) {
                        toSend << tmp.at(i).getBookName() << ",";
                    }
                    toSend << tmp.at(tmp.size() - 1).getBookName();
                }

                cout<<toSend.str()<<endl;

            } else if (content.at(2) == "added") {
                stringstream book;
                int m = content.size();
                for (int i = 5; i < m - 1; i++) {
                    book << content.at(i) << " ";
                }
                book << content.at(content.size() - 1);
                string bookName = book.str();

                Book k = Book(bookName);
                k.setGenere(msg.getDestination());
                k.setOwner(content.at(0));

                inventory->insertBook(msg.getDestination(), k);

        }
        } else if (sign==4) {
            if(err.getBody()== "You can't re-login after you already logged-in"){
                handler->close();
            }
        }

}





string ProtocolImpl::transformSendTostring(Send frm) {

    stringstream toSend;

    toSend << "SEND" << "\r";
    toSend << "destination:" << frm.getDesti() << "\r" << "\n";
    toSend << frm.getBody() << "\r";
    toSend << "\0";

    string s = toSend.str();
    return s;

}


vector<string> ProtocolImpl::splitString(string s, char c) {
    stringstream str1(s);
    string tmp;
    vector<string> newOne;
    while (getline(str1, tmp, c)) {
        newOne.push_back(tmp);
    }
    return newOne;
}

ProtocolImpl::ProtocolImpl(const ProtocolImpl & pt): name(pt.name), handler(pt.handler), inventory(pt.inventory), wishToBorrow(pt.wishToBorrow), IAM(pt.IAM), running(pt.running) {

}



ProtocolImpl &ProtocolImpl::operator=(const ProtocolImpl & pt) {
    if(this != &pt){

    }
    return *this;
}



