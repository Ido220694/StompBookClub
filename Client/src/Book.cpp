//
// Created by leviinba@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include <string>
#include "Book.h"

using std::string;


//constructor
Book::Book(string bookname) :BookName(bookname), Genere(),Available(true),  Owner(), myKeepers() {}


//Destructor
Book::~Book() {

}


string Book::getBookName() {
    return BookName;
}


string Book::getGenere() {
    return Genere;
}


string Book::getOwner() {
    return Owner;
}

void Book::setOwner(string owner) {
    Owner = owner;
}

void Book::setGenere(string genere) {
    Genere = genere;
}

void Book::addNewKeeper(string name) {
    myKeepers.push_back(name);
}








