/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/13/2015
 * Last Modification Date: 3/15/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Item.cpp
 *
 * Overview:
 *     Implementation for the Item class.
 ************************************************************************/
#include "Item.hpp"

#include <cstdlib>

// starting value for Item ID
unsigned Item::nextId = 1;

// constructor
Item::Item(std::string name, int size, int weight)
{
    id = nextId++;
    this->realName = name;
    this->names.insert(name);
    this->size = size;
    this->weight = weight;
}
Item::Item(unsigned id)
{
    this->id = id;
    nextId = id < nextId ? nextId : (id + 1);
}

// adds a name to the list of acceptable names
void Item::addName(std::string name)
{
    // set realName to first name added if not already set
    if (realName.empty())
        realName = name;
    // add to list of acceptable names
    names.insert(name);
}

// for configuring object with save data
void Item::deserialize(std::istream &in)
{
    std::string input;          // input buffer
    
    // get names
    std::getline(in, input);    // heading
    std::getline(in, input);    // realName
    while (input != "##ENDITEMNAMES##")
    {
        addName(input);
        std::getline(in, input);
    }
    
    // get description
    std::getline(in, input);
    desc = input;
    
    // get size
    std::getline(in, input);
    size = std::atoi(input.c_str());
    
    // get weight
    std::getline(in, input);
    weight = std::atoi(input.c_str());
}

// determines whether a string is an acceptable name
bool Item::hasName(std::string name)
{
    std::set<std::string>::iterator it = names.find(name);
    return it != names.end();
}

// overloaded stream insertion for serialization
std::ostream &operator<<(std::ostream &out, Item &itm)
{
    // output item ID
    out << itm.id << std::endl;
    
    // output real name followed by alternate names
    out << "##ITEMNAMES##" << std::endl;
    out << itm.realName << std::endl;
    std::set<std::string>::iterator it = itm.names.begin();
    while (it != itm.names.end())
    {
        out << *it << std::endl;
        ++it;
    }
    out << "##ENDITEMNAMES##" << std::endl;
    
    // output description
    out << itm.desc << std::endl;
    
    // output size
    out << itm.size << std::endl;
    
    // output weight
    out << itm.weight << std::endl;
    
    return out;
}
