/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        menu.cpp
 *
 * Description:     This program is a simulation of Conway's Game of Life.
 *                  The user can select from a list of known patterns and
 *                  add them to an 80x22 grid of cells. 
 *                  The user can only modify the initial state of the 
 *                  simulation. Once the simulation starts running, the
 *                  user can only specify the number of generations to
 *                  advance.
 *
 * Input:           - User chooses patterns to add to the initial state from
 *                    a list of known patterns loaded from patterns.txt.
 *                  - Once the simulation begins, the user specifies the
 *                    number of generations to advance at the prompt.
 *
 * Output:          - Displays a menu for setting the initial state.
 *                  - Displays a list of known patterns.
 *                  - Displays the changes of the cells as an animation for
 *                    the specified number of generations.
 ************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Simulation.hpp"
#include "Pattern.hpp"
#include "utility.hpp"

// Function prototypes
// Gets a set of coordinates from the user
void getCoordinates(int &, int &);
// Populates a vector with a set of hard-coded patterns
void loadPatterns(std::vector<Pattern> &);
// Prints the initial setup menu to the console
void printMenu();
// Prints a list of available patterns to the user
void printPatternMenu(std::vector<Pattern> &);
// Runs the simulation
void runSimulation(Simulation &);
// Gets the pattern index of the user selection
int selectPattern(std::vector<Pattern> &);

// Constants
static const int GRID_WIDTH = 80;
static const int GRID_HEIGHT = 22;
static const int BUFFER_CELLS = 40;

int main()
{
    Simulation sim = Simulation(GRID_WIDTH, GRID_HEIGHT, BUFFER_CELLS);
    int selection = 0;              // for menu selection
    int index;                      // for pattern index
    int x, y;                       // for pattern coordinates
    std::vector<Pattern> patterns;  // for predefined patterns
    
    // Load patterns from file
    loadPatterns(patterns);
    
    // Display welcome message
    std::cout << "\nWelcome to David Rigert's Life Simulator.\n";
    std::cout << "This program is for CS162_400 in Winter 2015.\n";

    // Menu loop
    do
    {
        std::cout << std::endl;
        printMenu();
        std::cout << "Enter your selection: ";
        std::cin >> selection;

        clearInputBuffer();
        
        // Initialize coordinate variables to invalid selection
        x = y = -1;
        
        switch(selection)
        {
            case 1: 
                sim.printCurrent();
                std::cout << "Press Enter to continue...";
                std::cin.ignore(1000, '\n');
                break;
            case 2:
                std::cout << std::endl;
                index = selectPattern(patterns);
                std::cout << std::endl;
                getCoordinates(x, y);
                
                // Add pattern to simulation
                sim.addPattern(patterns[index], x, y);
                break;
            case 3:
                runSimulation(sim);
                // Intentional fall-through
            case 4:
                std::cout << "\nThank you for playing.\n";
                break;
            default:
                std::cout << "\nInvalid selection.\n\n"; 
        }
    } while (selection < 3 || selection > 4);
    
    return 0;
}

/********************************************************************
 *  Function:       void getCoordinates(int &x, int &y)
 *  Description:    Gets a set of valid x,y coordinates from the user.
 *  Parameters:     x   Stores the X coordinate.
 *                  y   Stores the Y coordinate.
 *  Preconditions:  none
 *  Postconditions: x and y contain the entered coordinates.
 *******************************************************************/
void getCoordinates(int &x, int &y)
{
    std::cout << "Enter the starting coordinates of the top-left corner.\n";
    std::cout << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;

    // Validate coordinates
    while (std::cin.peek() != '\n'
        || x < 0 || x > GRID_WIDTH 
        || y < 0 || y > GRID_HEIGHT)
    {
        std::cout << "\nInvalid coordinates. Try again\n";
        clearInputBuffer();
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
    }

    clearInputBuffer();
}


/********************************************************************
 *  Function:       void loadPatterns(std::vector<Pattern> &patterns)
 *  Description:    Loads the patterns from patterns.txt.
 *  Parameters:     patterns    Stores the patterns from patterns.txt.
 *  Preconditions:  patterns.txt is in same directory as executable.
 *  Postconditions: patterns vector contains list of Pattern objects
 *                  defined in patterns.txt file.
 *******************************************************************/
