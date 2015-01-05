/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/27/2014
 * Last Modification Date: 11/30/2014
 * Assignment:             Final Project
 * Filename:               Book.cpp
 *
 * Overview:
 *     The Book class represents a Book in the Library class.
 *     This file provides the implementation details for functions not
 *     implemented in Book.h.
 ************************************************************************/
#include "Book.h"
#include <string>

// define NULL if not already defined
#ifndef NULL
#define NULL \0
#endif

/********************************************************************
 *  Default constructor. Sets pointers to NULL and location is undefined.
 *******************************************************************/
Book::Book()
{
    checkedOutBy = NULL;    // not checked out
    requestedBy = NULL;     // not requested
    dateCheckedOut = 0;     // not checked out
    // idCode, title, and author are empty strings
    // location is undefined
}

/********************************************************************
 *  Three argument constructor. Sets idCode, title, and author to the
 *  specified values, and sets location to ON_SHELF.
 *******************************************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
    idCode = idc;           // ID code of book
    title = t;              // title of book
    author = a;             // author of book
    checkedOutBy = NULL;    // not checked out
    requestedBy = NULL;     // not requested
    dateCheckedOut = 0;     // not checked out
    location = ON_SHELF;    // on the shelf
}
