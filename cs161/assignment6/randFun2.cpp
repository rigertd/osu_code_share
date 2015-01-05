/**********************************************************
 * Author:                 David Rigert
 * Date Created:           10/21/2014
 * Last Modification Date: 11/6/2014
 * Assignment:             Assignment 6
 * Filename:               randFun2.cpp
 *
 * Overview:
 *     This program gets two numbers from the user,
 *     generates a random number in between them,
 *     and prints the result to the console.
 * 
 * Input:
 *     Two integer values representing the minimum and maximum number
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Enter the smallest desired whole number: [1]
 *     Enter the largest desired whole number: [100]
 *
 *     Your randomly picked number is 49. (different every time)
 *********************************************************/
#include <ctime>    // For time (as seed)
#include <iostream> // For cout
#include <cstdlib>  // For rand and srand
#include <string>   // For string class
#include <limits>   // For numeric_limits

// Function prototypes

// Generates a random int between min and max and sets the 3rd param.
void rand_int(const int *, const int *, int *);

// Prompts the user for min and max values.
void GetMinAndMax(int &, int &);

// Prompts the user for a valid integer and returns it.
int GetValidatedInt(std::string);

int main()
{
    int maxNum;          // Maximum random number
    int minNum;          // Minimum random number
    int randNum;         // Generated random number
    unsigned int seed;   // seed for srand function

    seed = std::time(0); // Set seed value to seconds since epoch
    std::srand(seed);    // Set the seed value for rand
    
    // Get valid user input
    GetMinAndMax(minNum, maxNum);
    // Get random number
    rand_int(&minNum, &maxNum, &randNum);
    
    // Print the randomly generated number
    std::cout << std::endl << "Your randomly picked number is "
              << randNum << "." << std::endl;

    return 0;
}

/**********************************************************
 *  void rand_int(const int *min, const int *max, int *val)
 *
 *  Purpose: This function generates a random number between
 *           the values pointed to by min and max and assigns 
 *           it to the memory address pointed to by val.
 *
 *  Preconditions: Seed is set for rand() and *min <= *max.
 *   
 *  Postconditions: a random number between *min and *max
 *                  is stored in *val.
 *********************************************************/
void rand_int(const int *min, const int *max, int *val)
{
    *val = rand() % (*max + 1 - *min) + *min;
}

/**********************************************************
 *  void GetMinAndMax(int &min, int &max)
 *
 *  Purpose: This function prompts the user for the minimum 
 *           and maximum values of a range of integers.
 *
 *  Preconditions: None.
 *   
 *  Postconditions: min and max are set to the specified 
 *                  input values and min <= max.
 *********************************************************/
void GetMinAndMax(int &min, int &max)
{
    min = GetValidatedInt("Enter the smallest desired whole number: ");
    max = GetValidatedInt("Enter the largest desired whole number: ");

    // Make sure max >= min
    while (max < min)
    {
        std::cout << "The largest number must be at least as large "
                  << "as the smallest." << std::endl;
                  
        // Get new maxNum
        max = GetValidatedInt("Enter the largest desired whole number: ");
    }

}

/**********************************************************
 *  int GetValidatedInt(std::string prompt)
 *
 *  Purpose: This function displays the specified prompt
 *           and gets a valid integer from the user.
 *
 *  Preconditions: None.
 *   
 *  Postconditions: Leaves the input buffer empty 
 *                  and returns an integer value.
 *********************************************************/
int GetValidatedInt(std::string prompt)
{
    int input = 0; // for storing user input
    
    std::cout << prompt;
    std::cin >> input;
    
    /* Implements validation by detecting the next char in the cin buffer.
     * Unless the next char is a newline, 
     * it means there is unused data still in the buffer.
     */
    while (std::cin.get() != '\n') // true if next char not newline
    {
        std::cout << std::endl << "That is not a valid number." << std::endl
                  << "Please enter a whole number between "
                  << std::numeric_limits<int>::min() << " and " // Min int
                  << std::numeric_limits<int>::max()  // Max int
                  << std::endl << "without any commas: ";
        std::cin.clear();     // Clear any errors.
        std::cin.sync();      // Ignore any remaining input in buffer.
        std::cin >> input;    // Store console input in 'input' variable.
    }
    
    return input; // Send the input value back to the caller.
}
