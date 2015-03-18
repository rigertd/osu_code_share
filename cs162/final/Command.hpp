/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/13/2015
 * Last Modification Date: 3/14/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Command.hpp
 *
 * Overview:
 *     Represents a command and an optional argument.
 ************************************************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>   // std::string
#include <map>      // std::map

#include "Result.hpp"

class Command
{
    friend class UnitTest;  // for unit testing
public:
	// enumerates the available command types
	enum CommandType
	{
        COMMAND_HELP,       // display available commands
		ITEM_CREATE,        // create new item
		ITEM_DROP,          // remove item from inventory
		ITEM_TAKE,          // put room item in inventory
		ITEM_USE,           // use item on environment
        PLAYER_INVENTORY,   // view player inventory
        PLAYER_MAX_QUANTITY,// set player maxQuantity
        PLAYER_MAX_SIZE,    // set player maxSize
        PLAYER_MAX_WEIGHT,  // set player maxWeight
        ROOM_CLEAR_REQUIRED,// clear required item
        ROOM_CLEAR_TARGET,  // clear target room
		ROOM_DELETE_NORTH,  // delete exit to north
		ROOM_DELETE_EAST,   // delete exit to east
		ROOM_DELETE_SOUTH,  // delete exit to south
		ROOM_DELETE_WEST,   // delete exit to west
        ROOM_EDIT_DESC,     // edit room description
		ROOM_MAKE_NORTH,    // make exit to north
		ROOM_MAKE_EAST,     // make exit to east
		ROOM_MAKE_SOUTH,    // make exit to south
		ROOM_MAKE_WEST,     // make exit to west
		ROOM_MOVE_NORTH,    // go north from current location
		ROOM_MOVE_EAST,     // go east from current location
		ROOM_MOVE_SOUTH,    // go south from current location
		ROOM_MOVE_WEST,     // go west from current location
		ROOM_SET_REQUIRED,  // set item required to toggle room
		ROOM_SET_TARGET,    // set target of SwitchRoom
		ROOM_TOGGLE,        // toggles room state
        ROOM_ENABLE_NORTH,  // enable toggle on north exit
        ROOM_ENABLE_EAST,   // enable toggle on east exit
        ROOM_ENABLE_SOUTH,  // enable toggle on south exit
        ROOM_ENABLE_WEST,   // enable toggle on west exit
		WORLD_CLEAN,        // delete unused rooms and items
        WORLD_DELETE_ITEM,  // delete existing item
		WORLD_DELETE_ROOM,  // delete existing room
		WORLD_EDIT,         // toggle edit mode
		WORLD_ITEM_LIST,    // list all items in world
		WORLD_ROOM_LIST,    // list all rooms in world
		WORLD_SAVE,         // save the world to file
		WORLD_SET_END,      // set end point
        WORLD_SET_INTRO,    // set the introduction text
		WORLD_SET_START,    // set start point
		WORLD_SET_TIME,     // set time limit
		WORLD_EXIT,         // exit the game
        INVALID_COMMAND     // invalid command
	};
    
    // create type for command map
    typedef std::map<std::string, Command> CommandMap;
    
private:    
    
	std::string argument;   // optional command argument
    std::string desc;       // description of command for help list
    bool edit;              // whether command is an edit mode command
	CommandType type;       // command type
	static CommandMap commands; // maps valid command string to Command object
    static CommandMap populateCommands(); // populates command map with commands
    
public:
    // prints all available commands
    static void printCommands(bool);
    
    // constructors
    Command()
    {
        this->type = INVALID_COMMAND;
        this->edit = false;
    }
    Command(CommandType type)
    {
        this->type = type;
        this->edit = false;
    }
    Command(CommandType, const char *, bool);
    
    // reads user input and configures the command object
    Result read(const std::string &, bool);
    // gets the command type
    CommandType getType() const     { return type; }
    // gets the argument string
    std::string getArgument() const { return argument; }
    // sets the argument string
    void setArgument(std::string arg) { argument = arg; }
};
#endif  // end of COMMAND_HPP definition
