/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/13/2015
 * Last Modification Date: 3/15/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Command.cpp
 *
 * Overview:
 *     Represents a command and an optional argument.
 ************************************************************************/
#include "Command.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

// populate command map
Command::CommandMap Command::commands = Command::populateCommands();

Command::Command(Command::CommandType type, const char *description, bool editMode)
{
    this->type = type;
    this->desc = description;
    this->edit = editMode;
}

// prints all available commands
void Command::printCommands(bool showEdit)
{
    CommandMap::iterator it = commands.begin();
    while (it != commands.end())
    {
        if (!it->second.edit || showEdit)
            std::cout << "  " << std::setw(13) << std::left << it->first
                      << it->second.desc << std::endl;
        it++;
    }
}

// reads user input configures the command object
Result Command::read(const std::string &input, bool editMode)
{
    Result res;
    
    // clear current values
    this->argument.clear();
    this->desc.clear();
    this->type = INVALID_COMMAND;
    this->edit = false;
    
    // test for empty input
    if (input.empty())
    {
        this->type = INVALID_COMMAND;
        this->argument.clear();
        res.message = "You did not enter any command.";
        res.type = Result::FAILURE;
        return res;
    }
    std::string lower = input;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    std::istringstream iss(lower);  // for tokenizing input
    std::string cmd;                // token buffer
    std::map<std::string, Command>::iterator it;    // iterator for map
    
    // read first token
    iss >> cmd;
    // search map for token
    it = commands.find(cmd);
    if (it != commands.end()    // get command if it was found AND
        && (it->second.type == Command::WORLD_EDIT // is the edit command OR
            || !it->second.edit                    // is not an edit mode command OR
            || editMode))                           // editMode is on
    {
        *this = it->second;
        
        // clear buffer
        cmd.clear();
        // get next char from buffer (space or LF)
        iss.get();
        // get argument if any
        std::getline(iss, cmd);
        this->argument = cmd;
        
        // command successfully read
        res.type = Result::SUCCESS;
    }
    else
    {
        // unable to read command
        this->type = INVALID_COMMAND;
        this->argument.clear();
        res.message = "I don't know how to do that.";
        res.type = Result::FAILURE;
        
    }
    return res;
}

// fills a command map with command strings and corresponding command objects
Command::CommandMap Command::populateCommands()
{
    CommandMap result;
    result["north"] = Command(ROOM_MOVE_NORTH, "Move to the north.", false);
    result["n"] = Command(ROOM_MOVE_NORTH, "Move to the north.", false);
    result["east"] = Command(ROOM_MOVE_EAST, "Move to the east.", false);
    result["e"] = Command(ROOM_MOVE_EAST, "Move to the east.", false);
    result["south"] = Command(ROOM_MOVE_SOUTH, "Move to the south.", false);
    result["s"] = Command(ROOM_MOVE_SOUTH, "Move to the south.", false);
    result["west"] = Command(ROOM_MOVE_WEST, "Move to the west.", false);
    result["w"] = Command(ROOM_MOVE_WEST, "Move to the west.", false);
    result["take"] = Command(ITEM_TAKE, "Pick up an item.", false);
    result["drop"] = Command(ITEM_DROP, "Drop an item.", false);
    result["use"] = Command(ITEM_USE, "Use an item here.", false);
    result["create"] = Command(ITEM_CREATE, "Create a new item.", true);
    result["delitem"] = Command(WORLD_DELETE_ITEM, "Delete specified item ID", true);
    result["inventory"] = Command(PLAYER_INVENTORY, "View inventory.", false);
    result["inv"] = Command(PLAYER_INVENTORY, "View inventory.", false);
    result["maxquantity"] = Command(PLAYER_MAX_QUANTITY, "Set number of items that fit in bag.", true);
    result["maxsize"] = Command(PLAYER_MAX_SIZE, "Set largest item that fits in bag.", true);
    result["maxweight"] = Command(PLAYER_MAX_WEIGHT, "Set heaviest item that fits in bag.", true);
    result["dn"] = Command(ROOM_DELETE_NORTH, "Delete exit to north.", true);
    result["de"] = Command(ROOM_DELETE_EAST, "Delete exit to east.", true);
    result["ds"] = Command(ROOM_DELETE_SOUTH, "Delete exit to south.", true);
    result["dw"] = Command(ROOM_DELETE_WEST, "Delete exit to west.", true);
    result["desc"] = Command(ROOM_EDIT_DESC, "Edit the room description.", true);
    result["description"] = Command(ROOM_EDIT_DESC, "Edit the room description.", true);
    result["mn"] = Command(ROOM_MAKE_NORTH, 
                        "Make exit to north. Optional arg of room ID, 'cond' or 'switch'.", true);
    result["me"] = Command(ROOM_MAKE_EAST, 
                        "Make exit to east. Optional arg of room ID, 'cond' or 'switch'.", true);
    result["ms"] = Command(ROOM_MAKE_SOUTH, 
                        "Make exit to south. Optional arg of room ID, 'cond' or 'switch'.", true);
    result["mw"] = Command(ROOM_MAKE_WEST, 
                        "Make exit to west. Optional arg of room ID, 'cond' or 'switch'.", true);
    result["setrequired"] = Command(ROOM_SET_REQUIRED, "Set item required to toggle room.", true);
    result["settarget"] = Command(ROOM_SET_TARGET, "Set room to toggle when item is used.", true);
    result["clearreq"] = Command(ROOM_CLEAR_REQUIRED, "Clear item required to toggle room.", true);
    result["cleartar"] = Command(ROOM_CLEAR_TARGET, "Clear room to toggle when item is used.", true);
    result["toggle"] = Command(ROOM_TOGGLE, "Toggle state of current room.", true);
    result["tn"] = Command(ROOM_ENABLE_NORTH, "Enable toggle to north.", true);
    result["te"] = Command(ROOM_ENABLE_EAST, "Enable toggle to east.", true);
    result["ts"] = Command(ROOM_ENABLE_SOUTH, "Enable toggle to south.", true);
    result["tw"] = Command(ROOM_ENABLE_WEST, "Enable toggle to west.", true);
    result["clean"] = Command(WORLD_CLEAN, "Clean up unused rooms and items.", true);
    result["delroom"] = Command(WORLD_DELETE_ROOM, "Delete specified room ID.", true);
    result["edit"] = Command(WORLD_EDIT, "Toggle edit mode.", true);
    result["listitems"] = Command(WORLD_ITEM_LIST, "List all items in world.", true);
    result["listrooms"] = Command(WORLD_ROOM_LIST, "List all rooms in world.", true);
    result["save"] = Command(WORLD_SAVE, "Save the current world.", true);
    result["setend"] = Command(WORLD_SET_END, "Set current room to end point.", true);
    result["setintro"] = Command(WORLD_SET_INTRO, "Set introduction displayed at start.", true);
    result["setstart"] = Command(WORLD_SET_START, "Set current room to start point.", true);
    result["timelimit"] = Command(WORLD_SET_TIME, "Set time limit to find end point.", true);
    result["h"] = Command(COMMAND_HELP, "Display all available commands.", false);
    result["help"] = Command(COMMAND_HELP, "Display all available commands.", false);
    result["exit"] = Command(WORLD_EXIT, "Exit the game.", false);
    result["quit"] = Command(WORLD_EXIT, "Exit the game.", false);
    return result;
}
