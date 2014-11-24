/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/17/2014
 * Last Modification Date: 11/18/2014
 * Assignment:             Assignment 8
 * Filename:               carLot.cpp
 *
 * Overview:
 *     This program is a rudimentary menu-driven inventory management tool
 *     for a car dealer. The user can enter data on cars that are still on
 *     the lot and cars that have been sold. The user can also list unsold
 *     inventory and the profit for any given month.
 * 
 * Input:
 *     menu selection
 *     car and sale data
 *
 * Output:
 *     The output to the console will be in the form of:
 *
 *     Choose an item from the menu.
 *
 *     1) Add entry
 *     2) List current inventory
 *     3) Profit for a month
 *     4) Quit
 *
 *     Enter your selection:
 ************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <iomanip>
#include <cstdlib>

// margin between columns
#define MARGIN "  "

using namespace std;

// represents a date
struct Date
{
    int day,
        month,
        year;
};

// represents current or past inventory on a car dealer lot
struct Car
{
    string make,
           model;
    int year;
    Date datePurchased,
         dateSold;
    double purchasePrice,
           salePrice;
    bool isSold;
};

// function prototypes
// Adds a car entry to the system.
void addEntry(vector<Car> &);
// Lists all unsold cars in inventory.
void listInventory(const vector<Car> &);
// Prints the menu.
void printMenu();
// Prompts user for a month and year and prints the profit.
void printProfit(const vector<Car> &);

/********************************************************************
 *  user input functions
 *******************************************************************/
// Gets an amount from the user as a double.
double getAmount(const string &, double, double);
// Gets valid month, day and year values from the user.
void getDate(const string &, int &, int &, int &);
// Gets valid month and year values from the user.
void getMonthYear(int &, int &);
// Gets a string of length minLen to maxLen from the user.
string getString(const string &, int, int);
// Gets valid year value from the user.
int getYear(const string &);
// Prompts user for yes/no answer and returns true if yes/no
bool getYesNo(const string &);

/********************************************************************
 *  helper functions
 *******************************************************************/
// Determines whether a string is a valid double.
bool isDouble(const string &);
// Determines whether a string is a valid integer.
bool isInteger(const string &);
// Splits a string on the specified delimiter.
vector<string> split(const string &, char = ' ');

// global constants
const short MAKE_MAX_LEN = 20;
const short MODEL_MAX_LEN = 20;
const short DATE_LEN = 10;
const short PRICE_LEN = 10;
const double PRICE_MAX = 9999999.99;

int main()
{
    // declare variables
    vector<Car> ledger;   // inventory ledger
    string input;         // user input buffer
    short selection;      // holds menu selection
    
    // menu loop
    do
    {
        // show the menu
        printMenu();
        
        // get user selection
        cout << "Enter your selection: ";
        getline(cin, input);

        // parse selection
        if (!isInteger(input))
        {
            cout << "Invalid input. Please enter a number 1-4.\n";
        }
        else
        {
            // convert user input to short int
            selection = atoi(input.c_str());
            
            if (selection < 1 || selection > 4 )
            {
                // invalid range
                cout << "Invalid selection. Try again.\n";
                // reset menu selection
                selection = 0;
            }
            else if (selection == 1)
            {
                // add entry to ledger
                addEntry(ledger);
            }
            else if (selection == 2)
            {
                // list inventory on lot
                listInventory(ledger);
            }
            else if (selection == 3)
            {
                // show profit for specified month
                printProfit(ledger);
            }
        }
    } while (selection != 4 && !cin.fail());

    cout << "\nDestroying ledger. Thank you for wasting your time.\n";
    
    return 0;
}

/**
    void addEntry(vector<Car> &ledger)
    
    Purpose:
        This function adds a car entry to the system.
    
    Preconditions:
        none
    
    Postconditions:
        User input is stored in a new element of ledger.
 */
