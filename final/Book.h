//
//  Book.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//  
//  Modified by David Rigert on 11/30/14.
//

#ifndef examples_Book_h
#define examples_Book_h

#include <string>

class Patron;

enum Locale {ON_SHELF, ON_HOLD, CHECKED_OUT};

class Book
{
private:
    std::string idCode;
    std::string title;
    std::string author;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
public:
    static const int CHECK_OUT_LENGTH = 21;
    Book();
    Book(std::string idc, std::string t, std::string a);
    std::string getIdCode()         { return idCode; }
    std::string getTitle()          { return title; }
    std::string getAuthor()         { return author; }
    Locale getLocation()            { return location; }
    void setLocation(Locale lo)     { location = lo; }
    Patron* getCheckedOutBy()       { return checkedOutBy; }
    void setCheckedOutBy(Patron* p) { checkedOutBy = p; }
    Patron* getRequestedBy()        { return requestedBy; }
    void setRequestedBy(Patron* p)  { requestedBy = p; }
    int getDateCheckedOut()         { return dateCheckedOut; }
    void setDateCheckedOut(int d)   { dateCheckedOut = d; }
};

#endif
