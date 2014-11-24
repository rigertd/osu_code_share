/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/17/2014
 * Last Modification Date: 11/17/2014
 * Assignment:             Assignment 8
 * Filename:               findMode.cpp
 *
 * Overview:
 *     This program prompts the user for integers until a sentinel 
 *     value is entered, finds the mode(s) of all values entered,
 *     and displays the results.
 * 
 * Input:
 *     integer values
 *     sentinel value (blank line)
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     This program finds the mode(s) of a list of integer values.
 *     Press Enter without any value when you are done.
 *
 *     Enter a value: [4]
 *     Enter a value: [2]
 *     Enter a value: [9]
 *     Enter a value: [2]
 *     Enter a value:
 *
 *     The mode is 2.
 ************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <algorithm>

using namespace std;

// function prototypes
// Finds the mode(s) of the ints in the specified vector.
vector<int> findMode(const vector<int> &);
// Determines whether a string is a valid integer.
bool isInteger(const string &);

int main()
{
    // declare variables
    vector<int> input; // stores user input
    string buffer;     // stores unvalidated input
    
    cout << "This program finds the mode(s) of a list of integer values.\n"
         << "Press Enter without any value when you are done.\n\n";
         
    do
    {
        cout << "Enter a value: ";
        getline(cin, buffer);
        
        // check if valid input
        if (isInteger(buffer))
        {
            // add to vector
            input.push_back(atoi(buffer.c_str()));
        }
        else if (!buffer.empty())
        {
            // invalid input
            cout << "Invalid integer. Try again.\n";
        }
    } while (!buffer.empty());
    
    if (!input.empty()) // non-empty
    {
        // get the mode(s)
        vector<int> result = findMode(input);
        
        // display result(s)
        if (result.size() > 1)
        {
            // fencepost
            cout << "\nThe modes are " << result[0];
            for (int i = 1; i < result.size(); i++)
            {
                if (i == result.size() - 1)
                    cout << " and " << result[i] << ".\n";
                else
                    cout << ", " << result[i];
            }
        }
        else if (result.size() == 1)
        {
            cout << "\nThe mode is " << result[0] << ".\n";
        }
    }
    else              // empty
    {
        cout << "\nYou did not enter any integers.\n";
    }

    return 0;
}

/**
    bool isInteger(const string &str)
    
    Purpose:
        This function determines whether a string is a valid integer.
    
    Preconditions:
        none
    
    Postconditions:
        returns true if string only contains 0-9, false otherwise
 */
bool isInteger(const string &str)
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

/**
    vector<int> findMode(const vector<int> &vals)
    
    Purpose:
        This function finds the mode of the integer values in the specified 
        vector. Returns multiple values if there is more than one mode.
    
    Preconditions:
        vals is initialized
    
    Postconditions:
        returns a vector containing the mode(s)
 */
vector<int> findMode(const vector<int> &vals)
{
    // create working vectors
    vector<int> sorted (vals);
    vector<int> results;
    
    // return empty vector if vals is empty
    if (vals.empty())
        return results;
    
    // sort vector into ascending order
    sort(sorted.begin(), sorted.end());
    
    // add first element to result
    results.push_back(sorted[0]);
    int prev = sorted[0];
    int highCount = 1;
    int count = 1;
    
    // check for repeats in sorted vector and keep track of highest count
    for (int i = 1; i < sorted.size(); i++)
    {
        if (sorted[i] == prev)
        { // current value same as previous
            count++;
            if (count > highCount)
            {
                // update highCount
                highCount = count;
                // clear previous results unless current value is only result
                if (results.size() > 1 || results[0] != sorted[i])
                {
                    results.clear();
                    results.push_back(sorted[i]);
                }
            }
            else if (count == highCount)
            {
                // add current value to results
                results.push_back(sorted[i]);
            }
        }
        else
        { // different value--reset count and prev variables
            count = 1;
            prev = sorted[i];
            if (count == highCount)
            {
                // add current value to results
                results.push_back(sorted[i]);
            }
        }
    }

    return results;
}
