/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/27/2014
 * Last Modification Date: 11/30/2014
 * Assignment:             Final Project
 * Filename:               Patron.cpp
 *
 * Overview:
 *     The Patron class represents a Patron in the Library class. A Patron
 *     is the object used for members of the Library.
 *     This file provides the implementation details for functions not
 *     implemented in Patron.h.
 ************************************************************************/
#include "Book.h"
#include "Patron.h"
#include <iostream>
#include <string>
#include <stdexcept>

// define NULL if not already defined
#ifndef NULL
#define NULL \0
#endif

/********************************************************************
 *  Default constructor. Sets the fineAmount to 0.0.
 *******************************************************************/
Patron::Patron()
{
    fineAmount = 0.0;   // no fine
    // checkedOutBooks empty by default
}

/********************************************************************
 *  Three argument constructor. Sets idNum and name to the specified
 *  values, and sets fineAmount to 0.0.
 *******************************************************************/
Patron::Patron(std::string idn, std::string n)
{
    idNum = idn;        // ID number of patron
    name = n;           // name of patron
    fineAmount = 0.0;   // no fine
    // checkedOutBooks empty by default
}

/********************************************************************
 *  void Patron::addBook(Book* b)
 *
 *  Purpose: This function adds a pointer to a Book to the list of books
 *           checked out by the Patron object.
 *
 *  Preconditions: none
 *
 *  Postconditions: If b is a valid pointer to a Book object and is not
 *                  already checked out, b is added to checkedOutBooks.
 *******************************************************************/
void Patron::addBook(Book* b)
{
    // throw exception if null pointer
    if (b == NULL)
        throw std::invalid_argument("ERROR: Book object not found.");
    
    // check if already checked out based on idCode
    for (int i = 0; i < checkedOutBooks.size(); i++)
    {
        if (b->getIdCode() == checkedOutBooks[i]->getIdCode())
        {
            std::cout << "The patron already has that book checked out.\n";
            return;
        }
    }
    
    // book not checked out if execution reaches here
    // add to checkedOutBooks
    checkedOutBooks.push_back(b);
}

/********************************************************************
 *  void Patron::removeBook(Book* b)
 *
 *  Purpose: This function removes the Book object pointed to by b 
 *           from the list of books checked out by the Patron object.
 *
 *  Preconditions: none
 *
 *  Postconditions: If b is a valid pointer to a Book object that is an
 *                  element of checkedOutBooks, that object is removed
 *                  from checkedOutBooks.
 *******************************************************************/
void Patron::removeBook(Book* b)
{
    // throw exception if null pointer
    if (b == NULL)
        throw std::invalid_argument("ERROR: Book object not found.");
    
    // remove if found in checkedOutBooks
    for (int i = 0; i < checkedOutBooks.size(); i++)
    {
        if (b->getIdCode() == checkedOutBooks[i]->getIdCode())
        {
            checkedOutBooks.erase(checkedOutBooks.begin() + i);
            return;
        }
    }
    
    // book not checked out if execution reaches here
    // print error message
    std::cout << "The patron does not have that book checked out.\n";
}

/********************************************************************
 *  void Patron::amendFine(double amount)
 *
 *  Purpose: This function amends the amount owed in fines by the Patron
 *           object. A positive number increases the fine owed, and a negative
 *           argument decreases the fine owed.
 *
 *  Preconditions: none
 *
 *  Postconditions: The fine owed is adjusted by amount.
 *******************************************************************/
void Patron::amendFine(double amount)
{
    fineAmount += amount;
}
