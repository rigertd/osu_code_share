/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           2/28/2015
 * Last Modification Date: 3/1/2015
 * Course:                 CS162_400
 * Assignment:             Lab 8
 * Filename:               World.hpp
 *
 * Overview:
 *     Represents the overall world or map. The map consists of a series
 *     of areas or rooms. Each room has one or more of 4 possible directions:
 *     east, west, north, or south.
 ************************************************************************/
#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>

// enumerates the available commands in each room
enum Command
{
    MOVE_NORTH,     // go north
    MOVE_EAST,      // go east
    MOVE_SOUTH,     // go south
    MOVE_WEST,      // go west
    TOGGLE_LABEL,   // toggle label visibility
    TOGGLE_EDIT,    // toggle edit mode
    EDIT_DESC,      // edit description
    MAKE_NORTH,     // make room to north
    MAKE_EAST,      // make room to east
    MAKE_SOUTH,     // make room to south
    MAKE_WEST,      // make room to west
    DELETE_NORTH,   // delete room to north
    DELETE_EAST,    // delete room to east
    DELETE_SOUTH,   // delete room to south
    DELETE_WEST,    // delete room to west
    SET_START,      // set room as start point
    SET_END,        // set room as end point
    SAVE_WORLD,     // save the world to file
    LOAD_WORLD,     // load the world from file
    EXIT,           // exit the program
    HELP            // show available commands
};

// enumerates available directions
enum Direction
{
    NONE,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

// enumerates command results
enum Result
{
    RESULT_SUCCESS,
    RESULT_FAILURE,
    RESULT_EXIT,
    RESULT_SAVE,
    RESULT_LOAD
};

class World
{
private:
    /******************************************************
    *             Private Member Variables                *
    ******************************************************/
    // represents a room or area in the world
    struct Room
    {
        int roomId;                 // holds a unique room ID
        std::string description;    // description of the room
        Room *north;                // pointer to north
        Room *south;                // pointer to south
        Room *east;                 // pointer to east
        Room *west;                 // pointer to west
        
        // constructor
        Room(int id)
        {
            roomId = id;
            description = "A new room";
            north = NULL;
            south = NULL;
            east = NULL;
            west = NULL;
        }
        ~Room()
        {
            // memory leak check
            //std::cout << "Destroying Room " << roomId << std::endl;
        }
    };
    
    Room *start;        // starting point
    Room *end;          // exit
    Room *current;      // current location
    int nextRoomId;     // holds the next room ID
    bool editMode;      // edit mode flag
    bool labelVis;      // label visibility flag
    
    // maps string input to the corresponding command
    std::map<std::string, Command> commands;
    
    /******************************************************
    *             Private Member Functions                *
    ******************************************************/
    // loads the world from a file
    Result load(Room *&, Room *, std::ifstream &);
    
    // saves the world to a file
    Result save(Room *, Direction, std::ofstream &);
    
    // builds the command map
    void buildCommandMap();
    
    // deletes the room in the specified direction
    // and any orphaned rooms
    Result deleteRoom(Direction);
    
    // deletes the entire tree connected to the specified room
    Room *deleteTree(Room *);
    
    // edits the description of the current room
    Result editRoom();
    
    // creates a new room in the specified direction
    Result makeRoom(Direction);
    
    // moves in the specified direction
    Result move(Direction);
    
    // displays the help menu
    void printHelp() const;
    
    // runs the specified command
    Result runCommand(Command);
    
public:
    /******************************************************
    *            Constructors and Destructor              *
    ******************************************************/
    World();
    ~World();

    /******************************************************
    *              Public Member Functions                *
    ******************************************************/
    // parses user input and runs the specified command
    Result command(std::string &);
    
    // displays the current room
    void printRoom() const;
    
    // loads world data
    Result loadWorld(std::ifstream &);
    
    // saves world data
    Result saveWorld(std::ofstream &);
};

#endif  // end of WORLD_HPP definition
