/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/16/2014
 * Last Modification Date: 11/25/2014
 * Assignment:             Assignment 9
 * Filename:               shopCart2.cpp
 *
 * Overview:
 *     This program displays a menu that lets the user manipulate
 *     a shopping cart by adding items, listing items in the cart,
 *     and displaying the total cost of all items in the cart.
 * 
 * Input:
 *     menu selection (1 to 4)
 *     item name, price, and quantity when adding an item
 *
 * Output:
 *     The output to the console will be in the form of:
 *     Choose an item from the menu to manage your shopping cart.
 *
 *     1) Add item
 *     2) List contents
 *     3) Total price
 *     4) Quit
 *
 *     Enter your selection: [4]
 *
 *     Thank you for shopping with us!
 ************************************************************************/
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>

using namespace std;

// global constants
const int MAX_ITEMS = 100;
const int MAX_NAME_LEN = 40;
const double MAX_PRICE = 99999999.99;
const int MAX_QUANTITY = 99999999;

// represents an item in a shopping cart
class Item
{
    private:
        string name;    // name of item
        double price;   // price of item
        int quantity;   // quantity of item
        
    public:
        Item(const string &, double, int);            // constructor
        string getName() const { return name; }       // get name value
        double getPrice() const { return price; }     // get price value
        int getQuantity() const { return quantity; }  // get quantity of item
};

// represents a shopping cart
class ShoppingCart
{
    private:
        vector<Item> items; // items in cart
        
    public:
        void addItem(Item); // function prototypes
        void listItems() const;
        double totalPrice() const;
};

// member function implementations
/********************************************************************
 *  Three-argument constructor. Sets attributes to the specified values.
 *******************************************************************/
Item::Item(const string &nameVal, double priceVal, int qty)
{
    name = nameVal;
    price = priceVal;
    quantity = qty;
}

/********************************************************************
 *  void ShoppingCart::addItem(Item item)
 *
 *  Purpose: This function adds the specified item to the shopping cart.
 *
 *  Preconditions: none
 *
 *  Postconditions: Specified item is added to end of ShoppingCart.
 *******************************************************************/
void ShoppingCart::addItem(Item item)
{
    items.push_back(item);
}

/********************************************************************
 *  void ShoppingCart::listItems()
 *
 *  Purpose: This function lists the items in the specified array.
 *
 *  Preconditions: none
 *
 *  Postconditions: items in cart are displayed in console window.
 *******************************************************************/
void ShoppingCart::listItems() const
{
    cout << "\nYour cart contains the following:\n\n"
         << left << setw(MAX_NAME_LEN + 2) << "Product Name"
         << setw(15) << "Price"
         << setw(8) << "Quantity\n"
         << string (65, '-') << endl;
    if (items.size() < 1)
    {
        cout << "Cart empty\n";
    }
    for (int i = 0; i < items.size(); i++)
    {
        cout << left << setw(MAX_NAME_LEN + 2) << items[i].getName()
             << "$" << right << setw(11) << items[i].getPrice()
             << left << "   " << setw(10) << items[i].getQuantity()
             << endl;
    }
}

/********************************************************************
 *  double ShoppingCart::totalPrice()
 *
 *  Purpose: This function gets the total price of all items in the cart.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns the total price of all items in the cart.
 *******************************************************************/
double ShoppingCart::totalPrice() const
{
    double total = 0.0;
    for (int i = 0; i < items.size(); i++)
    {
        total += items[i].getPrice() * items[i].getQuantity();
    }
    
    return total;
}

// function prototypes
// Prints the menu.
void printMenu();
// Gets Item details from the user and adds an Item to the specified cart.
void addItem(ShoppingCart &);
// Shows the total cost of all items in the specified array.
void printTotal(const ShoppingCart &);
// Prompts the user for an integer in the specified range and returns it.
int getValidInt(const string &, 
                int = numeric_limits<int>::min(), 
                int = numeric_limits<int>::max());
// Prompts the user for a double in the specified range and returns it.
double getValidDouble(const string &, 
                      double = numeric_limits<double>::min(), 
                      double = numeric_limits<double>::max());
// Prompts the user for a string and validates the length.
string getValidString(const string &, int = 0, int = 0);
                          
int main()
{
    // declare variables
    ShoppingCart cart;  // holds items to purchase
    int selection;      // holds menu selection
    
    // menu loop
    do
    {
        // show the menu
        printMenu();
        
        // get user selection
        cout << "Enter your selection: ";
        cin >> selection;
        
        // parse selection
        if (cin.fail() ||
            cin.peek() != '\n' ||
            selection < 1 ||
            selection > 4 )
        {
            // invalid input
            cout << "Invalid selection. Try again.\n";
            // clear buffer if required
            if (cin.fail() || cin.peek() != '\n')
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            // reset menu selection
            selection = 0;
        }
        else
        {
            // consume newline
            cin.ignore();
            
            if (selection == 1)
            {
                // add item to cart
                addItem(cart);
            }
            else if (selection == 2)
            {
                // list items in cart
                cart.listItems();
            }
            else if (selection == 3)
            {
                // show total cost
                printTotal(cart);
            }
        }
    } while (selection != 4 && !cin.fail());

    cout << "\nThank you for shopping with us!\n";
    
    return 0;
}

/********************************************************************
 *  void printMenu()
 *
 *  Purpose: This function prints the menu to the console.
 *
 *  Preconditions: none
 *
 *  Postconditions: Menu is printed to the console.
 *******************************************************************/
