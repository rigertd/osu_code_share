/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/16/2014
 * Last Modification Date: 11/17/2014
 * Assignment:             Assignment 8
 * Filename:               shopCart.cpp
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

using namespace std;

struct Item
{
    string name;
    double price;
    int quantity;
};

// function prototypes
// Prints the menu.
void printMenu();
// Gets Item details from the user and adds an Item to the specified array.
void addItem(Item [], int &, const int);
// Lists the items in the specified array.
void listItems(const Item [], const int);
// Shows the total cost of all items in the specified array.
void printTotal(const Item [], const int);
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
                          
// global constants
const int MAX_ITEMS = 100;
const int MAX_NAME_LEN = 40;
const double MAX_PRICE = 99999999.99;
const int MAX_QUANTITY = 99999999;

int main()
{
    // declare variables
    Item shoppingCart[MAX_ITEMS];   // shopping cart
    int itemCount = 0;              // number of items in cart
    int selection;                  // holds menu selection
    
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
        else if (selection == 1)
        {
            // add item to cart
            addItem(shoppingCart, itemCount, MAX_ITEMS);
        }
        else if (selection == 2)
        {
            // list items in cart
            listItems(shoppingCart, itemCount);
        }
        else if (selection == 3)
        {
            // show total cost
            printTotal(shoppingCart, itemCount);
        }
    } while (selection != 4 && !cin.fail());

    cout << "\nThank you for shopping with us!\n";
    
    return 0;
}

/**
    void printMenu()
    
    Purpose:
        This function prints the menu to the console.
    
    Preconditions:
        None.
    
    Postconditions:
        Menu is printed to the console.
 */
void printMenu()
{
    cout << "\nChoose an item from the menu to manage your shopping cart.\n\n"
         << "1) Add item\n"
         << "2) List contents\n"
         << "3) Total price\n"
         << "4) Quit\n\n";
}

/**
    void addItem(Item cart[], int &count, const int max)
    
    Purpose:
        This function gets Item details from the user
        and adds an Item to the specified array, up to max items.
    
    Preconditions:
        cart is initialized with max elements
        count < max
    
    Postconditions:
        cart contains an additional Item entered by the user
        count is incremented by 1
 */
void addItem(Item cart[], int &count, const int max)
{
    if (count >= max)
    {
        cout << "\nCannot add any more items. Your cart is full.\n\n";
    }
    else
    {
        // consume line feed in buffer
        if (cin.peek() == '\n')
            cin.ignore();

        // get user input
        cart[count].name = getValidString(
            "\nEnter the product name: ", 1, MAX_NAME_LEN);
        cart[count].price = getValidDouble(
            "\nEnter the price of the product: ", 0.0, MAX_PRICE);
        cart[count].quantity = getValidInt(
            "\nEnter how many you want: ", 1, MAX_QUANTITY);
        
        // increment counter
        count++;
    }
}

/**
    void listItems(const Item cart[], const int count)
    
    Purpose:
        This function lists the items in the specified array.
    
    Preconditions:
        cart is initialized and contains count Items
    
    Postconditions:
        items in cart are displayed in console window
 */
void listItems(const Item cart[], const int count)
{
    cout << "\nYour cart contains the following:\n\n"
         << left << setw(MAX_NAME_LEN + 2) << "Product Name"
         << setw(15) << "Price"
         << setw(8) << "Quantity\n"
         << string (65, '-') << endl;
    if (count < 1)
    {
        cout << "Cart empty\n";
    }
    for (int i = 0; i < count; i++)
    {
        cout << left << setw(MAX_NAME_LEN + 2) << cart[i].name
             << "$" << right << setw(11) << cart[i].price
             << left << "   " << setw(10) << cart[i].quantity
             << endl;
    }
}

/**
    void printTotal(const Item cart[], const int count)
    
    Purpose:
        This function shows the total cost of all items
        in the specified array.
    
    Preconditions:
        cart is initialized and contains count Items
    
    Postconditions:
        total cost is displayed in console window
 */
void printTotal(const Item cart[], const int count)
{
    double total = 0.0;
    for (int i = 0; i < count; i++)
    {
        total += cart[i].price * cart[i].quantity;
    }
    
    cout << "\nThe total price of the items in your cart is $"
         << fixed << showpoint << setprecision(2)
         << total << ".\n";
}

/**
    int getValidInt(string prompt,
                        int min = numeric_limits<int>::min(),
                        int max = numeric_limits<int>::max())
 
    Purpose: 
        This function displays the specified prompt and gets a valid integer 
        from the user within the specified range. The range defaults to 
        the minimum and maximum int values if not specified.

    Preconditions:
        none
 
    Postconditions: 
        input buffer is empty
        returns an integer value between min and max
 */
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

/**
    double getValidDouble(string prompt,
                              double min = numeric_limits<double>::min(),
                              double max = numeric_limits<double>::max())
 
    Purpose: 
        This function displays the specified prompt and gets a valid double 
        from the user within the specified range. The range defaults to 
        the minimum and maximum double values if not specified.

    Preconditions:
        none
 
    Postconditions: 
        input buffer is empty
        returns a double value between min and max
        cout set to fixed, showpoint, and showprecision(2)
 */
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

/**
    string getValidString(const string &prompt,
                              int minLen = 0,
                              int maxLen = 0)
 
    Purpose: 
        This function displays the specified prompt and gets a string 
        from the user within the specified length range. The range
        defaults to no limit if not specified.
        The user is reprompted if the input is less than the minimum,
        but the input is truncated and returned if it is over the maximum.

    Preconditions:
        none
 
    Postconditions: 
        input buffer is empty
        returns a string with a length between minLen and maxLen
 */
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