void loadPatterns(std::vector<Pattern> &patterns)
{
    // Patterns taken from http://en.wikipedia.org/wiki/Conway's_Game_of_Life
    std::ifstream dataIn;
    dataIn.open("patterns.txt");
    if (dataIn.fail())
    {
        std::cout << "Warning: pattern.txt file not found.\n";
        return;
    }
    
    std::string name;
    std::string vals;
    std::istringstream iss;
    std::vector<std::vector<bool> > grid;
    int width = 0;
    int height = 0;
    int val = 0;
    
    // Load patterns from file
    while (!dataIn.eof())
    {
        // Load name and first line of values
        std::getline(dataIn, name);
        std::getline(dataIn, vals);

        // Create vector rows and store pattern
        while (vals != "#" && !dataIn.eof())
        {
            iss.clear();
            iss.str(vals);
            std::vector<bool> row;
            while (iss >> val)
            {
                row.push_back(static_cast<bool>(val));
            }
            grid.push_back(row);
            std::getline(dataIn, vals);
        }

        // Store pattern in vector unless name is blank
        if (!name.empty())
        {
            patterns.push_back(Pattern(name, grid));
        }
        grid.clear();
    }
    
    dataIn.close();
}

/********************************************************************
 *  Function:       void printMenu()
 *  Description:    Prints the initial setup menu
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Initial setup menu items are displayed on console.
 *******************************************************************/
void printMenu()
{
    std::cout << " 1: Show current configuration\n"
              << " 2: Add a pattern\n"
              << " 3: Run the simulation\n"
              << " 4: Quit the program\n\n";
}

/********************************************************************
 *  Function:       void printPatternMenu(std::vector<Pattern> &patterns)
 *  Description:    Prints the names of the Pattern objects in patterns
 *                  as a list of menu items.
 *  Parameters:     patterns    List of Pattern objects
 *  Preconditions:  none
 *  Postconditions: Initial setup menu items are displayed on console.
 *******************************************************************/
void printPatternMenu(std::vector<Pattern> &patterns)
{
    for (int i = 0; i < patterns.size(); i++)
    {
        std::cout << std::setw(2) << std::right << (i + 1) << ": "
                  << patterns[i].getName() << " (Size: " 
                  << patterns[i].getWidth() << " x " 
                  << patterns[i].getHeight() << " cells)" << std::endl;
    }
    std::cout << std::endl;
}

/********************************************************************
 *  Function:       void runSimulation(Simulation &sim)
 *  Description:    Prompts the user for the number of generations and
 *                  runs the simulation based on the current configuration.
 *  Parameters:     sim     Simulation object to run
 *  Preconditions:  none
 *  Postconditions: User chose to exit the simulation
 *******************************************************************/
void runSimulation(Simulation &sim)
{
    unsigned runForGens = 0; // for input of number of generations to run
    
    // Clear console
    clearWindow();
    // Print current state
    sim.printCurrent();
    
    std::cout << "Enter the number of generations to run or any letter to quit: ";

    while (std::cin >> runForGens)
    {
        sim.runInConsole(runForGens);
        std::cout << "Enter another number to advance or any letter to quit: ";
    }
}


/********************************************************************
 *  Function:       int selectPattern(std::vector<Pattern> &patterns)
 *  Description:    Prompts the user to select a pattern and returns 
 *                  the index.
 *  Parameters:     patterns    Vector of Pattern objects to list
 *  Preconditions:  patterns has at least one Pattern object.
 *  Postconditions: Returns the index of the selected Pattern object.
 *******************************************************************/
int selectPattern(std::vector<Pattern> &patterns)
{
    // Test for empty patterns vector
    if (patterns.size() < 1)
    {
        throw std::invalid_argument("ERROR: No patterns were loaded.\n");
    }
    
    int selection = 0;
    printPatternMenu(patterns);
    std::cout << "Select a pattern to add: ";
    std::cin >> selection;
    
    // Validate selection
    while (selection > patterns.size() || selection < 1)
    {
        clearInputBuffer();
        std::cout << "Invalid selection. Try again: ";
        std::cin >> selection;
    }
    
    clearInputBuffer();

    // Return index value
    return selection - 1;
}
