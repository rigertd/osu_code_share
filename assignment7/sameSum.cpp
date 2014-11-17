/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/10/2014
 * Last Modification Date: 11/11/2014
 * Assignment:             Assignment 7
 * Filename:               sameSum.cpp
 *
 * Overview:
 *     This program determines whether sums of the numbers in
 *     the rows, columns, and major diagonals of a square array
 *     are equal.
 *     It prompts the user for the number of rows in the array
 *     and then for the values in each row.
 * 
 * Input:
 *     number of rows, values for each row
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     This program determines whether sums of the numbers in
 *     the rows, columns, and major diagonals of a square array
 *     are equal.
 *  
 *     Enter the number of rows in your square array (1 to 50): [3]
 *     Enter 3 values for row 1, separated by spaces: [1 1 1]
 *     Enter 3 values for row 2, separated by spaces: [1 1 1]
 *     Enter 3 values for row 3, separated by spaces: [1 1 1]
 *
 *     All sums in your square array ARE equal.
 *********************************************************/
#include <iostream>
#include <string>

// Global constants
const int MIN_ARR_SIZE = 1;  // minimum size of square array
const int MAX_ARR_SIZE = 50; // maximum size of square array

// Function prototypes
// Determines whether all rows, columns, and major diagonals have same sum.
bool hasSameSum(int ** const, int);
// Gets an array size between min and max.
int getArrSize(int = MIN_ARR_SIZE, int = MAX_ARR_SIZE);
// Initializes a 2D square array with specified rows and columns.
void init2dArr(int **&, int);
// Populates a 2D square array with values.
void populate2dArr(int **, int);
// Gets values for a row in a 2D array.
void getRowInput(int *, int);
// Finalizes a 2D square array with specified rows.
void finalize2dArr(int **&, int);

int main()
{
    int arrSize = 0;
    int **squareArr;
    
    std::cout << "This program determines whether sums of the numbers in\n"
              << "the rows, columns, and major diagonals of a square array\n"
              << "are equal.\n\n";
    
    // get array size from user
    arrSize = getArrSize(); // use default arguments

    // initialize array
    init2dArr(squareArr, arrSize);
    
    // populate array with values
    populate2dArr(squareArr, arrSize);
    
    // call comparison function and display result
    std::cout << "\nAll sums in your square array ARE "
              << (hasSameSum(squareArr, arrSize) ? "" : "NOT ")
              << "equal.\n";

    // finalize array
    finalize2dArr(squareArr, arrSize);
    
    return 0;
}

/**********************************************************
 *  bool hasSameSum(int ** const arr, int rows)
 *
 *  Purpose: This function determines whether all rows, columns,
 *           and major diagonals have the same sum.
 *
 *  Preconditions: arr is an initialized square 2D array
 *                 with 'rows' height and width
 *   
 *  Postconditions: Returns whether the sums are equal
 *********************************************************/
bool hasSameSum(int ** const arr, int rows)
{
    int *rowSums = new int[rows]; // holds sums of rows
    int *colSums = new int[rows]; // holds sums of columns
    int topLeftDiag = 0;          // holds top-right to bottom-left diagonal
    int topRightDiag = 0;         // holds top-left to bottom-right diagonal
    bool result = true;           // holds whether the sums are equal
    
    // initialize colSums array
    for (int i = 0; i < rows; i++)
        colSums[i] = 0;
    
    for (int i = 0; i < rows; i++)
    {
        // initialize current row to 0
        rowSums[i] = 0;
        
        for (int j = 0; j < rows; j++)
        {
            // count nums in row
            rowSums[i] += arr[i][j];
            
            // count nums in col
            colSums[j] += arr[i][j];
            
            // count top-left diagonal
            if (i == j)
                topLeftDiag += arr[i][j];
            
            // count top-right diagonal
            if (i == (rows - j - 1))
                topRightDiag += arr[i][j];
        }
    }
    
    // check if diagonals are equal
    result = topLeftDiag == topRightDiag;
    
    // check if all sums are equal
    for (int i = 0; i < rows && result; i++)
    {
        // check rows and columns
        result = topLeftDiag == rowSums[i] && rowSums[i] == colSums[i];
    }
    
    // free dynamically allocated arrays
    delete [] rowSums;
    delete [] colSums;
    rowSums = colSums = 0;
    
    return result;
}

/**********************************************************
 *  int getArrSize(int min, int max)
 *
 *  Purpose: This function prompts the user for an array size
 *           between min and max until a valid value is entered.
 *
 *  Preconditions: min <= max
 *   
 *  Postconditions: Returns the array size
 *********************************************************/
int getArrSize(int min, int max)
{
    int size = 0;
    std::cout << "Enter the number of rows in your square array ("
              << min << " to "
              << max << "): ";
    std::cin >> size;

    // Validate input.
    while (std::cin.fail() || size < min || size > max)
    {
        std::cin.clear(); // remove error bit
        std::cin.sync();  // clear input buffer
        std::cout << "The number of rows must be between "
                  << min << " and "
                  << max << ": ";
        std::cin >> size;
    }
    
    return size;
}

/**********************************************************
 *  void init2dArr(int **&arr, int size)
 *
 *  Purpose: This function allocates memory for a 2D array
 *           with 'size' rows and columns.
 *
 *  Preconditions: arr is uninitialized
 *   
 *  Postconditions: arr is initialized
 *********************************************************/
void init2dArr(int **&arr, int size)
{
    // allocate memory for pointer to int pointer arrays
    arr = new int*[size];
    
    // allocate memory for each int pointer array in arr
    for (int i = 0; i < size; i++)
    {
        arr[i] = new int[size];
    }
}

/**********************************************************
 *  void populate2dArr(int **arr, int size)
 *
 *  Purpose: This function prompts the user for values to store
 *           in each row of the array. Invalid values are skipped.
 *
 *  Preconditions: arr is initialized and has 'size' rows and columns
 *   
 *  Postconditions: arr contains the user-entered values
 *********************************************************/
void populate2dArr(int **arr, int size)
{
    // clear input buffer
    std::cin.clear();
    std::cin.sync();

    // get values for each row
    for (int i = 0; i < size; i++)
    {
    std::cout << "Enter "
              << size
              << " values for row "
              << i + 1
              << ", separated by spaces: ";

        getRowInput(arr[i], size);
    }
}

/**********************************************************
 *  void getRowInput(int *row, int size)
 *
 *  Purpose: This function gets valid integers to store
 *           in a row. Invalid values are skipped.
 *
 *  Preconditions: User has been prompted, row has 'size' elements
 *                 and input buffer is empty
 *   
 *  Postconditions: row contains the user-entered values
 *                  and input buffer is empty
 *********************************************************/
void getRowInput(int *row, int size)
{
    int num = 0;         // current index
    std::string invalid; // invalid input

    while (num < size)
    {
        std::cin >> row[num];
        // input validation
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin >> invalid;
            std::cout << invalid << " is invalid input. Skipping.\n";
        }
        else
        {
            num++;
        }
    }
    
    // skip rest of input buffer if not LF or EOF
    if (std::cin.peek() != std::char_traits<char>::eof()
        && std::cin.peek() != '\n')
    {
        std::getline(std::cin, invalid);
        std::cout << "This row is already full. Skipping \""
                  << invalid << "\".\n";
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
