/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               ConditionRoom.hpp
 *
 * Overview:
 *     Represents a conditional room or area in the world. This room can
 *     be toggled between two states by using an item in it, or by using
 *     an item in a SwitchRoom that is linked to it.
 ************************************************************************/
#ifndef CONDITIONROOM_HPP
#define CONDITIONROOM_HPP

#include "Room.hpp"

#include <iostream>

class ConditionRoom : public Room
{
    friend class UnitTest;  // for unit testing
protected:
    std::string altDescription;     // alternate description for toggled state
    bool northEnabled;              // whether the state affects the north exit
    bool eastEnabled;               // whether the state affects the east exit
    bool southEnabled;              // whether the state affects the south exit
    bool westEnabled;               // whether the state affects the west exit
    bool enabled;                   // whether room is in toggled state
    Item *required;                 // item required to toggle the room state
    
public:
    // constructor
    ConditionRoom(World * = NULL);
    
    // destructor
    virtual ~ConditionRoom()
    {
        // memory leak check
        //std::cout << "Room ID " << id << " is being destroyed.\n";
    }
    
    // clears the item required to use the room
    virtual Result clearRequired();
    
    // gets a pointer to the specified direction
    virtual Room *getExit(Direction d) const;
    
    // serializes the room data into the save file format
    virtual void serialize(std::ostream &);
    
    // deserializes the room data and configures the Room object
    virtual void deserialize(std::istream &);
    
    // prompts the user to set the room description
    virtual Result setDescription(std::string = "");
    
    // sets the item required to use the room
    virtual Result setRequired(Item *);
    
    // toggles the state of a room with multiple states
    virtual Result toggle();
    
    // enables toggling in the specified direction
    virtual Result toggleExit(Direction);
    
    // attempts to use the specified Item in this room
    virtual Result useItem(Item *);
    virtual Result useItem(unsigned);
    
    // displays the current room info in the terminal window
    virtual void view(bool);
};
#endif  // end of CONDITIONROOM_HPP definition
