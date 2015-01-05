/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/6/2014
 * Last Modification Date: 11/6/2014
 * Assignment:             Assignment 6
 * Filename:               grades.cpp
 *
 * Overview:
 *     This program prompts the user for quiz grades between 0 and 5
 *     until the user enters -1 and then displays the histogram count.
 * 
 * Input:
 *     arbitrary number of grades
 *     -1 to stop entering grades
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Enter grades between 0 and 5. Enter -1 when done: [1 3 5 2 3 0 -1]
 *
 *     The histogram for the quiz is as follows:
 *     
 *     1 grade of 0
 *     1 grade of 1
 *     1 grade of 2
 *     2 grades of 3
 *     0 grades of 4
 *     1 grade of 5
 *********************************************************/
#include <iostream> // for cin/cout
#include <string>   // for string object

int main()
{
    const int MIN_GRADE = 0; // minimum possible grade
    const int MAX_GRADE = 5; // maximum possible grade
    int input;               // stores user input
    
    // declare array and initialize to 0
    int grades[MAX_GRADE + 1] = {0, 0, 0, 0, 0, 0};
    
    // Prompt user for grades
    std::cout << "Enter grades between " << MIN_GRADE << " and " << MAX_GRADE
              << ". Enter -1 when done: ";
    
    // Keep getting input until -1 is entered
    do
    {
        // get numeric input
        std::cin >> input;
        
        // Skip any invalid input
        if (std::cin.fail())
        {
            std::string invalid; // stores invalid input
            std::cin.clear();    // clear error bit
            std::cin >> invalid; // get invalid input from buffer
            std::cout << invalid << " is an invalid grade. Skipping.\n";
        }
        else if (input > MAX_GRADE || (input < MIN_GRADE && input != -1))
        {
            std::cout << input << " is an invalid grade. Skipping.\n";
        }
        else // valid input
        {
            grades[input]++;
        }
    } while (input != -1);
    
    // Output histogram count
    std::cout << "\nThe histogram for the quiz is as follows:\n";
    for (int i = 0; i <= MAX_GRADE; i++)
    {
        std::cout << grades[i] << (grades[i] == 1 ? " grade " : " grades ")
                  << "of " << i << "\n";
    }

    return 0;
}
