/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           3/14/2015
 * Last Modification Date: 3/15/2015
 * Course:                 CS162_400
 * Assignment:             Final Project
 * Filename:               final.hpp
 *
 * Overview:
 *     The main function for creating the World object to run the game.
 *     Type 'help' in game for a list of available commands.
 ************************************************************************/
#include <iostream>
#include "World.hpp"

int main()
{
    World game;
    game.run();
    return 0;
}