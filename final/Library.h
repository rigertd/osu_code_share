//
//  Library.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//  
//  Modified by David Rigert on 11/30/14.
//

#ifndef __examples__Library__
#define __examples__Library__

#include <vector>
#include <string>
#include <stdio.h>

class Patron;
class Book;

class Library
{
private:
    std::vector<Book> holdings;
    std::vector<Patron> members;
    int currentDate;
    int findBook(std::string bookId);       // finds a book in holdings
    int findMember(std::string memberId);   // finds a patron in members
public:
    static const double DAILY_FINE = 0.1;
    Library();
    bool isMember(std::string memberId);    // checks if valid member ID
    void addBook();
    void addMember();
    void checkOutBook(std::string patronID, std::string bookID);
    void returnBook(std::string bookID);
    void requestBook(std::string patronID, std::string bookID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    void viewBookInfo(std::string bookID);
};

#endif /* defined(__examples__Library__) */
