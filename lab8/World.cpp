/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           2/28/2015
 * Last Modification Date: 3/1/2015
 * Course:                 CS162_400
 * Assignment:             Lab 8
 * Filename:               World.cpp
 *
 * Overview:
 *     Implementation for World class.
 ************************************************************************/
#include <cstdlib>  // atoi

#include "utility.hpp"
#include "World.hpp"

/******************************************************
*             Private Member Functions                *
******************************************************/
// populates the commands map
void World::buildCommandMap()
{
    commands["north"] = MOVE_NORTH;
    commands["n"] = MOVE_NORTH;
    commands["east"] = MOVE_EAST;
    commands["e"] = MOVE_EAST;
    commands["south"] = MOVE_SOUTH;
    commands["s"] = MOVE_SOUTH;
    commands["west"] = MOVE_WEST;
    commands["w"] = MOVE_WEST;
    commands["label"] = TOGGLE_LABEL;
    commands["l"] = TOGGLE_LABEL;
    commands["edit"] = TOGGLE_EDIT;
    commands["description"] = EDIT_DESC;
    commands["desc"] = EDIT_DESC;
    commands["makenorth"] = MAKE_NORTH;
    commands["mn"] = MAKE_NORTH;
    commands["makeeast"] = MAKE_EAST;
    commands["me"] = MAKE_EAST;
    commands["makesouth"] = MAKE_SOUTH;
    commands["ms"] = MAKE_SOUTH;
    commands["makewest"] = MAKE_WEST;
    commands["mw"] = MAKE_WEST;
    commands["deletenorth"] = DELETE_NORTH;
    commands["dn"] = DELETE_NORTH;
    commands["deleteeast"] = DELETE_EAST;
    commands["de"] = DELETE_EAST;
    commands["deletesouth"] = DELETE_SOUTH;
    commands["ds"] = DELETE_SOUTH;
    commands["deletewest"] = DELETE_WEST;
    commands["dw"] = DELETE_WEST;
    commands["setstart"] = SET_START;
    commands["setend"] = SET_END;
    commands["help"] = HELP;
    commands["h"] = HELP;
    commands["save"] = SAVE_WORLD;
    commands["load"] = LOAD_WORLD;
    commands["exit"] = EXIT;
    commands["x"] = EXIT;
    commands["quit"] = EXIT;
    commands["q"] = EXIT;
}

// loads the world from a file
Result World::load(Room *&rm, Room *source, std::ifstream &in)
{
    Result result = RESULT_SUCCESS;
    std::string buffer;
    
    // read room info
    if (std::getline(in, buffer))
    {
        rm->roomId = std::atoi(buffer.c_str());
        std::getline(in, rm->description);
        
        // check if starting point
        std::getline(in, buffer);
        // test for least common occurrence first
        if (buffer != "notstart")
            start = rm;
        
        // check if end point
        std::getline(in, buffer);
        if (buffer != "notend")
            end = rm;
        
        // north tree
        std::getline(in, buffer);
        if (buffer == "s")
            rm->north = source;
        else if (buffer == "d")
        {
            rm->north = new Room(nextRoomId++);
            load(rm->north, rm, in);
        }
        
        // east tree
        std::getline(in, buffer);
        if (buffer == "s")
            rm->east = source;
        else if (buffer == "d")
        {
            rm->east = new Room(nextRoomId++);
            load(rm->east, rm, in);
        }
        
        // south tree
        std::getline(in, buffer);
        if (buffer == "s")
            rm->south = source;
        else if (buffer == "d")
        {
            rm->south = new Room(nextRoomId++);
            load(rm->south, rm, in);
        }
        
        // west tree
        std::getline(in, buffer);
        if (buffer == "s")
            rm->west = source;
        else if (buffer == "d")
        {
            rm->west = new Room(nextRoomId++);
            load(rm->west, rm, in);
        }
    }
    return result;
}

