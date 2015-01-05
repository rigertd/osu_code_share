/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/11/2014
 * Last Modification Date: 11/11/2014
 * Assignment:             Assignment 7
 * Filename:               symArrays.cpp
 *
 * Overview:
 *     This program takes 3 command line arguments for array sizes,
 *     prompts the users for data for each array, and prints whether
 *     the arrays are symmetric.
 * 
 * Input:
 *     3 ints as command line arguments, 
 *     values for each array
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     symArrays 5 3 2
 *
 *     Please enter 5 numbers for array 1.
 *     [1 2 3 2 1]
 *     Please enter 3 numbers for array 2.
 *     [1 2 3]
 *     Please enter 2 numbers for array 3.
 *     [2 2]
 *
 *     Array 1 is symmetric.
 *     Array 2 is not symmetric.
 *     Array 3 is symmetric.
 *********************************************************/
#include <iostream>
#include <cstdlib>

// Global constants
const int ARRAY_COUNT = 3;

// Function prototypes
// Determines whether an array is symmetric.
bool isSymmetric(int * const, int);
// Initializes a 2D jagged array with the specified rows and columns.
void init2dArr(int **&, int, int []);
// Populates a 2D jagged array with values.
void populate2dArr(int **, int, int []);
// Gets values for a row in a 2D array.
void getRowInput(int *, int);
// Finalizes a 2D array with the specified rows.
void finalize2dArr(int **&, int);

int main(int argc, char **argv)
{
    // declare variables
    int **arr;                  // pointer to an array of int pointers
    int rowCounts[ARRAY_COUNT]; // array of element count for each row
    
    // make sure required command line arguments were specified
    if (argc != ARRAY_COUNT + 1)
    {
        std::cout << "SYNTAX ERROR: "
                  << "This program requires three integer arguments.\n\n"
                  << "Specify the number of elements for three arrays\n"
                  << "and this program will tell you if they are symmetric.\n";
                  
        return 0;
    }
    
    // populate rowCounts with argument values
    for (int i = 1; i < argc; i++)
    {
        int val = std::atoi(argv[i]);
        if (val == 0)
        {
            std::cout << "Invalid argument specified.\n";
            return 0;
        }
        rowCounts[i - 1] = val;
    }
    
    // initialize array
    init2dArr(arr, ARRAY_COUNT, rowCounts);
    
    // populate array with values
    populate2dArr(arr, ARRAY_COUNT, rowCounts);
    
    // call comparison function and display result
    std::cout << std::endl;
    for (int i = 0; i < ARRAY_COUNT; i++)
    {
    std::cout << "Array " << i + 1 << " is "
              << (isSymmetric(arr[i], rowCounts[i]) ? "" : "not ")
              << "symmetric.\n";
    }
    
    // finalize array
    finalize2dArr(arr, ARRAY_COUNT);
    
    return 0;
}

/**********************************************************
 *  bool isSymmetric(int * const arr, int size)
 *
 *  Purpose: This function determines whether the values in
 *           the specified array are symmetric.
 *
 *  Preconditions: arr is an array of ints with 'size' elements
 *   
 *  Postconditions: Returns whether the array is symmetric
 *********************************************************/
bool isSymmetric(int * const arr, int size)
{
    // compare outer elements and move toward center
    for (int i = 0; i < size / 2; i++)
    {
        if (arr[i] != arr[size - i - 1])
            return false;
    }
    
    // if we make it here, it is symmetric
    return true;
}

/**********************************************************
 *  void init2dArr(int **&arr, int rows, int cols[])
 *
 *  Purpose: This function allocates memory for a 2D array
 *           with 'rows' rows and 'cols' columns.
 *
 *  Preconditions: arr is uninitialized
 *   
 *  Postconditions: arr is initialized
 *********************************************************/
void init2dArr(int **&arr, int rows, int cols[])
{
    // allocate memory for pointer to int pointer arrays
    arr = new int*[rows];
    
    // allocate memory for each int array in arr
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols[i]];
    }
}

/**********************************************************
 *  void populate2dArr(int **arr, int rows, int cols[])
 *
 *  Purpose: This function prompts the user for values to store
 *           in each row of the array.
 *
 *  Preconditions: arr is initialized and has 'rows' rows 
 *                 and each row has 'cols' columns
 *   
 *  Postconditions: arr contains the user-entered values
 *********************************************************/
void populate2dArr(int **arr, int rows, int cols[])
{
    // clear input buffer
    std::cin.clear();
    std::cin.sync();

    // get values for each row
    for (int i = 0; i < rows; i++)
    {
    std::cout << "Please enter "
              << cols[i]
              << " numbers for array "
              << i + 1
              << ".\n";

        getRowInput(arr[i], cols[i]);
    }
}

/**********************************************************
 *  void getRowInput(int *row, int size)
 *
 *  Purpose: This function gets valid integers to store in a row.
 *           Reprompts the user if invalid input is entered.
 *
 *  Preconditions: User has been prompted, row has 'size' elements
 *                 and input buffer is empty
 *   
 *  Postconditions: row contains the user-entered values
 *                  and input buffer is empty
 *********************************************************/
void getRowInput(int *row, int size)
{
    int num = 0; // current index

    while (num < size)
    {
        std::cin >> row[num++];
        // input validation
        if ( std::cin.fail() ||
            (std::cin.peek() == '\n' && num != size) ||
            (std::cin.peek() == ' ' && num == size)    )
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid data. Try again.\n";
            num = 0;
        }
    }
    
    // clear input buffer
    std::cin.clear();
    std::cin.sync();
}

/**********************************************************
 *  void finalize2dArr(int **&arr, int size)
 *
 *  Purpose: This function frees all of the memory that was allocated
 *           for the 'arr' array and sets the pointer to null.
 *
 *  Preconditions: arr is initialized and has 'size' rows and columns
 *   
 *  Postconditions: memory is returned to heap and arr points to null
 *********************************************************/
void finalize2dArr(int **&arr, int size)
{
    // return memory for each int array to heap
    for (int i = 0; i < size; i++)
    {
        delete [] arr[i];
    }
    
    // return memory for pointer to int pointer array
    delete [] arr;
    
    // set arr pointer to null
    // (this is why I passed the pointer by reference)
    arr = 0;
}
