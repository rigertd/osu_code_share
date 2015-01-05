/**********************************************************
 * Author:                 David Rigert
 * Date Created:           11/12/2014
 * Last Modification Date: 11/12/2014
 * Assignment:             Assignment 7
 * Filename:               ticTacToe.cpp
 *
 * Overview:
 *     This program lets two players play a game of Tic-Tac-Toe.
 *     The players can optionally pass a single command line argument
 *     for the number of consecutive games to play.
 * 
 * Input:
 *     3 ints as command line arguments, 
 *     values for each array
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *       0 1 2
 *     0 . . .
 *     1 . . .
 *     2 . . .
 *
 *     Player O: please enter your move.
 *     [0 0]
 *
 *       0 1 2
 *     0 O . .
 *     1 . . .
 *     2 . . .
 *
 *     Player X: please enter your move.
 *
 *     ...
 *
 *     Game 1 was a cat's game.
 *
 *     The final results were:
 *     Player O won 0 games.
 *     Player X won 0 games.
 *     There were 1 cat's games.
 *
 *     The final result is a draw!
 *********************************************************/
#include <iostream>
#include <cstdlib>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

// Global constants
const int BOARD_SIZE = 3;

// Type definitions
// 3x3 char array for the game board.
typedef char gameBoard[BOARD_SIZE][BOARD_SIZE];

// Function prototypes
// Prints the current state of the game board to the console.
void printBoard(const gameBoard, int);
// Initializes the game board.
void initBoard(gameBoard, int);
// Prompts player for coordinates and updates the game board.
bool getMove(gameBoard, int, char);
// Checks if a space is already taken.
bool checkMove(const gameBoard, int, int);
// Updates the game board with the specified move.
void updateBoard(gameBoard, int, int, char);
// Checks if either player has 3 in a row.
char checkBoard(const gameBoard, int);
// Prints out the final results to the console.
void printFinalResults(int, int, int);

int main(int argc, char **argv)
{
    // declare variables
    int playCount = 1,  // number of games to play
        curCount = 0,   // current game number
        moveCount = 0;  // current move number
    int results[] =     // [0] = Player 'O' win count
        {0, 0, 0};      // [1] = Cat game count
                        // [2] = Player 'X' win count
    gameBoard board;    // game board 3x3 array
    
    // Check if valid command line argument was specified
    if (argc == 2)
    {
        int input = std::atoi(argv[1]);
        if (input > 0)
            playCount = input;
        else
            cout << "Invalid argument. Defaulting to 1 game.\n";
    }
    else if (argc > 2)
    {
        std::cout << "Invalid number of arguments. Defaulting to 1 game.\n\n";
    }
    
    // start replay do-while loop
    do
    {
        // initialization
        moveCount = 0;
        initBoard(board, BOARD_SIZE);
        char winner = 0;
        
        // Display current game number if more than 1
        if (playCount > 1)
            cout << "Starting game " << curCount + 1
                 << " of " << playCount << ".\n";
        
        // start game do-while loop
        do
        {
            // Player O goes first, switch every game
            char player = (curCount + moveCount) % 2 == 0 ? 'O' : 'X';
            
            // print board to console and get move until valid move entered
            do
            {
                printBoard(board, BOARD_SIZE);

                // get player's move
            }
            while (!getMove(board, BOARD_SIZE, player));
            
            // check for winner if more than 2 moves
            if (moveCount >= 2)
                winner = checkBoard(board, BOARD_SIZE);
            
            // repeat until winner is found or board is full
        } while (winner == 0 && ++moveCount < (BOARD_SIZE * BOARD_SIZE));
        
        // Display final game board
        printBoard(board, BOARD_SIZE);
        
        // increment results array based on winner
        if (winner == 'O')
        {
            cout << "Player O won game " << curCount + 1 << ".\n";
            results[0]++;
        }
        else if (winner == 'X')
        {
            cout << "Player X won game " << curCount + 1 << ".\n";
            results[2]++;
        }
        else
        {
            cout << "Game " << curCount + 1 << " was a cat's game.\n";
            results[1]++;
        }
        cout << endl;
        
        // repeat until all games have been played
    } while (++curCount < playCount);
    
    // print final results to console
    printFinalResults(results[0], results[1], results[2]);
    
    return 0;
}    

/**********************************************************
 *  void printBoard(const gameBoard board, int size)
 *
 *  Purpose: This function prints the current state of 
 *           the game board to the console.
 *
 *  Preconditions: board is initialized and has size rows and columns
 *   
 *  Postconditions: The game board is printed to the console
 *********************************************************/
