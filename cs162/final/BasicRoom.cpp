/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               BasicRoom.hpp
 *
 * Overview:
 *     Implementation for BasicRoom class.
 ************************************************************************/
#include "BasicRoom.hpp"

// constructor
BasicRoom::BasicRoom(World *w) : Room(w)
{
    description = "A new basic room with no interactivity.\n";
}