void addEntry(vector<Car> &ledger)
{
    string input;   // user input buffer
    Car temp;       // stores input
    
    // get make
    temp.make = getString("Enter the make: ", 1, MAKE_MAX_LEN);
    
    // get model
    temp.model = getString("Enter the model: ", 1, MODEL_MAX_LEN);
    
    // get year
    temp.year = getYear("Enter the year: ");
    
    // get datePurchased
    getDate("Enter the purchase date as MM/DD/YYYY: ", 
            temp.datePurchased.month,
            temp.datePurchased.day,
            temp.datePurchased.year);
    
    // get purchasePrice
    temp.purchasePrice = getAmount("Enter the purchase price: $", 0, PRICE_MAX);
    
    // get isSold value
    temp.isSold = getYesNo("Has this car already been sold? (Y/N): ");
    
    if (temp.isSold)
    {
        // get dateSold
        getDate("Enter the date sold as MM/DD/YYYY: ",
                temp.dateSold.month,
                temp.dateSold.day,
                temp.dateSold.year);
    
        // get salePrice
        temp.salePrice = getAmount("Enter the sale price: $", 0, PRICE_MAX);
    }
    
    // add temp struct to vector
    ledger.push_back(temp);
}

/**
    void listInventory(const vector<Car> &ledger)
    
    Purpose:
        This function lists all unsold cars in inventory.
    
    Preconditions:
        none
    
    Postconditions:
        All unsold cars in ledger are printed to the console.
 */
void listInventory(const vector<Car> &ledger)
{
    unsigned int unsold = 0;
    
    // header row
    cout << "\nYou have the following unsold cars on the lot:\n\n"
         << setfill(' ') << left << setw(MAKE_MAX_LEN) << "Make" << MARGIN
         << setw(MODEL_MAX_LEN) << "Model" << MARGIN
         << setw(4) << "Year" << MARGIN
         << setw(DATE_LEN) << "Purchased" << MARGIN
         << setw(PRICE_LEN + 1) << "Price Paid" << MARGIN
         << endl << string (73, '-') << endl;
    for (int i = 0; i < ledger.size(); i++)
    {
        // print only if not sold
        if (!ledger[i].isSold)
        {
            cout << left << setw(MAKE_MAX_LEN) << ledger[i].make << MARGIN
                 << setw(MODEL_MAX_LEN) << ledger[i].model << MARGIN << right
                 << setfill('0') << setw(4) << ledger[i].year << MARGIN
                 << setw(2) << ledger[i].datePurchased.month << "/"
                 << setw(2) << ledger[i].datePurchased.day << "/"
                 << setw(4) << ledger[i].datePurchased.year << MARGIN
                 << setfill(' ') << fixed << showpoint
                 << "$" << setprecision(2) << setw(PRICE_LEN) 
                 << ledger[i].purchasePrice << left << endl;
            
            unsold++;
        }
    }
    cout << "\nYou have " << unsold << " unsold car"
         << (unsold == 1 ? " " : "s ") << "on the lot.\n\n";
}

/**
    void printMenu()
    
    Purpose:
        This function prints the menu to the console.
    
    Preconditions:
        none
    
    Postconditions:
        Menu is printed to the console.
 */
void printMenu()
{
    cout << "\nChoose an item from the menu.\n\n"
         << "1) Add entry\n"
         << "2) List current inventory\n"
         << "3) Profit for a month\n"
         << "4) Quit\n\n";
}

/**
    void printProfit(const vector<Car> &ledger)
    
    Purpose:
        This function prompts the user for a month and year and prints the
        total profit from all cars sold within the specified month and year.
    
    Preconditions:
        ledger is initialized
    
    Postconditions:
        total cost is displayed in console window
 */
void printProfit(const vector<Car> &ledger)
{
    double profit = 0.0;      // total profit for month
    int month = 0, year = 0;  // numerical month and year
    
    // get valid month and year
    getMonthYear(month, year);
    
    for (int i = 0; i < ledger.size(); i++)
    {
        // only count if correct month and year
        if (ledger[i].dateSold.month == month && 
            ledger[i].dateSold.year == year)
            profit += ledger[i].salePrice - ledger[i].purchasePrice;
    }
    
    cout << "\nYour total profit for " 
         << right << setfill('0') << setw(2) << month << "/" 
         << right << setfill('0') << setw(4) << year << " was $"
         << left << fixed << showpoint << setprecision(2) << profit << ".\n";
}

