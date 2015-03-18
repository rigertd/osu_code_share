/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               BasicRoom.hpp
 *
 * Overview:
 *     Represents a basic room or area in the world with no interactivity.
 ************************************************************************/
#ifndef BASICROOM_HPP
#define BASICROOM_HPP

#include "Room.hpp"

#include <iostream>

class BasicRoom : public Room
{
    friend class UnitTest;  // for unit testing
public:
    // constructor
    BasicRoom(World * = NULL);
    
    // destructor
    virtual ~BasicRoom()
    {
        // memory leak check
        // std::cout << "Room ID " << id << " is being destroyed.\n";
    }
};
#endif  // end of BASICROOM_HPP definition
