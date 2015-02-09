/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/30/2015
 * Assignment:      Assignment 2
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
 *  Function:       bool getYesNo()
 *  Description:    Gets input from the user and tests if the first letter
 *                  is 'Y' or 'y'.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Returns true if input starts with 'y' or 'Y'.
 *******************************************************************/
bool getYesNo()
{
    std::string buffer;
    std::getline(std::cin, buffer);
    // test if user did not select 'y'
    if (buffer.empty() || (buffer[0] != 'y' && buffer[0] != 'Y'))
        return false;
    else
        return true;
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
 *  Parameters:     milliseconds    number of milliseconds to sleep
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

/********************************************************************
 *  Function:       std::vector<std::string> split(const std::string &text, char delim)
 *  Description:    Splits a string into substrings based on the specified
 *                  delimiter. Defaults to a space if not specified.
 *  Parameters:     text    number of milliseconds to sleep
 *  Preconditions:  none
 *  Postconditions: Returns a vector containing the substrings.
 *******************************************************************/
std::vector<std::string> split(const std::string &text, char delim)
{
    std::vector<std::string> buffer;
    size_t pos = 0; // find position
    
    while (pos < text.length())
    {
        size_t next = text.find(delim, pos);
        if (next == std::string::npos)
            next = text.length();
        buffer.push_back(text.substr(pos, next - pos));
        pos = next + 1;
    }
    
    return buffer;
}

/********************************************************************
 *  Function:       bool isDouble(const std::string &str)
 *  Description:    This function determines whether a string is a valid
 *                  double. Note that a valid integer is considered to be 
 *                  a valid double.
 *  Parameters:     str     string object to test
 *  Preconditions:  none
 *  Postconditions: Returns true if entire string is valid double.
 ********************************************************************/
bool isDouble(const std::string &str)
{
    // return false if empty
    if (str.length() < 1)
        return false;
    
    bool pointFound = false;
    
    // check each char
    for (int i = 0; i < str.length(); i++)
    {
        if ( !isdigit(str[i]) &&           // not a digit
            (str[i] != '-' || i != 0) &&   // '-' found not at beginning
            (str[i] != '.' || pointFound)  // '.' when one already found
           )
            return false;
        if (str[i] == '.')
            pointFound = true;
    }
    
    // no illegal chars found
    return true;
}

/********************************************************************
 *  Function:       bool isInteger(const std::string &str)
 *  Description:    This function determines whether a string is a valid
 *                  integer.
 *  Parameters:     str     string object to test
 *  Preconditions:  none
 *  Postconditions: Returns true if entire string is valid integer.
 ********************************************************************/
bool isInteger(const std::string &str)
{
    // return false if empty
    if (str.length() < 1)
        return false;
    
    // check each char
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]) && (i != 0 || str[i] != '-'))
            return false;
    }
    
    // no non-digits found
    return true;
}
