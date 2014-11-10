/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/6/2014
 * Last Modification Date: 11/6/2014
 * Assignment:             Assignment 6
 * Filename:               stringMix.cpp
 *
 * Overview:
 *     This program prompts the user for a string, randomly shuffles 
 *     the characters, and displays the shuffled string to the user.
 * 
 * Input:
 *     String to shuffle
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Enter a string to shuffle: [fizz buzz]
 *
 *     Shuffling fizz buzz.
 *     
 *     Your shuffled string is fbzzz uzi. (different every time)
 *
 *     Shuffle the string again? (Y/N): [n]
 *********************************************************/
#include <iostream> // for cin/cout
#include <ctime>    // for time()
#include <cstdlib>  // for rand()
#include <string>   // for prompt
#include <cstring>  // for strlen()

// Function prototype
// Shuffles the chars in the first c string and stores them in the second.
void ShuffleString(const char *, char *);

// Prompts user for yes/no answer and returns true if yes/no
bool GetYesNo(std::string);

int main()
{
    const int MAX_STRING = 30;        // maximum input string length
    
    unsigned int seed = std::time(0); // seed value for rand
    
    char input[MAX_STRING],           // c string for storing user input
         shuffled[MAX_STRING] = "";   // c string for storing shuffled string
    
    // seed the pseudorandom number generator
    srand(seed);
    
    // Prompt user for a string.
    std::cout << "Enter a string to shuffle: ";
    std::cin.getline(input, MAX_STRING);
    
    // Shuffle loop
    do
    {
        std::cout << "\nShuffling " << input << ".\n";
        ShuffleString(input, shuffled);
        
        // Display result
        std::cout << "\nYour shuffled string is " << shuffled << ".\n";
    }
    while (GetYesNo("\nShuffle the string again? (Y/N): "));
    
    return 0;
}

/**********************************************************
 *  void ShuffleString(const char *source, char *target)
 *
 *  Purpose: This function randomly shuffles the order of the chars 
 *           in the first c string and stores them in the second c string.
 *
 *  Preconditions: both c strings are of the same length
 *   
 *  Postconditions: shuffled string stored in target
 *********************************************************/
void ShuffleString(const char *source, char *target)
{
    // Make sure source and target arrays are same length
    if (sizeof(source) != sizeof(target))
        return;

    // Get actual length of source string
    int sourceLen = std::strlen(source);
    
    // sets first sourceLen + 1 chars of target to NULL
    for (int i = 0; i <= sourceLen; i++)
    {
        target[i] = 0;
    }
    
    // Assign each character to random subscript
    for (int i = 0; i < sourceLen; i++)
    {
        // get random number between 0 and sourceLen
        int r = rand() % sourceLen;
        
        // keep trying until empty index is found
        while (target[r] != 0)
        {
            r = rand() % sourceLen;
        }
        
        // assign current subscript to random subscript
        target[r] = source[i];
    }
}

/**********************************************************
 *  bool GetYesNo(std::string prompt)
 *
 *  Purpose: This function displays the specified prompt
 *           until the first char of the input is
 *           'Y', 'y', 'N', or 'n'.
 *
 *  Preconditions: None.
 *   
 *  Postconditions: Leaves the input buffer empty 
 *                  and returns true if 'y' or 'Y'.
 *********************************************************/
bool GetYesNo(std::string prompt)
{
    char input; // for storing user input
    
    std::cout << prompt;
    std::cin >> input;
    
    // Flushes buffer and prompts for another value until
    // a valid value is entered.
    while (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
    {
        std::cout << "Please type yes or no: ";
        std::cin.clear();     // Clear any errors.
        std::cin.sync();      // Clear any text left in buffer.
        std::cin >> input;    // Store console input in 'input' variable.
    }
    
    // Clear any errors and text left in buffer.
    std::cin.clear();
    std::cin.sync();

    return input == 'Y' || input == 'y';
}
