#include <iostream>
#include "connectionHandler.h"
#include <string>
#include "ReadFromKeyboard.h"


using namespace std;


ReadFromKeyBoard::ReadFromKeyBoard(ConnectionHandler &connectionHandler,User &u, Inventory &inv, vector<string> s) :
_connectionHandler(&connectionHandler),IAM(&u), name(), inventory(&inv),countSubId(1), countRec(1) , running(true),start(s) {


}

void ReadFromKeyBoard::run() {
//    bool logout = false;
//    running = true;
//    _connectionHandler->connect();

    processOut(start);

    while (running && IAM->isOnline()) {

        const short bufsize = 1024;

        char buf[bufsize];

        cin.getline(buf, bufsize);

        string line(buf);

        vector<string> newVec = splitString(line, ' ');

        processOut(newVec);

    }
}

vector<string> ReadFromKeyBoard::splitString(string s, char c) {
    stringstream str1(s);
    string tmp;
    vector<string> newOne;
    while (getline(str1, tmp, c)) {
        newOne.push_back(tmp);
    }
    return newOne;

}

void ReadFromKeyBoard::processOut(vector<string> s) {
    if (s.at(0) == "login") { //valgrid
//        if(IAM->getReg()){
//            _connectionHandler->connect();
//        }
        if(!_connectionHandler->isConnected()){
            _connectionHandler->connect();
        }

        IAM->setOnReg();
        Connect connect = Connect();
        connect.setHost(s.at(1));
        vector<string> to = splitString(s.at(1),':');
        string host = to.at(0);
        string port = to.at(1);



        connect.setLogin(s.at(2));
        connect.setPasscode(s.at(3));
        name = s.at(2);
        IAM->setUserName(name);
        string toServer = transformConnectTostring(connect);
        inventory->addUser(name, IAM);
        _connectionHandler->sendFrame(toServer);
//        }

    }
    if (s.at(0) == "join") {
        Subscribe subscribe = Subscribe();
        subscribe.setDestination(s.at(1));
        subscribe.setId(countSubId); // valgrind
        map<string, map<string, int>>::iterator itr;
        itr = inventory->getSUbMap().find(name);

        if (inventory->getSUbMap().empty() || itr == inventory->getSUbMap().end()) {

            inventory->addSubsMap(name, s.at(1), countSubId);
            countSubId++;


            subscribe.setRecId(countRec);
            map<string, map<int, string>>::iterator it;
            it = inventory->getRecMap().find(name);

            if (inventory->getRecMap().empty() || it == inventory->getRecMap().end()) {
                inventory->addRecMap(name, countRec, "subscribe " + subscribe.getDesti());
            } else {
                inventory->updateReceiptIdMap(name, countRec, "subscribe " + subscribe.getDesti());
            }

            countRec++;
            inventory->startTopic(s.at(1), name);
            string toServer = transformSubscribeTostring(subscribe);

            _connectionHandler->sendFrame(toServer);

        }
        else {


        inventory->startTopic(s.at(1), name);
        map<string, int>::iterator itr1;
        map<string, int> na = inventory->getSubMap(name);
        itr1 = na.find(s.at(1));

        if (itr1 == na.end()) {
            inventory->updateMySubscriptions(name, s.at(1), countSubId);
            countSubId++;
            subscribe.setRecId(countRec);

            map<string, map<int, string>>::iterator it;
            it = inventory->getRecMap().find(name);

            if (it == inventory->getRecMap().end()) {
                inventory->addRecMap(name, countRec, "subscribe " + subscribe.getDesti());
            } else {
                inventory->updateReceiptIdMap(name, countRec, "subscribe " + subscribe.getDesti());
            }

            inventory->updateReceiptIdMap(name, countRec, "subscribe " + subscribe.getDesti());

            countRec++;


            string toServer = transformSubscribeTostring(subscribe);

            _connectionHandler->sendFrame(toServer);
        }
    }
    }
    if (s.at(0) == "exit") {
        Unsubscribe unsubscribe = Unsubscribe();
        map<string, map<string,int>>::iterator it;
        it = inventory->getSUbMap().find(name);

        if(inventory->getSUbMap().empty() || it == inventory->getSUbMap().end()){
            cout<<"Error: you tried to unsubscribe a topic which you didn't subscribe"<<endl;
        }
        else{
            map<string,int>::iterator itr;
            map<string,int> na = inventory->getSubMap(name);
            itr = na.find(s.at(1));
            if(itr == na.end()){
                cout<<"Error: you tried to unsubscribe a topic which you didn't subscribe"<<endl;
            }
            else{
                int tmp1 = inventory->getMySubscriptions(name).at(s.at(1));

                string tmp = s.at(1);
                unsubscribe.setId(tmp1);
                unsubscribe.setRecId(countRec);
//                inventory->eraseSub(name, tmp);

                map<string, map<int,string>>::iterator it1;
                it1 = inventory->getRecMap().find(name);

                if(inventory->getRecMap().empty() || it1 == inventory->getRecMap().end()){
                    inventory->addRecMap(name, countRec, "unsubscribe " + tmp);
                }
                else{
                    inventory->updateReceiptIdMap(name, countRec, "unsubscribe " + tmp);
                }
                countRec++;
                string toServer = transformUnsubscribeTostring(unsubscribe);

                _connectionHandler->sendFrame(toServer);

            }
        }

    }

    if (s.at(0) == "add") {
        string d = s.at(1);
        stringstream book;
        int f = s.size();
        for (int i = 2; i < f - 1; i++) {
            book << s.at(i) << " ";
        }
        book << s.at(s.size() - 1);
        string bookName = book.str();
        Book newbook = Book(bookName);
        newbook.setGenere(s.at(1));
        newbook.setOwner(name);
        newbook.addNewKeeper(name);

        map<string, vector<Book>>::iterator it;
        it = inventory->getAllBook().find(d);

        if(inventory->getAllBook().empty() || it == inventory->getAllBook().end()){
            inventory->insertBook(d, newbook);
            map<string, map<string,int>> nana = inventory->getSUbMap();
            map<string, map<string,int>>::iterator iter;
            iter = nana.find(name);
            if(iter != nana.end()){
                map<string,int> subs = inventory->getSubMap(name);
                map<string,int>::iterator iter3;
                iter3 = subs.find(s.at(1));
                if(iter3 != subs.end()){
                    inventory->insertBook(s.at(1), newbook);
                }
            }

        } else {
            inventory->insertBook(s.at(1), newbook);
            inventory->addKeeper(s.at(1), name, newbook);
        }
        Send send = Send();
        send.setBody(name + " has added the book " + bookName);
        send.setDestination(s.at(1));
        string toServer = transformSendTostring(send);
        inventory->addHist(bookName, name);
        _connectionHandler->sendFrame(toServer);



    }
    if (s.at(0) == "borrow") {
        Send send = Send();

        stringstream book;
        int j = s.size();
        for (int i = 2; i < j - 1; i++) {
            book << s.at(i) << " ";
        }
        book << s.at(s.size() - 1);
        string bookName = book.str();
        send.setBody(name + " wish to borrow " + bookName);

        send.setDestination(s.at(1));

        string toServer = transformSendTostring(send);

        _connectionHandler->sendFrame(toServer);


    }
    if (s.at(0) == "return") {

        stringstream book;
        int k = s.size();
        for (int i = 2; i < k - 1; i++) {
            book << s.at(i) << " ";
        }
        book << s.at(s.size() - 1);
        string bookName = book.str();

        Send send = Send();
//        Book book1 = inventory->getBook(s.at(1), name, bookName);

//        book1.eraseKeeper();
        map<string, vector<string>> his = inventory->getHistory();
        map<string,vector<string>>::iterator it;
        string owner ="";
        for(it = his.begin(); it!=his.end(); it++){
            if(it->first == bookName && !it->second.empty() ){
                owner = inventory->getPrev(bookName);
            }
        }
        if(owner != ""){
            inventory->eraseBook(bookName);
            send.setDestination(s.at(1));
            send.setBody("Returning " + bookName + " to " + owner);
            string toServer = transformSendTostring(send);
            inventory->removeKeeper(s.at(1), name, bookName);
            _connectionHandler->sendFrame(toServer);
        }

    }
    if (s.at(0) == "status") {
        Send send = Send();
        send.setBody("book status");
        send.setDestination(s.at(1));
        string toServer = transformSendTostring(send);
        _connectionHandler->sendFrame(toServer);

    }
    if (s.at(0) == "logout") {

        map<string, map<string,int>>::iterator it1;
        map<string, map<string,int>> nana = inventory->getSUbMap();

        if(!nana.empty()) {
            it1 = nana.find(name);
            if (it1 != nana.end()) {
                map<string, int>::iterator it3;
                map<string, int> nam = inventory->getSubMap(name);
                for (it3 = nam.begin(); it3 != nam.end(); it3++) {
                    int sub = it3->second;
                    string des = it3->first;
//                    inventory->eraseSub(name, des);
                    Unsubscribe unsubscribe = Unsubscribe();
                    unsubscribe.setId(sub);

                    unsubscribe.setRecId(countRec);
                    map<string, map<int, string>>::iterator it2;
                    it2 = inventory->getRecMap().find(name);
                    map<string, map<int, string>> nama1 = inventory->getRecMap();


                    if (nama1.empty() || it2 == nama1.end()) {
                        inventory->addRecMap(name, countRec, "unsubscribe " + des);
                    } else {
                        inventory->updateReceiptIdMap(name, countRec, "unsubscribe " + des);
                    }
                    countRec++;
                    string toServer = transformUnsubscribeTostring(unsubscribe);
                    _connectionHandler->sendFrame(toServer);
                }
            }
        }

        Disconnect disconnect = Disconnect();
        disconnect.setRecId(countRec);

        map<string, map<int,string>>::iterator it;
        map<string, map<int,string>> nama = inventory->getRecMap();

        it = nama.find(name);
        if(nama.empty() || it == nama.end()){ // we have a problem here, out map is empty after immediately logout and
            inventory->addRecMap(name, countRec, "disconnect" );
        }
        else{
            inventory->updateReceiptIdMap(name, countRec, "disconnect");
        }

//            countRec++;
        string toServer = transformDisconnectTostring(disconnect);
        _connectionHandler->sendFrame(toServer);
        running = false;
    }

}

