/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        Simulation.cpp
 *
 * Description:     Implementation of the Simulation class.
 ************************************************************************/
#include <iostream>
#include <stdexcept>
#include "Simulation.hpp"
#include "Pattern.hpp"
#include "utility.hpp"

/********************************************************************
 *  Function:       Simulation(int width, int height, int bufCellCount)
 *  Description:    The constructor takes the width and height of the
 *                  visible grid and creates a vgrid with bufCellCount 
 *                  cells added to all sides.
 *  Parameters:     width           Width of the visible grid
 *                  height          Height of the visible grid
 *                  bufCellCount    Number of padding cells added 
 *                                  to all sides
 *******************************************************************/
Simulation::Simulation(int width, int height, int bufCellCount)
{
    this->bufCellCount = bufCellCount;
    this->width = width + (bufCellCount * 2);
    this->height = height + (bufCellCount * 2);
    generationCount = 0;
    
    // Initialize grids
    initializeGrid(currentGrid);
    initializeGrid(nextGrid);
}

/********************************************************************
 *  Function:       bool getCellNextState(int x, int y)
 *  Description:    Gets whether the specified cell will be alive in
 *                  the next generation. Live cells will be alive if
 *                  there are 2-3 live neighbors. Dead cells will
 *                  come to life if there are 3 live neighbors.
 *  Parameters:     x   X coordinate of cell to check
 *                  y   Y coordinate of cell to check
 *  Preconditions:  Grids are initialized
 *                  Specified coords are at least 1 cell away from real edge
 *  Postconditions: Returns true if cell is alive in next generation.
 *******************************************************************/
bool Simulation::getCellNextState(int x, int y)
{
    // Validate argument values
    if ((x < 1 || x > width - 2) || (y < 1 || y > width - 2))
    {
        throw std::invalid_argument("ERROR: Invalid cell coordinates specified.");
    }
    
    int liveNeighborCount = 0;  // number of live neighbor cells
    bool currentState = false;  // stores state of cell in current generation
    bool nextState = false;        // stores state of cell in next generation
    
    // Check number of live neighbors
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (y == i && x == j)         // specified cell
            {
                currentState = currentGrid[i][j];
            }
            else if (currentGrid[i][j]) // neighbor is alive
            {
                liveNeighborCount++;
            }
        }
    }
    
    // Determine next state
    if (currentState)   // currently alive
    {
        // stays alive if 2 or 3 live neighbors
        nextState = liveNeighborCount > 1 && liveNeighborCount < 4;
    }
    else                // currently dead
    {
        // becomes alive if 3 live neighbors
        nextState = liveNeighborCount == 3;
    }
    return nextState;
}

/********************************************************************
 *  Function:       void initializeGrid(vgrid &grid)
 *  Description:    Creates the specified vgrid based on the width and
 *                  height member variables and sets all values to false.
 *  Parameters:     &grid   Grid to initialize
 *  Preconditions:  width and height are set
 *  Postconditions: Specified grid is initialized as 2D vector with
 *                  height rows, width columns, and all elements set to false.
 *******************************************************************/
void Simulation::initializeGrid(vgrid &grid)
{
    // Clear any existing data
    grid.clear();
    
    // Initialize rows and set all values to false
    for (int i = 0; i < height; i++)
    {
        std::vector<bool> row;
        for (int j = 0; j < width; j++)
        {
            row.push_back(false);
        }
        grid.push_back(row);
    }
}

/********************************************************************
 *  Function:       void resetGrid(vgrid &grid)
 *  Description:    Sets all values of the specified vgrid to false.
 *  Parameters:     &grid   Grid to reset
 *  Preconditions:  none
 *  Postconditions: Specified grid has all elements set to false.
 *******************************************************************/
void Simulation::resetGrid(vgrid &grid)
{
    // Set entire grid to false
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j] = false;
        }
    }
}

/********************************************************************
 *  Function:       void addPattern(Pattern p, int x, int y)
 *  Description:    Adds a pattern to the current grid with the top-left
 *                  corner at the specified x, y coordinates.
 *  Parameters:     p   Pattern to add
 *                  x   X coordinate of top-left corner of pattern
 *                  y   Y coordinate of top-left corner of pattern
 *  Preconditions:  Current grid is initialized, x,y is on visible grid
 *  Postconditions: Specified pattern is on current grid
 *******************************************************************/
void Simulation::addPattern(Pattern p, int x, int y)
{
    // Convert visible x and y to actual x and y
    int realX = x + bufCellCount;
    int realY = y + bufCellCount;
    int patternX = p.getWidth();
    int patternY = p.getHeight();
    
    // Validate argument values
    if ((realX + patternX > width)
          || (realY + patternY > height))
    {
        throw std::invalid_argument("ERROR: Pattern too large for coordinates.");
    }
    
    // Update currentGrid with specified Pattern
    for (int i = 0; i < patternY; i++)
    {
        for (int j = 0; j < patternX; j++)
        {
            currentGrid[i + realY][j + realX] = p.getCellState(j, i);
        }
    }
}

/********************************************************************
 *  Function:       void advanceGeneration()
 *  Description:    Makes the simulation transition to the next generation
 *                  and updates all cells according to the rules of
 *                  Conway's Game of Life.
 *  Parameters:     none
 *  Preconditions:  Current grid is initialized
 *  Postconditions: Current grid contains next generation and
 *                  generation count is incremented by 1
 *******************************************************************/
void Simulation::advanceGeneration()
{
    bool nextState = false; // stores the next state
    
    // Get state in next generation and set nextState grid
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            nextState = getCellNextState(j, i);
            nextGrid[i][j] = nextState;
        }
    }
    
    // Copy nextGrid to currentGrid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            currentGrid[i][j] = nextGrid[i][j];
        }
    }
    // Set nextGrid to all false
    resetGrid(nextGrid);
    // Increment generation counter
    generationCount++;
}

/********************************************************************
 *  Function:       void printCurrent()
 *  Description:    Prints the current generation to the console window.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Grid of current generation is displayed in console
 *******************************************************************/
void Simulation::printCurrent()
{
    // Calculate visible range of coordinates
    int startX = bufCellCount;
    int startY = bufCellCount;
    int endX = width - bufCellCount - 1;
    int endY = height - bufCellCount - 1;
    
    for (int i = startY; i < endY; i++)
    {
        for (int j = startX; j < endX; j++)
        {
            if (currentGrid[i][j])  // alive
            {
                std::cout << '#';
            }
            else                    // dead
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Current generation number: " << generationCount << std::endl;
}

/********************************************************************
 *  Function:       void runInConsole(int generations)
 *  Description:    Runs the simulation for the specified number of
 *                  generations and displays the output in the console.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Grid of the last generation is displayed in console
 *******************************************************************/
void Simulation::runInConsole(int generations)
{
    for (int i = 0; i < generations; i++)
    {
        sleepMilliseconds(SLEEP_MS);
        advanceGeneration();
        moveCursorToTopLeft();
        printCurrent();
    }
    clearWindow();
    printCurrent();
}
