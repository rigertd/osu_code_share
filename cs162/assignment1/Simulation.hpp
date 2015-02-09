/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/10/2015
 * Last Modified:   1/13/2015
 * Assignment:      Assignment 1
 * Filename:        Simulation.hpp
 *
 * Description:     Represents a Game of Life simulator.
 ************************************************************************/
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>

// Define 2D bool vector as vgrid
typedef std::vector<std::vector<bool> > vgrid;

// forward declaration
class Pattern;

class Simulation
{
// member variables
private:
    vgrid currentGrid;          // grid in current generation
    vgrid nextGrid;             // grid in next generation
    unsigned generationCount;   // number of generations that have passed
    int width;                  // width of visible grid
    int height;                 // height of visible grid
    int bufCellCount;           // hidden buffer cells on all sides of grid

public:
    static const int SLEEP_MS = 50; // Sleep time between frames
    
// member functions    
private:
    // Gets whether a cell will be alive or dead next generation.
    bool getCellNextState(int, int);
    
    // Creates the specified vgrid with all values set to false.
    void initializeGrid(vgrid &);

    // Sets the specified vgrid to all false.
    void resetGrid(vgrid &);
    
public:
    // Instantiates a simulation object with a grid of the specified size.
    Simulation(int, int, int);
    
    // Adds a pattern to the current grid starting from x,y
    void addPattern(Pattern, int, int);
    
    // Advances the simulation to the next generation
    void advanceGeneration();

    // Prints the current state of the visible grid to the console
    void printCurrent();
    
    // Runs for specified number of generations and displays output in console.
    void runInConsole(int);
};
#endif // end of define SIMULATION_HPP
