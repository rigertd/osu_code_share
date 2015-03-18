/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/13/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Room.hpp
 *
 * Overview:
 *     Represents a room or area in the world. 
 ************************************************************************/
#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <map>

#include "Result.hpp"
#include "Direction.hpp"

class Item;
class World;

class Room
{
    friend class UnitTest;      // for unit testing
protected:
    int id;                     // holds a unique room ID
    std::string description;    // description of the room
    std::map<unsigned, Item *> items;   // list of items in room
    Room *north;                // pointer to north
    Room *south;                // pointer to south
    Room *east;                 // pointer to east
    Room *west;                 // pointer to west
    World *global;              // access to global functions
    
    static int nextId;          // ID of next Room to be created
    
public:
    // constructors
    Room(World *);
    
    // destructor
    virtual ~Room() = 0;
    
    // adds an item to the room
    Result addItem(Item *);
    
    // removes the exit in the specified direction
    virtual Result clearExit(Direction);
    
    // clears the item required to use the room
    virtual Result clearRequired();
    
    // clears the target room of a SwitchRoom
    virtual Result clearTarget();
    
    // finds an item with the specified id in the room or returns NULL
    Item *findItem(unsigned);
    
    // gets a pointer to the specified direction
    virtual Room *getExit(Direction d) const;
    
    // gets a pointer to the target of a SwitchRoom
    virtual Room *getTarget() const { return NULL; }
    
    // gets the ItemMap of the room
    std::map<unsigned, Item *> &getItems()   { return items; }
    
    // gets the room ID
    unsigned getRoomId() const  { return id; }
    
    // removes an item with the specified id from the room
    Result removeItem(unsigned);
    
    // serializes the room data into the save file format
    virtual void serialize(std::ostream &);
    
    // serializes the exits of the room
    virtual void serializeExits(std::ostream &);
    
    // deserializes the exits of the room
    virtual void deserializeExits(std::istream &);
    
    // deserializes the room data and configures the Room object
    virtual void deserialize(std::istream &);
    
    // prompts the user to set the room description
    virtual Result setDescription(std::string = "");
    
    // sets the exit in the specified direction to the specified room
    virtual Result setExit(Direction, Room *);
    
    // sets the item required to use the room
    virtual Result setRequired(Item *);
    
    // sets the target room affected by a SwitchRoom
    virtual Result setTarget(Room *);
    
    // toggles the state of a room with multiple states
    virtual Result toggle();
    
    // enables toggling in the specified direction
    virtual Result toggleExit(Direction);
    
    // attempts to use the specified Item in this room
    virtual Result useItem(Item *);
    virtual Result useItem(unsigned);
    
    // displays the current room info in the terminal window
    virtual void view(bool);
    
    // for converting object to save data
    friend std::ostream &operator<<(std::ostream &, Room &);
};
#endif  // end of ROOM_HPP definition
