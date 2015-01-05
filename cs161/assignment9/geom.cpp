/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/23/2014
 * Last Modification Date: 11/23/2014
 * Assignment:             Assignment 9
 * Filename:               geom.cpp
 *
 * Overview:
 *     This program prompts the user for the coordinates of two points and
 *     prints the length and slope of the line segment that is formed.
 *     This process can be repeated until the user chooses to exit.
 * 
 * Input:
 *     X and Y coordinates for two points
 *     'y' to enter new coordinates
 *
 * Output:
 *     The output is the length and slope of the line segment formed by the
 *     specified point coordinates.
 *     The output to the console will be in the form of:
 *
 *     This program finds the length and slope of a line segment.
 *
 *     Enter the X and Y coordinate of point 1, separated by a space.
 *     [0 0]
 *     Enter the X and Y coordinate of point 2, separated by a space.
 *     [3 4]
 *
 *     You entered a line segment from (0,0) to (3,4).
 *     Your line segment has a length of 5 and has a slope of 1.33333.
 *
 *     Enter another line segment? (Y/N): [n]
 ************************************************************************/
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// represents a point on a graph
class Point
{
    private:
        double x, y;                      // X and Y coordinates
        
    public:
        Point();                          // default constructor
        Point(double, double);            // constructor
        double distanceTo(const Point &); // function prototype
        double getX() {return x;};        // returns X value
        double getY() {return y;};        // returns Y value
};

// represents a line segment
class LineSegment
{
    private:
        Point p1, p2;               // endpoints of line segment
    
    public:
        LineSegment();              // default constructor
        LineSegment(Point, Point);  // constructor
        double length();            // function prototypes
        double slope();
};

// member function implementations
/********************************************************************
 *  Default constructor. Sets X and Y to 0.
 *******************************************************************/
Point::Point()
{
    x = y = 0;
}

/********************************************************************
 *  Two-argument constructor. Sets X and Y to the specified values.
 *******************************************************************/
Point::Point(double xVal, double yVal)
{
    x = xVal;
    y = yVal;
}

/********************************************************************
 *  double distanceTo(const Point &p)
 *
 *  Purpose: This function finds the distance from the current point
 *           to the specified point.
 *
 *  Preconditions: none
 *
 *  Postconditions: returns the distance as a double value
 *******************************************************************/
double Point::distanceTo(const Point &p)
{
    double dX = x - p.x;    // X delta
    double dY = y - p.y;    // Y delta
    
    // Use a^2 + b^2 = c^2
    return sqrt((dX * dX) + (dY * dY));
}

/********************************************************************
 *  Default constructor. Sets both endpoints to (0,0).
 *******************************************************************/
LineSegment::LineSegment()
{
    // nothing needed because default point constructor already does this
}

/********************************************************************
 *  Two-argument constructor. Sets points to specified Point values.
 *******************************************************************/
LineSegment::LineSegment(Point p1Val, Point p2Val)
{
    p1 = p1Val;
    p2 = p2Val;
}

/********************************************************************
 *  double length()
 *
 *  Purpose: This function gets the length of the line segment.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns the length as a double value.
 *******************************************************************/
double LineSegment::length()
{
    return p1.distanceTo(p2);
}

/********************************************************************
 *  double slope()
 *
 *  Purpose: This function gets the slope of the line segment.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns the slope as a double value.
 *                  Returns infinity if vertical line.
 *******************************************************************/
double LineSegment::slope()
{
    // slope is (y1 - y2)/(x1 - x2)
    return (p1.getY() - p2.getY())/(p1.getX() - p2.getX());
}

// constant declarations
const int NUM_POINTS = 2;   // number of points to get input for

// function prototype
// Prompts user for yes/no answer and returns true if yes/no
bool getYesNo(const string &);

int main()
{
    cout << "This program finds the length and slope of a line segment.\n\n";
    
    // start of replay loop
    do
    {
        Point points[NUM_POINTS];
        
        for (int i = 0; i < NUM_POINTS; i++)
        {
            double x, y;    // stores user input for X and Y coordinates

            cout << "Enter the X and Y coordinate of point " << i+1 
                 << ", separated by a space.\n";
            cin >> x >> y;
            
            // store in Point array
            points[i] = Point (x, y);
        }
        
        // create line segment from points
        LineSegment lSeg = LineSegment (points[0], points[1]);
        
        cout << "\nYou entered a line segment from (" << points[0].getX()
             << "," << points[0].getY() << ") to (" << points[1].getX()
             << "," << points[1].getY() << ").\n";
        cout << "Your line segment has a length of " << lSeg.length();
        
        // have to check if slope is infinity
        double slope = lSeg.slope();
        if (isinf(slope))
            cout << " and is vertical.\n\n";
        else
            cout << " and has a slope of " << slope << ".\n\n";
    
    // repeat until user enters a word that starts with 'n'
    } while (getYesNo("Enter another line segment? (Y/N): "));
}

/********************************************************************
 *  bool getYesNo(string prompt)
 *
 *  Purpose: This function displays the specified prompt until the first
 *           char of the input is 'Y', 'y', 'N', or 'n'.
 *
 *  Preconditions: none
 *
 *  Postconditions: input buffer is empty and returns true if 'y' or 'Y'
 *******************************************************************/
bool getYesNo(const string &prompt)
{
    char input; // for storing user input
    
    cout << prompt;
    cin >> input;
    
    // Flushes buffer and reprompts until valid value is entered.
    while (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
    {
        cout << "Please type yes or no: ";
        cin.clear();     // Clear any errors.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;    // Store console input in 'input' variable.
    }
    
    // Clear any text left in buffer.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return input == 'Y' || input == 'y';
}
