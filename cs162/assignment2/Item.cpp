/*************************************************************************
 * Author:          David Rigert
 * Date Created:    1/30/2015
 * Last Modified:   1/31/2015
 * Assignment:      Assignment 2
 * Filename:        Item.cpp
 *
 * Description:     Implementation of the Item class. 
 ************************************************************************/
#include "Item.hpp"

#include <iomanip>      // std::setprecision, std::fixed
#include <iostream>     // std::cin, std::cout, std::getline, std::endl
#include <sstream>      // std::ostringstream
#include <stdexcept>    // std::invalid_argument
#include <cstdlib>      // std::strtod

#include "utility.hpp"  // isDouble()

/*========================== Static Constants ==========================*/
const int Item::NAME_LEN = 35;      // width of name column
const int Item::PRICE_LEN = 10;     // width of price column
const int Item::QUANTITY_LEN = 15;  // width of quantity column
const int Item::SUBTOTAL_LEN = 10;  // width of subtotal column

/*============================ Constructors ============================*/
/*************************************************************************
 *  Function:       Item::Item(std::string &serialized)
 *  Description:    Deserializes a tab-delimited Item string
 *                  an instantiates an object.
 *  Parameters:     serialized  Item serialized as tab-delimited string
 ************************************************************************/
Item::Item(std::string &serialized)
{
    // put name in separate string
    size_t pos = serialized.find('\t', 0);
    this->name = serialized.substr(0, pos);

    // tokenize price and quantity using a stringstream object
    std::istringstream iss (serialized.substr(pos));
    iss >> this->unitPrice;
    iss >> this->quantity;
    
    // get remainder of stringstream for unit
    iss.ignore(1000, '\t');
    std::getline(iss, this->unit);
    
    // throw exception on invalid serialized data
    if (iss.fail())
        throw std::invalid_argument("ERROR: Invalid Item data.");
}
    
/*====================== Private Member Functions ======================*/
/*************************************************************************
 *  Function:       std::string Item::getFormattedTotal()
 *  Description:    Gets the total cost of the specified quantity as 
 *                  a formatted string.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Returns unitPrice * quantity as a string with 2 digits
 *                  after the decimal point and prepended with '$'.
 ************************************************************************/
std::string Item::getFormattedTotal()
{
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2)
        << (this->quantity * this->unitPrice);
    return oss.str();
}

/*************************************************************************
 *  Function:       std::string Item::getFormattedPrice()
 *  Description:    Gets the unit price as a formatted string.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Returns unitPrice as a string with 2 digits after
 *                  the decimal point and prepended with '$'.
 ************************************************************************/
std::string Item::getFormattedPrice()
{
    std::ostringstream oss;
    oss << "$" << std::fixed << std::setprecision(2)
        << (this->unitPrice);
    return oss.str();
}

/*************************************************************************
 *  Function:       std::string Item::getFormattedQuantity()
 *  Description:    Gets the quantity and unit as a formatted string
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Returns quantity as a string followed by a space and
 *                  the unit string.
 ************************************************************************/
std::string Item::getFormattedQuantity()
{
    std::ostringstream oss;
    oss << this->quantity << " " << this->unit;
    return oss.str();
}

/*======================= Public Member Functions ======================*/
/*************************************************************************
 *  Function:       void Item::edit()
 *  Description:    Prompts the user for new information and updates 
 *                  the Item object.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Member variables are updated if valid data was entered.
 ************************************************************************/
void Item::edit()
{
    // user input variables
    std::string name;
    std::string unit;
    std::string unitPrice;
    std::string quantity;
    
    // for conversion to double
    double newUnitPrice = 0.0;
    double newQuantity = 0.0;
    
    // display current 'name' value and prompt for new one
    std::cout << "The current name is \"" << getName() << "\".\n"
              << "Type a new name or press Enter to keep it: ";
    std::getline(std::cin, name);
    
    // display current 'unitPrice' value and prompt for new one
    std::cout << "The current price is " 
              << getFormattedPrice() << ".\n"
              << "Type a new price or press Enter to keep it: $";
    std::getline(std::cin, unitPrice);
    
    // validate user input
    if (unitPrice.empty())
    {
        // keep old value
    }
    else if ( !isDouble(unitPrice))
    {
        std::cout << "Invalid price entered. Aborting edit.\n";
        return;
    }
    else
    {
        newUnitPrice = std::strtod(unitPrice.c_str(), NULL);
        if (newUnitPrice < 0)   // must be at least 0
        {
            std::cout << "\nThe store will not pay you to take its goods.\n";
            return;
        }
    }
    
    // display current 'quantity' value and prompt for new one
    std::cout << "The current quantity is "
              << getFormattedQuantity() << ".\n"
              << "Type a new quantity or press Enter to keep it: ";
    std::getline(std::cin, quantity);
    
    // validate user input
    if (quantity.empty())
    {
        // keep old value
    }
    else if (!isDouble(quantity))
    {
        std::cout << "Invalid quantity entered. Aborting edit.\n";
        return;
    }
    else
    {
        newQuantity = std::strtod(quantity.c_str(), NULL);
        if (newQuantity <= 0)   // must be greater than 0
        {
            std::cout << "\nThe store does not buy goods from customers.\n";
            return;
        }
    }
    
    // prompt for new 'unit'
    std::cout << "Type a new unit or press Enter to keep it: ";
    std::getline(std::cin, unit);
    
    // if execution reaches here, all input was valid.
    // test for non-empty input and set member variables accordingly.
    if (!name.empty())
        this->name = name;
    if (!unit.empty())
        this->unit = unit;
    if (!unitPrice.empty())
        this->unitPrice = newUnitPrice;
    if (!quantity.empty())
        this->quantity = newQuantity;
}

/*************************************************************************
 *  Function:       std::string Item::convertToTabDelim()
 *  Description:    Serializes the Item object as a tab-delimited string.
 *  Parameters:     none
 *  Preconditions:  none
 *  Postconditions: Returns the serialized Item object.
 ************************************************************************/
std::string Item::convertToTabDelim()
{
    std::ostringstream oss;
    oss << name << "\t" 
        << std::setprecision(2) << std::fixed   // price formatting
        << unitPrice << "\t"
        << std::resetiosflags(std::ios::fixed)  // turn off for quantity
        << std::setprecision(16)
        << quantity << "\t"
        << unit;
    return oss.str();
}
    
/*========================== Friend Functions ==========================*/
/*************************************************************************
 *  Function:       std::ostream &operator<<(std::ostream &out, Item itm)
 *  Description:    Converts the specified Item into an 80-character line 
 *                  of text for display in the terminal window.
 *                  Truncates any attributes that exceed the column width.
 *  Parameters:     out     An ostream object
 *                  itm     The Item object to display
 *  Preconditions:  none    
 *  Postconditions: Returns a reference to the ostream object.
 ************************************************************************/
std::ostream &operator<<(std::ostream &out, Item itm)
{
    out << std::left << std::setw(Item::NAME_LEN)
        << itm.name.substr(0, Item::NAME_LEN) << " "
        << std::right << std::setw(Item::PRICE_LEN)
        << itm.getFormattedPrice().substr(0, Item::PRICE_LEN) << " "
        << std::left << std::setw(Item::QUANTITY_LEN)
        << itm.getFormattedQuantity().substr(0, Item::QUANTITY_LEN) << " "
        << std::right << std::setw(Item::SUBTOTAL_LEN)
        << itm.getFormattedTotal().substr(0, Item::SUBTOTAL_LEN) << std::left;
    
    return out;
}
