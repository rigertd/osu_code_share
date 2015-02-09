/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        Pattern.cpp
 *
 * Description:     Implementation of the Pattern class.
 ************************************************************************/
#include <stdexcept>
#include <algorithm>
#include "Pattern.hpp"

/********************************************************************
 *  Function:       Pattern(std::string name, vgrid &sourceGrid)
 *  Description:    Instantiates a Pattern with the specified name
 *                  and pattern.
 *  Parameters:     name        Name to assign to pattern
 *                  sourceGrid  Grid pattern to copy to new object
 *******************************************************************/
Pattern::Pattern(std::string name, vgrid &sourceGrid)
{
    this->name = name;
    
    // Copy source grid to member variable
    std::copy(sourceGrid.begin(), sourceGrid.end(), std::back_inserter(grid));
}

/********************************************************************
 *  Function:       bool getCellState(int x, int y)
 *  Description:    Gets whether the cell at the specified coordinates
 *                  is alive.
 *  Parameters:     x   X coordinate of the cell to check
 *                  y   Y coordinate of the cell to check
 *  Preconditions:  x,y is a valid cell
 *  Postconditions: Returns true if the cell is alive; false otherwise
 *******************************************************************/
bool Pattern::getCellState(int x, int y)
{
    // Validate arguments
    if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
    {
        throw std::invalid_argument("ERROR: Specified coordinates out of bounds.");
    }
    
    return grid[y][x];
}