// saves the world to a file
Result World::save(Room *rm, Direction source, std::ofstream &out)
{
    Result result = RESULT_SUCCESS;
    
    // write room info
    out << rm->roomId << std::endl
        << rm->description << std::endl
        << (rm == start ? "start" : "notstart") << std::endl
        << (rm == end ? "end" : "notend") << std::endl;
    
    // north tree
    if (rm->north == NULL)
        out << '-' << std::endl;
    else if (source == NORTH)
        out << 's' << std::endl;
    else
    {
        out << 'd' << std::endl;
        result = save(rm->north, SOUTH, out);
    }
    // east tree
    if (rm->east == NULL)
        out << '-' << std::endl;
    else if (source == EAST)
        out << 's' << std::endl;
    else
    {
        out << 'd' << std::endl;
        result = save(rm->east, WEST, out);
    }
    // south tree
    if (rm->south == NULL)
        out << '-' << std::endl;
    else if (source == SOUTH)
        out << 's' << std::endl;
    else
    {
        out << 'd' << std::endl;
        result = save(rm->south, NORTH, out);
    }
    // west tree
    if (rm->west == NULL)
        out << '-' << std::endl;
    else if (source == WEST)
        out << 's' << std::endl;
    else
    {
        out << 'd' << std::endl;
        result = save(rm->west, EAST, out);
    }

    return result;
}

