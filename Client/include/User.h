//
// Created by leviinba@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef ASSIGNMENT3_USER_H
#define ASSIGNMENT3_USER_H

#include <string>

using std::string;

class User {


public:
    User();

    virtual ~User();

    bool isOnline();

    string getUserName();


    void setOffline();


    void setOnReg();


    void setUserName(string userName);



private:
    string UserName;
    bool IsOnline;
    bool isRegister;
};


#endif //ASSIGNMENT3_USER_H