/**
    double getAmount(const string &prompt, double min, double max)
    
    Purpose:
        This function prompts the user for an amount of money and validates 
        the input. The user is reprompted until a valid value is entered.
    
    Preconditions:
        none
    
    Postconditions:
        returns entered amount
 */
double getAmount(const string &prompt, double min, double max)
{
    string input;   // user input buffer
    double amt;     // amount value
    bool valid;     // store isDouble result
    
    do
    {
        cout << prompt;
        getline(cin, input);
        valid = isDouble(input);
        
        // validate input
        if (valid)
        {
            amt = atof(input.c_str());
            if (amt < min || amt > max)
            {
                cout << "Invalid amount. " 
                     << "Enter a value between "
                     << fixed << showpoint << setprecision(2)
                     << min << " and " << max << ".\n";
                
                // set valid flag to false
                valid = false;
            }
        }
        else
            cout << "Invalid amount.\n";
    } while (!valid);
    
    return amt;
}

/**
    void getDate(const string &prompt, int &month, int &day, int &year)
    
    Purpose:
        This function prompts the user for the month, day and year
        and validates the input. The user is reprompted until 
        valid values are entered.
    
    Preconditions:
        none
    
    Postconditions:
        month, day and year contain the entered month, day and year
 */
void getDate(const string &prompt, int &month, int &day, int &year)
{
    string input;         // user input buffer
    vector<string> date;  // split month, day and year
    
    do
    {
        cout << prompt;
        getline(cin, input);
        
        // split on slash
        date = split(input, '/');
        
        // validate input length
        if (date.size() != 3)
            cout << "Invalid date format.\n";
        else
        {
            // validate month
            if (isInteger(date[0]))
            {
                month = atoi(date[0].c_str());
                if (month < 1 || month > 12 || date[0].length() > 2)
                {
                    cout << "Invalid month. "
                         << "Enter a number between 1 and 12.\n";
                    month = day = year = 0;
                    // cannot detect valid day without valid month
                    continue;
                }
            }
            else
                cout << "Invalid month.\n";
            
            // validate day
            if (isInteger(date[1]))
            {
                int maxDay;
                // set maxDay based on month
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    maxDay = 30;
                else if (month == 2)
                    maxDay = 28;
                else
                    maxDay = 31;
                
                day = atoi(date[1].c_str());
                if (day < 1 || day > maxDay || date[1].length() > 2)
                {
                    cout << "Invalid day. "
                         << "Enter a number between 1 and " << maxDay <<".\n";
                    month = day = year = 0;
                }
            }
            else
                cout << "Invalid year.\n";
            
            // validate year
            if (isInteger(date[2]))
            {
                year = atoi(date[2].c_str());
                if (year < 1 || year > 9999 || date[2].length() != 4)
                {
                    cout << "Invalid year. "
                         << "Enter a number between 0001 and 9999.\n";
                    month = day = year = 0;
                }
            }
            else
                cout << "Invalid year.\n";
        }
    } while (month == 0 || day == 0 || year == 0);
}

/**
    void getMonthYear(int &month, int &year)
    
    Purpose:
        This function prompts the user for a month and a year
        and validates the input. The user is reprompted until 
        valid values are entered.
    
    Preconditions:
        none
    
    Postconditions:
        month and year contain the entered month and year
 */