void printMenu()
{
    cout << "\nChoose an item from the menu to manage your shopping cart.\n\n"
         << "1) Add item\n"
         << "2) List contents\n"
         << "3) Total price\n"
         << "4) Quit\n\n";
}

/********************************************************************
 *  void addItem(ShoppingCart &cart)
 *
 *  Purpose: This function gets Item details from the user
 *           and adds an Item to the specified ShoppingCart object.
 *
 *  Preconditions: none
 *
 *  Postconditions: cart contains an additional Item entered by the user.
 *******************************************************************/
void addItem(ShoppingCart &cart)
{
    string name;    // stores item name
    double price;   // stores item price
    int quantity;   // stores quantity of item
    
    // get user input
    name = getValidString(
        "\nEnter the product name: ", 1, MAX_NAME_LEN);
    price = getValidDouble(
        "\nEnter the price of the product: ", 0.0, MAX_PRICE);
    quantity = getValidInt(
        "\nEnter how many you want: ", 1, MAX_QUANTITY);
    
    // add new Item to cart
    cart.addItem(Item (name, price, quantity));
}

/********************************************************************
 *  void printTotal(const ShoppingCart &cart)
 *
 *  Purpose: This function shows the total cost of all items in the cart.
 *
 *  Preconditions: none
 *
 *  Postconditions: The total price is displayed in console window.
 *******************************************************************/
void printTotal(const ShoppingCart &cart)
{
    cout << "\nThe total price of the items in your cart is $"
         << fixed << showpoint << setprecision(2)
         << cart.totalPrice() << ".\n";
}

/********************************************************************
 *  int getValidInt(string prompt,
 *                  int min = numeric_limits<int>::min(),
 *                  int max = numeric_limits<int>::max())
 *
 *  Purpose: This function displays the specified prompt and gets a valid
 *           integer from the user within the specified range. The range
 *           defaults to the minimum and maximum int values if not specified.
 *
 *  Preconditions: none
 *
 *  Postconditions: Input buffer is empty.
 *                  Returns an integer value between min and max.
 *******************************************************************/
int getValidInt(const string &prompt, int min, int max)
{
    int input = 0; // for storing user input
    
    cout << prompt;
    cin >> input;
    
    // reprompt user until entire buffer except newline is consumed
    while (cin.peek() != '\n')
    {
        cout << "\nThat is not a valid integer.\n"
             << "Please enter a whole number between "
             << min << " and " // Min value
             << max            // Max value
             << ": ";
        
        // clear failbit and ignore rest of buffer
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cin >> input;
    }
    
    // recursively call until input is between min and max
    if (input < min || input > max)
    {
        cout << "\nThe number must be between "
             << min << " and " << max << ".";
        input = getValidInt(prompt, min, max);
    }
    
    // send input value back to caller
    return input;
}

/********************************************************************
 *  double getValidDouble(string prompt,
 *                        double min = numeric_limits<double>::min(),
 *                        double max = numeric_limits<double>::max())
 *
 *  Purpose: This function displays the specified prompt and gets a valid
 *           double from the user within the specified range. The range
 *           defaults to the min and max double values if not specified.
 *
 *  Preconditions: none
 *
 *  Postconditions: The input buffer is empty.
 *                  Returns a double value between min and max.
 *                  cout set to fixed, showpoint, and showprecision(2).
 *******************************************************************/
double getValidDouble(const string &prompt, double min, double max)
{
    double input = 0; // for storing user input
    
    cout << fixed << showpoint << setprecision(2);
    cout << prompt;
    cin >> input;
    
    // reprompt user until entire buffer except newline is consumed
    while (cin.peek() != '\n')
    {
        cout << "\nThat is not a valid number.\n"
             << "Please enter a real number between "
             << fixed << showpoint << setprecision(2)
             << min << " and " // Min value
             << max            // Max value
             << ": ";
        
        // clear failbit and ignore rest of buffer
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cin >> input;
    }
    
    // recursively call until input is between min and max
    if (input < min || input > max)
    {
        cout << "\nThe number must be between "
             << min << " and " << max << ".";
        input = getValidDouble(prompt, min, max);
    }
    
    // send input value back to caller
    return input;
}

/********************************************************************
 *  string getValidString(const string &prompt,
 *                        int minLen = 0,
 *                        int maxLen = 0)
 *
 *  Purpose: This function displays the specified prompt and gets a string 
 *           from the user within the specified length range. The range
 *           defaults to no limit if not specified.
 *           If the input is less than the minimum, the user is reprompted.
 *           If over the maximum, the input is truncated to max and returned.
 *
 *  Preconditions: none
 *
 *  Postconditions: The input buffer is empty.
 *                  Returns a string with a length between minLen and maxLen.
 *******************************************************************/
string getValidString(const string &prompt, int minLen, int maxLen)
{
    string input;  // stores user input
    
    // handle any error bits and leftover input
    cin.clear();
    cin.sync();
        
    // get input from user
    cout << prompt;
    getline(cin, input);
    
    // validate
    while (input.length() < minLen)
    {
        cout << "The input must contain at least " << minLen << " character"
             << (minLen == 1 ? ".\n" : "s.\n") << prompt;
        getline(cin, input);
    }
    
    // truncate if over maxLen
    if (input.length() > maxLen)
        input = input.substr(0, maxLen);
    
    return input;
}
