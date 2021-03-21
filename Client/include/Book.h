//
// Created by leviinba@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef ASSIGNMENT3_BOOK_H
#define ASSIGNMENT3_BOOK_H

#include <string>
#include <vector>

using namespace std;

using std::string;

class Book {

public:
    Book(string Bookname);

    virtual ~Book();

    string getBookName();


    string getGenere();

    string getOwner();

    void setGenere(string genere);

    void setOwner(string owner);

    void addNewKeeper(string name);



private:
    string BookName;
    string Genere;
    bool Available;
    string Owner;
    vector<string> myKeepers;

};


#endif //ASSIGNMENT3_BOOK_H