void printBoard(const gameBoard board, int size)
{
    // print top coordinates
    cout << endl << " ";
    for (int i = 0; i < size; i++)
        cout << std::setw(2) << i;
    cout << endl;
    
    // print left coordinates and array
    for (int i = 0; i < size; i++)
    {
        cout << i;
        for (int j = 0; j < size; j++)
        {
            cout << std::setw(2) << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

/**********************************************************
 *  void initBoard(gameBoard board, int size)
 *
 *  Purpose: This function initializes the game board
 *
 *  Preconditions: board has size rows and columns
 *   
 *  Postconditions: board is filled with '.' chars
 *********************************************************/
void initBoard(gameBoard board, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = '.';
}

/**********************************************************
 *  bool getMove(gameBoard board, int size, char player)
 *
 *  Purpose: This function prompts player for coordinates 
 *           and updates the game board.
 *
 *  Preconditions: board is initialized to size, has open spaces,
 *                 and player is 'O' or 'X'
 *   
 *  Postconditions: Returns true board is updated with player's move
 *                  or false otherwise
 *********************************************************/
bool getMove(gameBoard board, int size, char player)
{
    int row = -1, col = -1; // row and column input
    cout << "Player " << player << ": please enter your move.\n";
    
    // check for invalid input type
    cin >> row >> col;
    if (cin.fail())
    {
        cout << "Invalid input. Enter the row and column numbers, "
             << "separated by a space.\n";
        cin.clear();
        row = col = -1;
    }
    // check for invalid numbers
    else if (row < 0 || row > size - 1 || col < 0 || col > size - 1)
    {
        cout << "Invalid coordinates. Enter two numbers between 0 and "
             << size - 1 << ".\n";
        row = col = -1;
    }
    // check for invalid move
    else if (!checkMove(board, row, col))
    {
        cout << "That space is already taken.\n";
        row = col = -1;
    }
    
    // clear input buffer if anything is left in it
    if (cin.peek() != '\n')
    {
        cin.ignore(1000, '\n');
    }
    
    if (row == -1 || col == -1)
    {
        // invalid input
        return false;
    }
    else
    {
        // update game board
        updateBoard(board, row, col, player);
        return true;
    }
}

/**********************************************************
 *  bool checkMove(const gameBoard board, int row, int col)
 *
 *  Purpose: This function determines whether a space on the board
 *           is already taken.
 *
 *  Preconditions: board is initialized and row and col are valid
 *                 coordinates on the board.
 *   
 *  Postconditions: Returns whether the space is empty ('.')
 *********************************************************/
bool checkMove(const gameBoard board, int row, int col)
{
    return board[row][col] == '.';
}

/**********************************************************
 *  void updateBoard(gameBoard board, int row, int col, char player)
 *
 *  Purpose: This function updates the game board with the specified move.
 *
 *  Preconditions: board is initialized and row and col are valid
 *                 coordinates on the board.
 *   
 *  Postconditions: board is updated with the player symbol at (row, col)
 *********************************************************/
void updateBoard(gameBoard board, int row, int col, char player)
{
    board[row][col] = player;
}

/**********************************************************
 *  char checkBoard(const gameBoard board, int size)
 *
 *  Purpose: This function determines whether either player has 3 in a row.
 *
 *  Preconditions: board is initialized with size rows and columns
 *   
 *  Postconditions: Returns 'O' if player O has three in a row,
 *                  'X' if player X has three in a row,
 *                  and '\0' (NULL) if there is no winner yet
 *********************************************************/
char checkBoard(const gameBoard board, int size)
{
    int *rows = new int[size]; // holds sums of rows
    int *cols = new int[size]; // holds sums of columns
    int topLeftDiag = 0;       // holds top-right to bottom-left diagonal
    int topRightDiag = 0;      // holds top-left to bottom-right diagonal
    char winner = 0;           // holds winner
    
    // initialize colSums array
    for (int i = 0; i < size; i++)
        cols[i] = 0;
    
    for (int i = 0; i < size; i++)
    {
        // initialize current row to 0
        rows[i] = 0;
        
        // Add 1 to total for 'O', 10 for 'X'
        for (int j = 0; j < size; j++)
        {
            // count pieces in row
            rows[i] += (board[i][j] == 'O' ? 1 : 
                        board[i][j] == 'X' ? 10 : 0);
            
            // count pieces in col
            cols[j] += (board[i][j] == 'O' ? 1 : 
                        board[i][j] == 'X' ? 10 : 0);
            
            // count top-left diagonal
            if (i == j)
                topLeftDiag += (board[i][j] == 'O' ? 1 : 
                                board[i][j] == 'X' ? 10 : 0);
            
            // count top-right diagonal
            if (i == (size - j - 1))
                topRightDiag += (board[i][j] == 'O' ? 1 : 
                                 board[i][j] == 'X' ? 10 : 0);
        }
    }
    
    // check diagonals for winner
    if (topLeftDiag % 10 == 3 || topRightDiag % 10 == 3)
        winner = 'O';
    else if (topLeftDiag / 10 == 3 || topRightDiag / 10 == 3)
        winner = 'X';
    
    // check rows and columns for winner
    for (int i = 0; i < size && winner == 0; i++)
    {
        if (rows[i] % 10 == 3 || cols[i] % 10 == 3)
            winner = 'O';
        else if (rows[i] / 10 == 3 || cols[i] / 10 == 3)
            winner = 'X';
    }
    
    // free dynamically allocated arrays
    delete [] rows;
    delete [] cols;
    rows = cols = 0;
    
    return winner;

}

/**********************************************************
 *  void printFinalResults(const int oWins, const int cats, const int xWins)
 *
 *  Purpose: This function prints out the final results to the console.
 *
 *  Preconditions: None
 *   
 *  Postconditions: The final results are printed to the console
 *********************************************************/
void printFinalResults(const int oWins, const int cats, const int xWins)
{
    cout << "The final results were:\n"
         << "Player O won " << oWins << " games.\n"
         << "Player X won " << xWins << " games.\n"
         << "There were " << cats << " cat's games.\n\n";
    
    if (oWins > xWins)
        cout << "Player O is the overall winner!\n";
    else if (xWins > oWins)
        cout << "Player X is the overall winner!\n";
    else
        cout << "The final result is a draw!\n";
}