// deletes the room in the specified direction and any orphaned rooms
Result World::deleteRoom(Direction d)
{
    Result result = RESULT_SUCCESS;
    switch (d)
    {
    case NORTH:
        if (current->north != NULL)
        {
            // remove return pointer
            current->north->south = NULL;
            
            // delete entire tree starting from node
            deleteTree(current->north);
            delete current->north;
            current->north = NULL;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case EAST:
        if (current->east != NULL)
        {
            // remove return pointer
            current->east->west = NULL;
            
            // delete entire tree starting from node
            deleteTree(current->east);
            delete current->east;
            current->east = NULL;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case SOUTH:
        if (current->south != NULL)
        {
            // remove return pointer
            current->south->north = NULL;
            
            // delete entire tree starting from node
            deleteTree(current->south);
            delete current->south;
            current->south = NULL;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case WEST:
        if (current->west != NULL)
        {
            // remove return pointer
            current->west->east = NULL;
            
            // delete entire tree starting from node
            deleteTree(current->west);
            delete current->west;
            current->west = NULL;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    }
    
    if (result == RESULT_FAILURE)
        std::cout << "No room exists there!\n";
    else
    {
        // make current room new starting point if starting point was deleted
        if (start == NULL)
        {
            std::cout << "Making the current room the new starting point.\n";
            start = current;
        }
    }
    return result;
}

// recursively deletes the entire tree connected to the specified room
World::Room *World::deleteTree(Room *rm)
{
    if (rm->north != NULL)
    {
        // remove return pointer
        rm->north->south = NULL;
        delete deleteTree(rm->north);
    }
    if (rm->east != NULL)
    {
        // remove return pointer
        rm->east->west = NULL;
        delete deleteTree(rm->east);
    }
    if (rm->south != NULL)
    {
        // remove return pointer
        rm->south->north = NULL;
        delete deleteTree(rm->south);
    }
    if (rm->west != NULL)
    {
        // remove return pointer
        rm->west->east = NULL;
        delete deleteTree(rm->west);
    }
    // set start/end point to null if that room is deleted
    if (start == rm)
        start = NULL;
    if (end == rm)
        end = NULL;
    
    return rm;
}

// edits the description of the current room
Result World::editRoom()
{
    std::string input;
    std::cout << "\nEnter a new description or blank to keep the old one.\n: ";
    std::getline(std::cin, input);
    if (!input.empty())
        current->description = input;
    return RESULT_SUCCESS;
}

// creates a new room in the specified direction
Result World::makeRoom(Direction d)
{
    Result result = RESULT_SUCCESS;
    switch (d)
    {
    case NORTH:
        if (current->north == NULL)
        {
            current->north = new Room(nextRoomId++);
            current->north->south = current;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case EAST:
        if (current->east == NULL)
        {
            current->east = new Room(nextRoomId++);
            current->east->west = current;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case SOUTH:
        if (current->south == NULL)
        {
            current->south = new Room(nextRoomId++);
            current->south->north = current;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case WEST:
        if (current->west == NULL)
        {
            current->west = new Room(nextRoomId++);
            current->west->east = current;
        }
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    }
    
    if (result == RESULT_FAILURE)
        std::cout << "\nA room already exists in that direction!\n";
    
    return result;
}

// moves in the specified direction
Result World::move(Direction d)
{
    Result result = RESULT_SUCCESS;
    switch (d)
    {
    case NORTH:
        if (current->north != NULL)
            current = current->north;
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case EAST:
        if (current->east != NULL)
            current = current->east;
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case SOUTH:
        if (current->south != NULL)
            current = current->south;
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    case WEST:
        if (current->west != NULL)
            current = current->west;
        else
        {
            result = RESULT_FAILURE;
        }
        break;
    }
    
    if (result == RESULT_FAILURE)
        std::cout << "\nYou cannot go that direction.\n";
    return result;
}

// displays the help menu
void World::printHelp() const
{
    std::cout << "\nThe following commands are available.\n";
    
    // display editing commands if in edit mode
    if (editMode)
    {
    std::cout << "  edit              : Toggle edit mode\n"
              << "  description (desc): Edit the room description\n"
              << "  makenorth     (mn): Make a room to the North\n"
              << "  makeeast      (me): Make a room to the East\n"
              << "  makesouth     (ms): Make a room to the South\n"
              << "  makewest      (mw): Make a room to the West\n"
              << "  deletenorth   (dn): Delete the room to the North\n"
              << "  deleteeast    (de): Delete the room to the East\n"
              << "  deletesouth   (ds): Delete the room to the South\n"
              << "  deletewest    (dw): Delete the room to the West\n"
              << "  setstart          : Set the starting point of the world\n"
              << "  setend            : Set the end of the world\n";
              
    }
    std::cout << "  north (n): Move to the North\n"
              << "  east  (e): Move to the East\n"
              << "  south (s): Move to the South\n"
              << "  west  (w): Move to the West\n"
              << "  label (l): Toggle label visibility\n"
              << "  help  (h): Show this guide\n"
              << "  exit  (x): Exit the program\n";
}

// runs the specified command
Result World::runCommand(Command c)
{
    Result result = RESULT_SUCCESS;
    switch (c)
    {
    case MOVE_NORTH:    // move one room to the north
        move(NORTH);
        break;
    case MOVE_EAST:     // move one room to the east
        move(EAST);
        break;
    case MOVE_SOUTH:    // move one room to the south
        move(SOUTH);
        break;
    case MOVE_WEST:     // move one room to the west
        move(WEST);
        break;
    case TOGGLE_LABEL:  // toggle the room ID label
        std::cout << "\nToggling room label\n";
        labelVis = !labelVis;
        break;
    case TOGGLE_EDIT:   // toggle edit mode (off by default)
        std::cout << "\nToggling edit mode\n";
        editMode = !editMode;
        break;
    case EDIT_DESC:     // (edit mode) edit the room description
        if (editMode)
            editRoom();
        else
            result = RESULT_FAILURE;
        break;
    case MAKE_NORTH:    // (edit mode) make a room to the north
        if (editMode)
            makeRoom(NORTH);
        else
            result = RESULT_FAILURE;
        break;
    case MAKE_EAST:     // (edit mode) make a room to the east
        if (editMode)
            makeRoom(EAST);
        else
            result = RESULT_FAILURE;
        break;
    case MAKE_SOUTH:    // (edit mode) make a room to the south
        if (editMode)
            makeRoom(SOUTH);
        else
            result = RESULT_FAILURE;
        break;
    case MAKE_WEST:     // (edit mode) make a room to the west
        if (editMode)
            makeRoom(WEST);
        else
            result = RESULT_FAILURE;
        break;
    case DELETE_NORTH:  // (edit mode) delete the room to the north
        if (editMode)
            deleteRoom(NORTH);
        else
            result = RESULT_FAILURE;
        break;
    case DELETE_EAST:   // (edit mode) delete the room to the east
        if (editMode)
            deleteRoom(EAST);
        else
            result = RESULT_FAILURE;
        break;
    case DELETE_SOUTH:  // (edit mode) delete the room to the south
        if (editMode)
            deleteRoom(SOUTH);
        else
            result = RESULT_FAILURE;
        break;
    case DELETE_WEST:   // (edit mode) delete the room to the west
        if (editMode)
            deleteRoom(WEST);
        else
            result = RESULT_FAILURE;
        break;
    case SET_START:     // (edit mode) set starting point to current room
        if (editMode)
        {
            std::cout << "Setting starting point to current room.\n";
            start = current;
        }
        else
            result = RESULT_FAILURE;
        break;
    case SET_END:       // (edit mode) set end point to current room
        if (editMode)
        {
            std::cout << "Setting end point to current room.\n";
            end = current;
        }
        else
            result = RESULT_FAILURE;
        break;
    case HELP:          // (edit mode) display help menu
        printHelp();
        break;
    case SAVE_WORLD:    // (edit mode) save the world
        if (editMode)
        {
            std::cout << "Saving the world to the current directory.\n";
            result = RESULT_SAVE;
        }
        else
            result = RESULT_FAILURE;
        break;
    case LOAD_WORLD:    // (edit mode) load the world
        if (editMode)
        {
            std::cout << "Loading the world from the current directory.\n";
            result = RESULT_LOAD;
        }
        else
            result = RESULT_FAILURE;
        break;
    case EXIT:          // exit the program
        std::cout << "\nAre you sure you want to exit? (y/N): ";
        if (getYesNo())
            result = RESULT_EXIT;
        break;
    }
    if (result == RESULT_FAILURE)
        std::cout << "\nInvalid command. Try again or type 'help' for help.\n";

    return result;
}
    
/******************************************************
*            Constructors and Destructor              *
******************************************************/
World::World()
{
    labelVis = true;    // labels are visible by default
    editMode = false;   // edit mode is off by default
    nextRoomId = 1;     // start room ID at 1
    
    // create first room and set to current
    current = new Room(nextRoomId++);
    start = current;
    end = NULL;
    
    // populate commands
    buildCommandMap();
}

World::~World()
{
    // delete all rooms
    start = deleteTree(start);
    delete start;
    start = NULL;
}

/******************************************************
*              Public Member Functions                *
******************************************************/
// parses user input and runs the specified command
Result World::command(std::string &input)
{
    Result result = RESULT_SUCCESS;
    
    // convert command to lowercase
    input = toLower(input);
    
    // check command map for Command
    std::map<std::string, Command>::iterator iter;
    iter = commands.find(input);
    
    // run the command if found
    if (iter != commands.end())
    {
        result = runCommand(iter->second);
    }
    // otherwise display an error message
    else
    {
        std::cout << "\nInvalid command. Try again or type 'help' for help.\n";
        result = RESULT_FAILURE;
    }
    return result;
}

// displays the current room
void World::printRoom() const
{
    // display room label only if labels are enabled
    if (labelVis)
        std::cout << "\nRoom " << current->roomId << "\n";
    // display description only if not empty
    if (!current->description.empty())
        std::cout << std::endl << current->description << "\n";
    // display if this is starting point
    if (current == start)
        std::cout << "\nThis is where you started your journey.\n"
                  << "Type 'help' or 'h' to display instructions.\n";
    // display if this is the end point
    if (current == end)
        std::cout << "\nCongratulations, you have reached your destination.\n"
                  << "Type 'x' to exit or you may continue to explore.\n";
    // always display available directions
    std::cout << "\nYou can go the following directions: ";
    std::cout << (current->north != NULL ? "North " : "")
              << (current->east != NULL ? "East " : "")
              << (current->south != NULL ? "South " : "")
              << (current->west != NULL ? "West" : "") << "\n\n";
}

// loads the world from the specified file stream
Result World::loadWorld(std::ifstream &in)
{
    if (in)
    {
        load(start, NULL, in);
    }
    else
    {
        std::cout << "Cannot read data file.\n";
    }
}

// saves the world to the specified file stream
Result World::saveWorld(std::ofstream &out)
{
    if (out)
    {
        save(start, NONE, out);
    }
    else
    {
        std::cout << "Cannot save to file.\n";
    }
}
