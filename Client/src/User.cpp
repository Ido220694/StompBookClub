//
// Created by leviinba@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "User.h"


User::User():UserName() ,IsOnline(true), isRegister(false) {}

User::~User() {

}

bool User::isOnline() {
    return  IsOnline;
}

string User::getUserName() {
    return UserName;
}


void User::setOnReg(){
    isRegister = true;
}


void User::setOffline() {
    IsOnline = false;
}



void User::setUserName(string userName) {
    UserName=userName;
}

