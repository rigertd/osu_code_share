/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        utility.cpp
 *
 * Description:     Implementations of the utility functions. 
 ************************************************************************/
#include <iostream>
#include <limits>
#include "utility.hpp"

// Include unix header if running on Linux
#if defined(__linux__)
#include <unistd.h>
#endif

// Include Windows header if running on Windows
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/********************************************************************
 *  Function:       void clearInputBuffer()
 *  Description:    Clears the keyboard buffer in the console window.
 *  Parameters:     none
 *  Preconditions:  Keyboard buffer has input (or blocks until input received).
 *  Postconditions: Keyboard buffer and fail bit are cleared.
 *******************************************************************/
void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/********************************************************************
 *  Function:       void clearWindow()
 *  Description:    Clears the console window.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Console window is cleared and cursor is at top-left.
 *******************************************************************/
void clearWindow()
{
    // Clear window in Linux terminal using ANSI escape codes
    #if defined(__linux__)
    // clear screen
    std::cout << "\033[2J";
    // move cursor to top-left
    std::cout << "\033[1;1H";
    #endif
    
    // Clear window in Windows using cls command
    #if defined(_WIN32) || defined(_WIN64)
    system("cls");
    #endif
}

/********************************************************************
 *  Function:       void moveCursorToTopLeft()
 *  Description:    Moves the cursor to the top-left corner of the console.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Cursor is at top-left corner of console window.
 *******************************************************************/
void moveCursorToTopLeft()
{
    // Clear window in Linux terminal using ANSI escape codes
    #if defined(__linux__)
    // move cursor to top-left
    std::cout << "\033[1;1H";
    #endif
    
    // Place cursor in top-left position
    #if defined(_WIN32) || defined(_WIN64)
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(screen, position);
    #endif
}

/********************************************************************
 *  Function:       void sleepMilliseconds(int milliseconds)
 *  Description:    Sleeps for the specified number of milliseconds.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: none
 *******************************************************************/
void sleepMilliseconds(int milliseconds)
{
    #if defined(__linux__)
    unsigned int microseconds = milliseconds * 1000;
    usleep(microseconds);
    #endif

    #if defined(_WIN32) || defined(_WIN64)
    Sleep(milliseconds);
    #endif
}
