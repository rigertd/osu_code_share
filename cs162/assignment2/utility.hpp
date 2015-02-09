/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/31/2015
 * Assignment:      Assignment 2
 * Filename:        utility.hpp
 *
 * Description:     A collection of utility functions for common tasks. 
 ************************************************************************/
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>

// Clears the keyboard buffer in the console window.
void clearInputBuffer();

// Clears the console window.
void clearWindow();

// Gets terminal input and returns true if starts with 'y'.
bool getYesNo();

// Moves the cursor to the top-left corner of the console.
void moveCursorToTopLeft();

// Sleeps for the specified number of milliseconds.
void sleepMilliseconds(int);

// Splits a string on the specified delimiter.
std::vector<std::string> split(const std::string &, char = ' ');

// Determines whether a string is a valid double.
bool isDouble(const std::string &);

// Determines whether a string is a valid integer.
bool isInteger(const std::string &);

#endif // end of define UTILITY_HPP