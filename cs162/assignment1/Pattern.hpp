/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        Pattern.hpp
 *
 * Description:     Represents a pattern of live and dead cells.
 ************************************************************************/
#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <vector>

// Define 2D bool vector as vgrid
typedef std::vector<std::vector<bool> > vgrid;

class Pattern
{
// member variables
private:
    std::vector<std::vector<bool> > grid;   // holds the pattern
    std::string name;                       // name of pattern

// member functions    
public:
    /********************************************************************
     *  Function:       Pattern()
     *  Description:    The default constructor. Sets name to empty string
     *                  and creates a 0 x 0 grid. 
     *******************************************************************/
    Pattern()
    {
        name = "";
    }
    
    // Constructs a Pattern object with the specified name and pattern
    Pattern(std::string, vgrid &);
    
    /********************************************************************
     *  Function:       int getWidth()
     *  Description:    Gets the width of the pattern grid.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns the width of the grid or 0 if uninitialized
     *******************************************************************/
    int getWidth()
    {
        return grid.size() > 0 ? grid[0].size() : 0;
    }
    
    /********************************************************************
     *  Function:       int getHeight()
     *  Description:    Gets the height of the pattern grid.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns the height of the grid
     *******************************************************************/
    int getHeight()
    {
        return grid.size();
    }
    
    /********************************************************************
     *  Function:       std::string getName()
     *  Description:    Gets the name of the pattern.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns the name of the pattern
     *******************************************************************/
    std::string getName()
    {
        return name;
    }
    
    // Gets whether the specified cell is alive
    bool getCellState(int, int);
};

#endif // end of define PATTERN_HPP