string ReadFromKeyBoard::transformConnectTostring(Connect frm) {
    stringstream toSend;
    toSend << "CONNECT" << "\n";
    toSend << "accept-version:1.2" << "\n";
    toSend << "host:" << frm.getHost() << "\n";
    toSend << "login:" << frm.getlogin() << "\n";
    toSend << "passcode:" + frm.getpasscode() + "\n";
    toSend << "\0";

    string s = toSend.str();

    return s;

}

string ReadFromKeyBoard::transformSubscribeTostring(Subscribe frm) {
    stringstream toSend;

    toSend << "SUBSCRIBE" << "\n";
    toSend << "destination:" << frm.getDesti() << "\n";
    toSend << "id:" << frm.getId() << "\n";
    toSend << "receipt:" << frm.getRec() << "\n";
    toSend << "\0";

    string s = toSend.str();

    return s;

}

string ReadFromKeyBoard::transformUnsubscribeTostring(Unsubscribe frm) {
    stringstream toSend;

    toSend << "UNSUBSCRIBE" << "\n";
    toSend << "id:" << frm.getId() << "\n";
    toSend << "receipt:" << frm.getRec() << "\n";
    toSend << "\0";

    string s = toSend.str();

    return s;


}


string ReadFromKeyBoard::transformSendTostring(Send frm) {

    stringstream toSend;

    toSend << "SEND" << "\n";
    toSend << "destination:" << frm.getDesti() << "\n" ;
    toSend << frm.getBody() << "\n";
    toSend << "\0";

    string s = toSend.str();
    return s;
}


    string ReadFromKeyBoard::transformDisconnectTostring(Disconnect frm) {

    stringstream toSend;

    toSend << "DISCONNECT" << "\n";
    toSend << "receipt:" << frm.getRec() << "\n";
    toSend << "\0";
    string s = toSend.str();
    return s;

}

ReadFromKeyBoard::~ReadFromKeyBoard() {

}

ReadFromKeyBoard::ReadFromKeyBoard(const ReadFromKeyBoard & re) : _connectionHandler(re._connectionHandler), IAM(re.IAM), name(re.name), inventory(re.inventory), countSubId(re.countSubId), countRec(re.countRec), running(re.running), start(re.start){

}

ReadFromKeyBoard &ReadFromKeyBoard::operator=(const ReadFromKeyBoard &re) {
    if(this!=&re){

    }
    return  *this;
}