void getMonthYear(int &month, int &year)
{
    string input;              // user input buffer
    vector<string> monthYear;  // split month and year
    
    do
    {
        cout << "Enter the month and year as MM/YYYY: ";
        getline(cin, input);
        
        // split on slash
        monthYear = split(input, '/');
        
        // validate input length
        if (monthYear.size() != 2)
            cout << "Invalid date format.\n";
        else
        {
            // validate month
            if (isInteger(monthYear[0]))
            {
                month = atoi(monthYear[0].c_str());
                if (month < 1 || month > 12 || monthYear[0].length() > 2)
                {
                    cout << "Invalid month. "
                         << "Enter a number between 1 and 12.\n";
                    month = year = 0;
                }
            }
            else
                cout << "Invalid month.\n";
            // validate year
            if (isInteger(monthYear[1]))
            {
                year = atoi(monthYear[1].c_str());
                if (year < 1 || year > 9999 || monthYear[1].length() != 4)
                {
                    cout << "Invalid year. "
                         << "Enter a number between 0001 and 9999.\n";
                    month = year = 0;
                }
            }
            else
                cout << "Invalid year.\n";
        }
    } while (month < 1 || month > 12 || year < 1 || year > 9999);
}

/**
    string getString(const string &prompt,
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
string getString(const string &prompt, int minLen, int maxLen)
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

/**
    int getYear(const string &prompt)
    
    Purpose:
        This function prompts the user for a year and validates 
        the input. The user is reprompted until a valid value is entered.
    
    Preconditions:
        none
    
    Postconditions:
        returns entered year value
 */
int getYear(const string &prompt)
{
    string input;   // user input buffer
    int year;     // year value
    
    do
    {
        cout << prompt;
        getline(cin, input);
        
        // validate year
        if (isInteger(input))
        {
            year = atoi(input.c_str());
            if (year < 1 || year > 9999 || input.length() != 4)
            {
                cout << "Invalid year. "
                     << "Enter a number between 0001 and 9999.\n";
                year = 0;
            }
        }
        else
            cout << "Invalid year.\n";
    } while (year < 1 || year > 9999);
    
    return year;
}

/**
    bool getYesNo(string prompt)

    Purpose: 
        This function displays the specified prompt until the first char 
        of the input is 'Y', 'y', 'N', or 'n'.
  
    Preconditions: 
        none
     
    Postconditions: 
        input buffer is empty and returns true if 'y' or 'Y'
 */
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

/**
    bool isDouble(const string &str)
    
    Purpose:
        This function determines whether a string is a valid double.
        Note that a valid integer is considered to be a valid double.
    
    Preconditions:
        none
    
    Postconditions:
        returns true if entire string is valid double
 */
bool isDouble(const string &str)
{
    // return false if empty
    if (str.length() < 1)
        return false;
    
    bool pointFound = false;
    
    // check each char
    for (int i = 0; i < str.length(); i++)
    {
        if ( !isdigit(str[i]) &&           // not a digit
            (str[i] != '-' || i != 0) &&   // not '-' at beginning
            (str[i] != '.' || pointFound)  // '.' when one already found
           )
            return false;
        if (str[i] == '.')
            pointFound = true;
    }
    
    // no illegal chars found
    return true;
}

/**
    bool isInteger(const string &str)
    
    Purpose:
        This function determines whether a string is a valid integer.
    
    Preconditions:
        none
    
    Postconditions:
        returns true if entire string is valid integer
 */
bool isInteger(const string &str)
{
    // return false if empty
    if (str.length() < 1)
        return false;
    
    // check each char
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]) && (i != 0 || str[i] != '-'))
            return false;
    }
    
    // no non-digits found
    return true;
}

/**
    vector<string> split(const string &text, char delim = ' ')
    
    Purpose:
        This function splits a string into substrings based on 
        the specified delimiter. It defaults to a space if no
        delimiter is specified.
    
    Preconditions:
        none
    
    Postconditions:
        returns a vector containing the substrings
 */
vector<string> split(const string &text, char delim)
{
    vector<string> buffer;
    size_t pos = 0; // find position
    
    while (pos < text.length())
    {
        size_t next = text.find(delim, pos);
        if (next == string::npos)
            next = text.length();
        buffer.push_back(text.substr(pos, next - pos));
        pos = next + 1;
    }
    
    return buffer;
}
