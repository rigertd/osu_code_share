/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/30/2015
 * Last Modified:   1/31/2015
 * Assignment:      Assignment 2
 * Filename:        ShoppingList.hpp
 *
 * Description:     Represents a shopping list containing items to purchase.
 ************************************************************************/
#ifndef SHOPPING_LIST_HPP
#define SHOPPING_LIST_HPP

#include <string>   // std::string
#include <vector>   // std::vector
#include <ostream>  // std::ostream

class Item;

class ShoppingList
{
private:
    /*==================== Private Member Variables ===================*/
    std::vector<Item> list; // items in the shopping list
    std::string filename;   // current filename (if any).
    bool modified;          // whether list has been modified since last save
    
    /*==================== Private Member Functions ===================*/
    // gets the total price of all items on list formatted as a string
    std::string getFormattedTotal();
    
    // gets total price of all items on list
    double getTotalCost();
    
    // prints header row as single line of text to terminal window
    void printHeaderRow();
    
public:
    /*======================== Static Constants =======================*/
    static const std::string DEFAULT_FILENAME;

    /*========================= Constructors ==========================*/
    /********************************************************************
     *  Function:       ShoppingList()
     *  Description:    The default constructor. Sets the modified flag to
     *                  false and the filename to the default.
     *******************************************************************/
    ShoppingList()
    {
        this->modified = false;
        this->filename = DEFAULT_FILENAME;
    }
    
    /*==================== Public Member Functions ====================*/
    // gets whether modified since last save
    /********************************************************************
     *  Function:       bool isModified()
     *  Description:    Gets whether the ShoppingList has been modified
     *                  since the last time it was saved.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns whether the list has been modified.
     *******************************************************************/
    bool isModified()   
    {
        return modified;
    }
    
    // prompts user for input and adds item to list
    void addItem();
    
    // prompts user to select and edit an existing item
    void editItem();
    
    // prompts user to select an item to remove from list
    void removeItem();
    
    // displays the items to the terminal window
    void listItems();
    
    // saves list to default or user-specified file
    void saveList();
    
    // loads list from default or user-specified file
    void loadList();
};

#endif  // end of SHOPPING_LIST_HPP include guard