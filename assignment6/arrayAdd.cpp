/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/7/2014
 * Last Modification Date: 11/7/2014
 * Assignment:             Assignment 6
 * Filename:               arrayAdd.cpp
 *
 * Overview:
 *     This program prompts the user for the size of two arrays
 *     and the values in each array, adds values at the same index
 *     of each array, and displays the results.
 * 
 * Input:
 *     Number of values to enter in each array
 *     Specified number of integer values for each array
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     This program adds each of the numbers in one sequence
 *     to the same position in another sequence.
 *
 *     Enter the number of integers in each sequence: [4]
 *
 *     Enter 4 integers for the 1st sequence, separated by spaces: [1 2 3 4]
 *     Enter 4 integers for the 2nd sequence, separated by spaces: [3 2 1 0]
 *     
 *     The sum produces the following sequence: (4, 4, 4, 4)
 *********************************************************/
#include <iostream>
#include <string>

// Function prototype
// Stores the sum of each element in the first 2 arrays in the 3rd.
void AddArrays(const int *, const int *, int *);

int main()
{
    int arrSize = 0;         // will hold actual number entered by user
    const int MAX_SIZE = 50; // as instructed. don't dock me, bro!
    
    // Display program description.
    std::cout << "This program adds each of the numbers in one sequence\n"
              << "to the same position in another sequence.\n\n";
    
    // Prompt user and get array size.
    std::cout << "Enter the number of integers in each sequence, up to 50: ";
    std::cin >> arrSize;
    
    // Validate input.
    while (std::cin.fail() || arrSize < 1 || arrSize > MAX_SIZE)
    {
        std::cin.clear(); // remove error bit
        std::cin.sync();  // clear input buffer
        std::cout << "Your number must be between 1 and 50: ";
        std::cin >> arrSize;
    }
    
    // Clear input buffer.
    std::cin.clear();
    std::cin.sync();
    
    // Allocate memory for new arrays in heap
    int *inputArr1Ptr = new int[arrSize],
        *inputArr2Ptr = new int[arrSize],
        *outputArrPtr = new int[arrSize];
    
    // Populate first array
    int i = 0;
    std::string invalid; // invalid input
    std::cout << "\nEnter " << arrSize 
              << " integers for the 1st sequence, separated by spaces: ";
    while (i < arrSize)
    {
        std::cin >> *(inputArr1Ptr + i);
        // input validation
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin >> invalid;
            std::cout << invalid << " is invalid input. Skipping.\n";
        }
        else
        {
            i++;
        }
    }
    
    // Populate second array
    i = 0;
    std::cout << "\nEnter " << arrSize 
              << " integers for the 2nd sequence, separated by spaces: ";
    while (i < arrSize)
    {
        std::cin >> *(inputArr2Ptr + i);
        // input validation
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin >> invalid;
            std::cout << invalid << " is invalid input. Skipping.\n";
        }
        else
        {
            i++;
        }
    }
    
    // Sum values
    AddArrays(inputArr1Ptr, inputArr2Ptr, outputArrPtr);
    
    // Display result
    std::cout << "\nThe sum produces the following sequence: (";
    std::cout << *outputArrPtr;
    for (int j = 1; j < arrSize; j++)
    {
        std::cout << ", " << *(outputArrPtr + j);
    }
    std::cout << ")\n";
    
    // Free heap memory (good habit to get into)
    delete [] inputArr1Ptr;
    delete [] inputArr2Ptr;
    delete [] outputArrPtr;
    inputArr1Ptr = inputArr2Ptr = outputArrPtr = 0;
    
    return 0;
}

/**********************************************************
 *  void AddArrays(const int *arr1, const int *arr2, int *result)
 *
 *  Purpose: This function stores the sum of each element in
 *           arr1 and arr2 in result.
 *
 *  Preconditions: arr1, arr2, and result are all the same size
 *   
 *  Postconditions: result contains the sum of each index in arr1 and arr2
 *********************************************************/
void AddArrays(const int *arr1, const int *arr2, int *result)
{
    // Add the values of arr1 and arr2 and store the sum in result.
    for (int i = 0; i < sizeof(arr1); i++)
    {
        *(result + i) = *(arr1 + i) + *(arr2 + i);
    }
}