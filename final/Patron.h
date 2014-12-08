//
//  Patron.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//  
//  Modified by David Rigert on 11/30/14.
//

#ifndef __examples__Patron__
#define __examples__Patron__

#include <stdio.h>
#include <vector>
#include <string>

class Book;

class Patron
{
private:
    std::string idNum;                      // id number of patron
    std::string name;                       // name of patron
    std::vector<Book*> checkedOutBooks;     // books checked out by patron
    double fineAmount;                      // amount owed in fines by patron
public:
    Patron();                               // see implementation file
    Patron(std::string idn, std::string n); // see implementation file
    std::string getIdNum()                  { return idNum; }
    std::string getName()                   { return name; }
    std::vector<Book*> getCheckedOutBooks() { return checkedOutBooks; }
    void addBook(Book* b);                  // see implementation file
    void removeBook(Book* b);               // see implementation file
    double getFineAmount()                  { return fineAmount; }
    void amendFine(double amount);          // see implementation file
};

#endif /* defined(__examples__Patron__) */
