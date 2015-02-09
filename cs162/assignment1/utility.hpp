/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        utility.hpp
 *
 * Description:     A collection of utility functions for common tasks. 
 ************************************************************************/
#ifndef UTILITY_HPP
#define UTILITY_HPP

// Clears the keyboard buffer in the console window.
void clearInputBuffer();

// Clears the console window.
void clearWindow();

// Moves the cursor to the top-left corner of the console.
void moveCursorToTopLeft();

// Sleeps for the specified number of milliseconds.
void sleepMilliseconds(int);

#endif // end of define UTILITY_HPP