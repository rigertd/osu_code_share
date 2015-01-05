/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/7/2014
 * Last Modification Date: 11/7/2014
 * Assignment:             Assignment 6
 * Filename:               wordShift.cpp
 *
 * Overview:
 *     This program prompts the user for a string and then lets
 *     them manipulate it by typing commands.
 * 
 * Input:
 *     The string to manipulate
 *     Commands to manipulate the string:
 *     - 'L#' to shift all of the letters # spaces to the left
 *     - 'R#' to shift all of the letters # spaces to the right
 *     - 'rev' to reverse all of the letters
 *     - 'quit' to exit the program.
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Please enter a string.
 *     [12345678]
 *     Please enter a command.
 *     [L2]
 *     New string: 34567812
 *     [R1]
 *     New string: 23456781
 *     [rev]
 *     New string: 18765432
 *     [quit]
 *********************************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>

// Function prototype
// Validates the L and R commands and returns the number value.
long ParseCommand(const char *);

// Shifts chars in the string 'amt' spaces to the left.
void ShiftLeft(char *, int);

// Shifts chars in the string 'amt' spaces to the right.
void ShiftRight(char *, int);

// Reverses the order of the chars in the string.
void Reverse(char *);

// Converts an entire C-style string to uppercase.
void CStringToUpper(char *);

int main()
{
    const int MAX_SIZE = 31;   // Max chars allowed for user input
    char input[MAX_SIZE] = ""; // Stores user input string
    char cmd[MAX_SIZE];        // Stores menu commands

    // Prompt user for input string
    std::cout << "Please enter a string.\n";
    std::cin.getline(input, MAX_SIZE);
    
    // Validate user input
    while (std::strlen(input) < 1)
    {
        // Clear the failbit flag
        std::cin.clear();

        // Re-prompt user for valid input.
        std::cout << "Your string must contain at least one character. "
                  << "Try again.\n";
        std::cin.getline(input, MAX_SIZE);
    }

    // Start of menu do-while loop
    do
    {
        // Clear any leftover text in input buffer
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        
        // Prompt user for command
        std::cout << "Please enter a command.\n";
        std::cin.getline(cmd, MAX_SIZE);
        
        // Convert command to uppercase
        CStringToUpper(cmd);
        
        // Get command value, if any
        int val = ParseCommand(cmd);
        
        // Handle command
        if (cmd[0] == 'L' && val > -1)      // Shift to left
        {
            ShiftLeft(input, val);
            std::cout << "New string: " << input << "\n";
        }
        else if (cmd[0] == 'R' && val > -1) // Shift to right
        {
            ShiftRight(input, val);
            std::cout << "New string: " << input << "\n";
        }
        else if (strcmp(cmd, "REV") == 0)   // Reverse chars
        {
            Reverse(input);
            std::cout << "New string: " << input << "\n";
        }
        else if (strcmp(cmd, "QUIT") != 0)  // Invalid command
        {
            std::cout << "Invalid command.\nYour string is: "
                      << input << "\n";
        }
    } while (strcmp(cmd, "QUIT") != 0);
    
    return 0;
}

/**********************************************************
 *  long ParseCommand(const char *cmd)
 *
 *  Purpose: This function gets the number value of a command.
 *
 *  Preconditions: Command is 1 letter followed by numbers
 *   
 *  Postconditions: Returns the value of the numbers, or -1 if 0 or none
 *********************************************************/
long ParseCommand(const char *cmd)
{
    int len = std::strlen(cmd); // Length of command string
    int val = -1;               // Default value is invalid
    
    // Increment pointer by 1 to see if rest of command is number
    cmd++;
    val = std::strtol(cmd, 0, 10);
    
    // Set val to -1 if there was no number
    if (val == 0)
        val = -1;

    return val;
}

/**********************************************************
 *  void ShiftLeft(char *pText, int amt)
 *
 *  Purpose: This function shifts chars in the string to the left
 *           by 'amt' spaces.
 *
 *  Preconditions: pText is not empty and amt >= 0
 *   
 *  Postconditions: pText is shifted to the left by 'amt' spaces
 *********************************************************/
void ShiftLeft(char *pText, int amt)
{
    int len = std::strlen(pText); // length of string
    int relShift = amt % len;     // actual shift if larger than len
    char temp;                    // temp var for swapping
    
    // Shift one char relShift times
    for (int i = 0; i < relShift; i++)
    {
        temp = pText[0];
        // Shift each char to the left by 1
        for (int j = 1; j < len; j++)
        {
            pText[j - 1] = pText[j];
        }
        pText[len - 1] = temp;
    }
}

/**********************************************************
 *  void ShiftRight(char *pText, int amt)
 *
 *  Purpose: This function shifts chars in the string to the right
 *           by 'amt' spaces.
 *
 *  Preconditions: pText is not empty and amt >= 0
 *   
 *  Postconditions: pText is shifted to the right by 'amt' spaces
 *********************************************************/
void ShiftRight(char *pText, int amt)
{
    int len = std::strlen(pText); // length of string
    int relShift = amt % len;     // actual shift if larger than len
    char temp;                    // temp var for swapping
    
    // Shift one char relShift times
    for (int i = 0; i < relShift; i++)
    {
        temp = pText[len - 1];
        // Shift each char to the right by 1
        for (int j = len - 1; j > 0; j--)
        {
            pText[j] = pText[j - 1];
        }
        pText[0] = temp;
    }
}

/**********************************************************
 *  void ShiftLeft(char *pText)
 *
 *  Purpose: This function reverses the order of the chars in the string.
 *
 *  Preconditions: pText is not empty
 *   
 *  Postconditions: The order of the chars in pText is reversed
 *********************************************************/
void Reverse(char *pText)
{
    int len = std::strlen(pText); // length of string
    char temp;                    // temp var for swapping
    
    // Only go half way and stop (working from both ends)
    for (int i = 0; i < (len / 2); i++)
    {
        temp = pText[i];
        pText[i] = pText[len - 1 - i];
        pText[len - 1 - i] = temp;
    }
}

/**********************************************************
 *  void CStringToUpper(char *pText)
 *
 *  Purpose: This function converts an entire C-style string to uppercase.
 *
 *  Preconditions: None
 *   
 *  Postconditions: The specified string is converted to uppercase.
 *********************************************************/
void CStringToUpper(char *pText)
{
    int len = std::strlen(pText);
    for (int i = 0; i < len; i++)
    {
        if (pText[i] >= 'a' && pText[i] <= 'z')
            pText[i] = pText[i] - 32;
    }
}

