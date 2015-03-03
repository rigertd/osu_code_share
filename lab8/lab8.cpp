/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           2/28/2015
 * Last Modification Date: 3/1/2015
 * Course:                 CS162_400
 * Assignment:             Lab 8
 * Filename:               lab8.cpp
 *
 * Overview:
 *     This program uses a linked structure to represent a maze that the
 *     user must navigate. From each room, the user can move in one or more
 *     of 4 possible directions: east, west, north, or south. One room in
 *     the maze will contain the exit.
 *     Each room will have an optional room label for ease of navigation.
 *     The display of these labels can be toggled. 
 *
 * Input:
 *     n or north - Move to the North
 *     e or east  - Move to the East
 *     s or south - Move to the South
 *     w or west  - Move to the West
 *     x or exit  - Give up and exit
 *     h or help  - Show the available commands
 *
 * Output:
 *     Iterations and microseconds required for specified search/sort algorithm
 ************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#include "utility.hpp"
#include "World.hpp"

int main()
{
    World w;
    Result result;
    std::string input;
    
    // load world data if found
    std::ifstream in("world.dat");
    if (in)
    {
        w.loadWorld(in);
    }
    in.close();
    
    // game loop
    do
    {
        w.printRoom();
        std::cout << "Where do you want to go?\n: ";
        std::getline(std::cin, input);
        result = w.command(input);
        
        // check for save command
        if (result == RESULT_SAVE)
        {
            std::ofstream out("world.dat");
            w.saveWorld(out);
            out.close();
        }
    } while (result != RESULT_EXIT);
    
    return 0;
}
