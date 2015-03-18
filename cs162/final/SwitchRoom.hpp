/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               SwitchRoom.hpp
 *
 * Overview:
 *     Represents a room that can toggle the state of a different ConditionRoom
 *     when the correct item is used in it.
 ************************************************************************/
#ifndef SWITCHROOM_HPP
#define SWITCHROOM_HPP

#include <iostream>
#include "Room.hpp"

class SwitchRoom : public Room
{
    friend class UnitTest;  // for unit testing
protected:
    std::string altDescription;     // alternate description for toggled state
    bool enabled;                   // whether room is in toggled state
    Item *required;                 // item required to toggle the room state
    Room *target;                   // room affected by switch

public:
    // constructor
    SwitchRoom(World * = NULL);
    
    // destructor
    virtual ~SwitchRoom()
    {
        // memory leak check
        //std::cout << "Room ID " << id << " is being destroyed.\n";
    }
    
    // clears the item required to use the room
    virtual Result clearRequired();
    
    // clears the target room of the room
    virtual Result clearTarget();
    
    // gets a pointer to the target of the room
    virtual Room *getTarget() const { return target; };
    
    // serializes the room data into the save file format
    virtual void serialize(std::ostream &);
    
    // deserializes the room data and configures the Room object
    virtual void deserialize(std::istream &);
    
    // prompts the user to set the room description
    virtual Result setDescription(std::string = "");
    
    // sets the item required to use the room
    virtual Result setRequired(Item *);
    
    // sets the target room affected by this room
    virtual Result setTarget(Room *);
    
    // toggles the state of a room with multiple states
    virtual Result toggle();
    
    // attempts to use the specified Item in this room
    virtual Result useItem(Item *);
    virtual Result useItem(unsigned);
    
    // displays the current room info in the terminal window
    virtual void view(bool);
};
#endif  // end of SWITCHROOM_HPP definition
