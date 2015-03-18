/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/15/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               Player.cpp
 *
 * Overview:
 *     Implementation for the Player class.
 ************************************************************************/
#include "Player.hpp"

#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <string>

#include "Item.hpp"
#include "Room.hpp"
#include "World.hpp"

// constructor - default global pointer is NULL
Player::Player(World *w)
{
    global = w;
}

// constructor - default weight = 100 lbs, default size = 10, default quantity = 5
Player::Player(World *w, Room *location, unsigned weight, unsigned size, unsigned quantity)
{
    this->global = w;
    this->location = location;
    this->weightLimit = weight;
    this->maxSize = size;
    this->maxQuantity = quantity;
}

// drop the item with the specified ID in inventory
Result Player::dropItem(unsigned id)
{
    Result res(Result::SUCCESS);
    // check for ID in inventory
    std::map<unsigned, Item *>::iterator it = inventory.find(id);
    if (it != inventory.end())
    {
        // add item to Room
        res = location->addItem(it->second);
        // remove item from inventory if successful
        if (res.type == Result::SUCCESS)
        {
            res.message = "You dropped your " + it->second->getName() + ".";
            inventory.erase(it);
        }
    }
    else    // item ID not found
    {
        res.type = Result::FAILURE;
        res.message = "You are not carrying that item.";
    }
    return res;
}

// get the combined weight of all items in inventory
int Player::getInventoryWeight()
{
    int total = 0;  // accumulator
    std::map<unsigned, Item *>::iterator it = inventory.begin();
    while (it != inventory.end())
    {
        total += it->second->getWeight();
        it++;
    }
    
    return total;
}

// move in the specified direction
Result Player::move(Direction d)
{
    Result res(Result::SUCCESS);
    
    // get pointer to room in specified direction
    Room *dest = location->getExit(d);
    // check for NULL pointer
    if (dest)
    {
        // set current location to destination
        location = dest;
    }
    else
    {
        res.type = Result::FAILURE;
        res.message = "You cannot go that way.";
    }
    
    return res;
}

// pick up the item with the specified ID in the current location
Result Player::take(unsigned id)
{
    Result res(Result::FAILURE);
    // see if item is in current location
    Item *itm = location->findItem(id);
    if (itm)
    {
        if (itm->getSize() > maxSize)
        {
            res.message = "That is too big to fit in your bag.";
        }
        else if (itm->getWeight() + getInventoryWeight() > weightLimit)
        {
            res.message = "You are too encumbered to pick that up.";
        }
        else if (inventory.size() >= maxQuantity)
        {
            res.message = "Your bag is already full. Drop something first.";
        }
        else
        {
            // remove item from room
            res = location->removeItem(id);
            // add to inventory if successful
            if (res.type == Result::SUCCESS)
            {
                inventory[id] = itm;
                res.message = "You picked up the " + itm->getName() + ".";
            }
        }
    }
    else
    {
        res.message = "There is no such item here.";
    }
    
    return res;
}

// use an item with the specified ID in inventory or in the room
Result Player::useItem(unsigned id)
{
    Result res(Result::FAILURE);
    Item *itm = NULL;
    
    // check if item is in inventory
    std::map<unsigned, Item *>::iterator it = inventory.find(id);
    if (it != inventory.end())
    {
        itm = it->second;
        res = location->useItem(itm);
    }
    else
    {
        res = location->useItem(id);
    }
    
    return res;
}

// view all items in inventory
void Player::viewItems()
{
    std::map<unsigned, Item *>::iterator it = inventory.begin();

    if (inventory.size() > 0)
        std::cout << "Your bag contains the following items:" << std::endl;
    else
        std::cout << "You are not carrying anything right now." << std::endl;
    
    // list all items and the ID number
    while (it != inventory.end())
    {
        std::cout << "  " << it->second->getName() 
                  << " (ID: " << it->second->getId() << ", " 
                  << "weight: " << it->second->getWeight() << ")" << std::endl;
        it++;
    }
    
    std::cout << "\nTotal weight:   " << getInventoryWeight() << "/" 
              << weightLimit << " lbs max"
              << "\nTotal quantity: " << inventory.size() << "/" 
              << maxQuantity << " items max" << std::endl;
}

// for configuring object with save data
void Player::deserialize(std::istream &in)
{
    std::string input;      // input buffer
    
    // get weightLimit
    std::getline(in, input);
    weightLimit = std::atoi(input.c_str());
    
    // get maxSize
    std::getline(in, input);
    maxSize = std::atoi(input.c_str());
    
    // get maxQuantity
    std::getline(in, input);
    maxQuantity = std::atoi(input.c_str());
    
    // get player inventory
    std::getline(in, input);
    std::istringstream iss(input);
    unsigned id = 0;
    while (iss >> id)
    {
        Item *itm = global->findItem(id);
        if (itm)
            inventory[id] = itm;
    }
}

std::ostream &operator<<(std::ostream &out, Player &plr)
{
    // output weight limit
    out << plr.weightLimit << std::endl;
    
    // output max item size
    out << plr.maxSize << std::endl;
    
    // output max inventory quantity
    out << plr.maxQuantity << std::endl;
    
    // output item IDs on one line
    std::map<unsigned, Item *>::iterator it = plr.inventory.begin();
    while (it != plr.inventory.end())
    {
        out << it->first << ' ';
        ++it;
    }
    out << std::endl;
    
    return out;
}
