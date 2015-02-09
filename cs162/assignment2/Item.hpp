/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/30/2015
 * Last Modified:   1/31/2015
 * Assignment:      Assignment 2
 * Filename:        Item.hpp
 *
 * Description:     Represents an item to purchase on a shopping list.
 ************************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>   // std::string
#include <ostream>  // std::ostream

class Item
{
private:
    /*==================== Private Member Variables ===================*/
    std::string name;       // name of item
    std::string unit;       // unit of sale
    double unitPrice;       // price per unit
    double quantity;        // amount in units

    /*==================== Private Member Functions ===================*/
    // gets the total cost of the specified quantity as a formatted string
    std::string getFormattedTotal();
    
    // gets the unit price as a formatted string
    std::string getFormattedPrice();
    
    // gets the quantity as a formatted string
    std::string getFormattedQuantity();

public:
    /*======================== Static Constants =======================*/
    static const int NAME_LEN;
    static const int PRICE_LEN;
    static const int QUANTITY_LEN;
    static const int SUBTOTAL_LEN;
    
    
    /*========================= Constructors ==========================*/
    /********************************************************************
     *  Function:       Item()
     *  Description:    The default constructor. Sets name and unit to
     *                  empty strings and price and quantity to 0.
     *******************************************************************/
    Item()
    {
        this->unitPrice = 0.0;
        this->quantity = 0.0;
    }
    
    /********************************************************************
     *  Function:       Item(std::string name, std::string unit, 
     *                       double unitPrice, double quantity)
     *  Description:    Instantiates a Pattern with the specified name
     *                  and pattern.
     *  Parameters:     name        Name of item
     *                  unit        Unit of purchase
     *                  unitPrice   Price per unit
     *                  quantity    Quantity to purchase
     *******************************************************************/
    Item(std::string name, std::string unit, double unitPrice, double quantity):
        name(name), unit(unit), unitPrice(unitPrice), quantity(quantity)
    {
        // set members using initialization list
    }
    
    // deserialization constructor
    Item(std::string &);
    
    /*=================== Public Member Functions =====================*/
    // converts object to tab-delimited string
    std::string convertToTabDelim();
    
    /********************************************************************
     *  Function:       std::string getName()
     *  Description:    Gets the name of the item.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns the name of the item
     *******************************************************************/
    std::string getName()
    {
        return this->name;
    }
    
    /********************************************************************
     *  Function:       double getTotal()
     *  Description:    Gets the total price of the item as a double.
     *  Parameters:     none
     *  Preconditions:  none
     *  Postconditions: Returns the total price of the item
     *******************************************************************/
    double getTotal()
    {
        return this->quantity * this->unitPrice;
    }
    
    // prompts user for new information and updates object
    void edit();
    
    /*======================== Friend Functions =======================*/
    // converts item to single line of text for display
    friend std::ostream &operator<<(std::ostream &out, Item itm);
};

#endif  // end of ITEM_HPP include guard