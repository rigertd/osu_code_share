/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/6/2014
 * Last Modification Date: 11/6/2014
 * Assignment:             Assignment 6
 * Filename:               evenOdd.cpp
 *
 * Overview:
 *     This program prompts the user for a number of integer values 
 *     and returns the difference of the even values and the odd values.
 * 
 * Input:
 *     Number of values to enter
 *     Specified number of integer values
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Enter the number of integers to input, up to 50: [4]
 *
 *     Enter 3 integers, separated by spaces: [1 2 3 4]
 *     
 *     Even values minus odd values is 2.
 *********************************************************/
#include <iostream>

// Function prototype
// Returns the difference of the even and odd numbers in an array.
int GetEvenMinusOdd(const int *, const int);

int main()
{
    int arrSize = 0;         // will hold actual number entered by user
    const int MAX_SIZE = 50; // as instructed. don't dock me, bro!
    
    // Prompt user and get array size.
    std::cout << "Enter the number of integers to input, up to 50: ";
    std::cin >> arrSize;
    
    // Validate input.
    while (std::cin.fail() || arrSize < 1 || arrSize > MAX_SIZE)
    {
        std::cin.clear(); // remove error bit
        std::cin.sync();  // clear input buffer
        std::cout << "Your number must be between 1 and 50: ";
        std::cin >> arrSize;
    }
    
    // Allocate memory for new array in heap
    int *inputArrPtr = new int[arrSize];
    
    // Populate array
    int i = 0;
    std::cout << "\nEnter " << arrSize 
              << " integers, separated by spaces: ";
    while (i < arrSize)
    {
        std::cin >> inputArrPtr[i++];
    }
    
    // Display result
    std::cout << "\nEven values minus odd values is "
              << GetEvenMinusOdd(inputArrPtr, arrSize) << ".\n";

    return 0;
}

/**********************************************************
 *  int GetEvenMinusOdd(const int *arr, const int size)
 *
 *  Purpose: This function returns the difference of the even
 *           and odd values in the specified array.
 *
 *  Preconditions: size = elements in array
 *   
 *  Postconditions: Returns even numbers - odd numbers
 *********************************************************/
int GetEvenMinusOdd(const int *arr, const int size)
{
    int difference = 0;
    
    // Add even values and subtract odd values.
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
            difference += arr[i];
        else
            difference -= arr[i];
    }
    
    return difference;
}