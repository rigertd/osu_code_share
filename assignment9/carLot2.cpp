/*************************************************************************
 * Author:                 David Rigert
 * Date Created:           11/17/2014
 * Last Modification Date: 11/27/2014
 * Assignment:             Assignment 9
 * Filename:               carLot2.cpp
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
#include <stdexcept>
#include <cmath>

using namespace std;

// represents a date
class Date
{
    private:
        int day,                     // the day value
            month,                   // the month value
            year;                    // the year value
            
    public:
        static const int DAYS_IN_MONTH[13]; // number of days in each month
        
        // constructor prototypes
        Date();                 // default constructor
        Date(int, int, int);    // three argument constructor
        
        // accessors
        int getDay() const {return day;};     // gets the day value
        int getMonth() const {return month;}; // gets the month value
        int getYear() const {return year;};   // gets the year value
};

// represents current or past inventory on a car dealer lot
class Car
{
    private:
        string make,            // the make of the car
               model;           // the model of the car
        int year;               // the model year
        Date datePurchased,     // date purchased by dealer
             dateSold;          // date sold by dealer
        double purchasePrice,   // price paid by dealer
               salePrice;       // price paid by customer
        bool sold;              // whether the car is sold
        
    public:
        // constructor prototypes
        Car(string &, string &, int, Date , double, bool);
        Car(string &, string &, int, Date , double, bool, Date , double);
        
        // accessor functions
        string getMake() const {return make;}                // make of car
        string getModel() const {return model;}              // model of car
        int getModelYear() const {return year;}              // model year
        Date getPurchDate() const {return datePurchased;}    // purchase date
        double getPurchPrice() const {return purchasePrice;} // purchase price
        bool isSold() const {return sold;}                   // whether sold
        Date getSoldDate() const {return dateSold;}          // sale date
        
        // member function prototypes
        double getProfit() const;      // gets profit for this car if sold
};

// represents the current and past inventory of a car dealer
class CarLot
{
    private:
        vector<Car> lot;    // ledger
        
    public:
        static const string MARGIN;     // margin between columns
        static const int MAKE_MAX_LEN;  // max length of make in list
        static const int MODEL_MAX_LEN; // max length of model in list
        static const int DATE_LEN;      // length of date in list
        static const int PRICE_LEN;     // length of price in list
        static const double PRICE_MAX;  // max price value <= PRICE_LEN
        
        // member function prototypes
        void addCar(Car);             // adds the specified car to the ledger
        void listCurrentInv() const;  // prints unsold cars on lot to console
        double getMonthProfit(int, int) const; // gets profit for month/year
};

// assign number of days in each month to static const array
const int Date::DAYS_IN_MONTH[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// set values in CarLot static constants
const string CarLot::MARGIN = "  ";
const int CarLot::MAKE_MAX_LEN = 20;
const int CarLot::MODEL_MAX_LEN = 20;
const int CarLot::DATE_LEN = 10;
const int CarLot::PRICE_LEN = 10;
const double CarLot::PRICE_MAX = 9999999.99;

// member function implementations

/********************************************************************
 *  Default constructor. Sets the date to January 1, 1970.
 *******************************************************************/
Date::Date()
{
    day = month = 1;
    year = 1970;
}
 
/********************************************************************
 *  Three argument constructor. Sets the date to the specified values.
 *  Throws an invalid argument exception if invalid date specified.
 *******************************************************************/
Date::Date(int d, int m, int y)
{
    // validate month value
    if (m < 1 || m > 12)
        throw invalid_argument("ERROR: Invalid month specified.");
    
    // validate day value
    if (d < 1 || d > DAYS_IN_MONTH[m])
        throw invalid_argument("ERROR: Invalid day specified.");
    
    day = d;
    month = m;
    year = y;
}

/********************************************************************
 *  Eight argument constructor. Used for cars that are already sold.
 *******************************************************************/
Car::Car(string &makeVal, string &modelVal, int yearVal, Date purchDate, 
         double purchPrice, bool isSold, Date sellDate, double sellPrice)
{
    make = makeVal;
    model = modelVal;
    year = yearVal;
    datePurchased = purchDate;
    purchasePrice = purchPrice;
    sold = isSold;
    dateSold = sellDate;
    salePrice = sellPrice;
}

/********************************************************************
 *  Six argument constructor. Used for cars that are still in inventory.
 *******************************************************************/
Car::Car(string &makeVal, string &modelVal, int yearVal, Date purchDate, 
         double purchPrice, bool isSold)
{
    make = makeVal;
    model = modelVal;
    year = yearVal;
    datePurchased = purchDate;
    purchasePrice = purchPrice;
    sold = isSold;
    salePrice = 0;
}

/********************************************************************
 *  double Car::getProfit() const
 *
 *  Purpose: This function gets the profit earned from the sale of the car.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns salePrice - purchasePrice, or NAN if not sold
 *******************************************************************/
double Car::getProfit() const
{
    // return not-a-number if unsold
    if (!sold)
        return NAN;
    
    return salePrice - purchasePrice;
}

/********************************************************************
 *  void CarLot::addCar(Car car)
 *
 *  Purpose: This function adds the specified Car to the lot.
 *
 *  Preconditions: none
 *
 *  Postconditions: Car is added to the lot.
 *******************************************************************/
void CarLot::addCar(Car car)
{
    lot.push_back(car);
}

/********************************************************************
 *  void CarLot::listCurrentInv() const
 *
 *  Purpose: This function prints unsold cars on lot to console.
 *           It also lists the number of unsold cars.
 *
 *  Preconditions: none
 *
 *  Postconditions: A list of unsold cars and number of unsold cars 
 *                  are printed to the console.
 *******************************************************************/
void CarLot::listCurrentInv() const
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
    for (int i = 0; i < lot.size(); i++)
    {
        // Print only if not sold. Format is as follows:
        // Make (max 20 chars)  Model (max 20 chars)  Year  Purchased  Price
        if (!lot[i].isSold())
        {
            cout << left << setw(MAKE_MAX_LEN) 
                 << lot[i].getMake().substr(0, MAKE_MAX_LEN) << MARGIN
                 << setw(MODEL_MAX_LEN) 
                 << lot[i].getModel().substr(0,MODEL_MAX_LEN) << MARGIN 
                 << right << setfill('0') << setw(4) 
                 << lot[i].getModelYear() << MARGIN
                 << setw(2) << lot[i].getPurchDate().getMonth() << "/"
                 << setw(2) << lot[i].getPurchDate().getDay() << "/"
                 << setw(4) << lot[i].getPurchDate().getYear() << MARGIN
                 << setfill(' ') << fixed << showpoint
                 << "$" << setprecision(2) << setw(PRICE_LEN) 
                 << lot[i].getPurchPrice() << left << endl;
            
            unsold++;
        }
    }
    cout << "\nYou have " << unsold << " unsold car"
         << (unsold == 1 ? " " : "s ") << "on the lot.\n\n";
}

/********************************************************************
 *  double CarLot::getMonthProfit(int month, int year) const
 *
 *  Purpose: This function gets profit for all cars sold during the
 *           specified month and year.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns total of salePrice - purchasePrice for all
 *                  cars with dateSold in specified month and year.
 *******************************************************************/
double CarLot::getMonthProfit(int month, int year) const
{
    double profit = 0.0;      // total profit for month
    
    for (int i = 0; i < lot.size(); i++)
    {
        // only count if sold and correct month and year
        if (lot[i].isSold() &&
            lot[i].getSoldDate().getMonth() == month &&
            lot[i].getSoldDate().getYear() == year)
            profit += lot[i].getProfit();
    }
    
    return profit;
}

// function prototypes
// Adds a car entry to the system.
void addEntry(CarLot &);
// Prints the menu.
void printMenu();
// Prompts user for a month and year and prints the profit.
void printProfit(const CarLot &);

/********************************************************************
 *  user input functions
 *******************************************************************/
// Gets an amount from the user as a double.
double getAmount(const string &, double, double);
// Gets a Date object filled in by the user.
Date getDate(const string &);
// Gets valid month and year values from the user.
void getMonthYear(int &, int &);
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

int main()
{
    // declare variables
    CarLot ledger;        // inventory ledger
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
            
            switch (selection)
            {
                case 1: addEntry(ledger);
                        break;
                
                case 2: ledger.listCurrentInv();
                        break;
                
                case 3: printProfit(ledger);
                        break;
                        
                case 4: break;
                
                default: // invalid range
                        cout << "Invalid selection. Try again.\n";
                        selection = 0;
            }
        }
    } while (selection != 4 && !cin.fail());

    cout << "\nDestroying ledger. Thank you for wasting your time.\n";
    
    return 0;
}

/********************************************************************
 *  void addEntry(CarLot &lot)
 *
 *  Purpose: This function adds a car entry to the system.
 *
 *  Preconditions: none
 *
 *  Postconditions: User input is stored in a Car and added to the CarLot.
 ********************************************************************/
void addEntry(CarLot &lot)
{
    string make,    // temporary input storage
           model;
    int year, purchDay, purchMonth, purchYear, 
        soldDay, soldMonth, soldYear;
    double purchPrice, salePrice;
    bool isSold;
    Date purchDate, saleDate;
    
    // get make
    cout << "Enter the make: ";
    getline(cin, make);
    
    // get model
    cout << "Enter the model: ";
    getline(cin, model);
    
    // get year
    year = getYear("Enter the year: ");
    
    // get date purchased
    purchDate = getDate("Enter the purchase date as MM/DD/YYYY: ");
    
    // get purchase price
    purchPrice = getAmount("Enter the purchase price: $", 0, 
                           CarLot::PRICE_MAX);
    
    // get sold value
    isSold = getYesNo("Has this car already been sold? (Y/N): ");
    
    if (isSold)
    {
        // get dateSold
        saleDate = getDate("Enter the date sold as MM/DD/YYYY: ");
    
        // get salePrice
        salePrice = getAmount("Enter the sale price: $", 0, CarLot::PRICE_MAX);
        
        // add sold Car to CarLot
        lot.addCar(Car (make, model, year, purchDate, purchPrice, isSold,
                        saleDate, salePrice));
    }
    else
    {
        // add unsold Car to CarLot
        lot.addCar(Car (make, model, year, purchDate, purchPrice, isSold));
    }
}

/********************************************************************
 *  void printMenu()
 *
 *  Purpose: This function prints the menu to the console.
 *
 *  Preconditions: none
 *
 *  Postconditions: Menu is printed to the console.
 ********************************************************************/
void printMenu()
{
    cout << "\nChoose an item from the menu.\n\n"
         << "1) Add entry\n"
         << "2) List current inventory\n"
         << "3) Profit for a month\n"
         << "4) Quit\n\n";
}

/********************************************************************
 *  void printProfit(const CarLot &lot)
 *
 *  Purpose: This function prompts the user for a month and year and prints
 *           the total profit from all cars sold within the specified month 
 *           and year.
 *
 *  Preconditions: none
 *
 *  Postconditions: The total cost is displayed in console window.
 ********************************************************************/
void printProfit(const CarLot &lot)
{
    int month, year;
    
    // get valid month and year
    getMonthYear(month, year);
    
    double profit = lot.getMonthProfit(month, year);
    
    cout << "\nYour total profit for " 
         << right << setfill('0') << setw(2) << month << "/" 
         << right << setfill('0') << setw(4) << year << " was $"
         << left << fixed << showpoint << setprecision(2) << profit << ".\n";
}

/********************************************************************
 *  double getAmount(const string &prompt, double min, double max)
 *
 *  Purpose: This function prompts the user for an amount of money and 
 *           validates the input. The user is reprompted until a valid 
 *           value is entered.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns the entered amount.
 ********************************************************************/
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

/********************************************************************
 *  Date getDate(const string &prompt)
 *
 *  Purpose: This function prompts the user for the month, day and year and 
 *           validates the input syntax, but not the input value. The Date 
 *           constructor throws an exception if the value is invalid.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns a Date object with the entered values.
 ********************************************************************/
Date getDate(const string &prompt)
{
    string input;         // user input buffer
    vector<string> date;  // split month, day and year
    int month, day, year; // store converted date
    
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
            month = atoi(date[0].c_str());
            day = atoi(date[1].c_str());
            year = atoi(date[2].c_str());
        }
    } while (date.size() != 3);
    
    return Date (day, month, year);
}

/********************************************************************
 *  void getMonthYear(int &month, int &year)
 *
 *  Purpose: This function prompts the user for a month and a year and
 *           validates the input syntax. The user is reprompted until valid 
 *           MM/YYYY syntax is used. The values themselves are not validated.
 *
 *  Preconditions: none
 *
 *  Postconditions: month and year contain the entered month and year.
 ********************************************************************/
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
            month = atoi(monthYear[0].c_str());
            year = atoi(monthYear[1].c_str());
        }
    } while (monthYear.size() != 2);
}

/********************************************************************
 *  int getYear(const string &prompt)
 *
 *  Purpose: This function prompts the user for a year and validates the 
 *           input. The user is reprompted until a valid integer is entered.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns the entered year value.
 ********************************************************************/
int getYear(const string &prompt)
{
    string input;   // user input buffer
    int year;       // year value
    bool valid;     // valid integer?
    
    do
    {
        cout << prompt;
        getline(cin, input);
        
        // validate year
        valid = isInteger(input);
        if (valid)
            year = atoi(input.c_str());
        else
            cout << "Invalid year.\n";
    } while (!valid);
    
    return year;
}

/********************************************************************
 *  bool getYesNo(string prompt)
 *
 *  Purpose: This function displays the specified prompt until the first char
 *           of the input is 'Y', 'y', 'N', or 'n'.
 *
 *  Preconditions: none
 *
 *  Postconditions: The input buffer is empty and returns true if 'y' or 'Y'.
 ********************************************************************/
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

/********************************************************************
 *  bool isDouble(const string &str)
 *
 *  Purpose: This function determines whether a string is a valid double.
 *           Note that a valid integer is considered to be a valid double.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns true if entire string is valid double.
 ********************************************************************/
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
            (str[i] != '-' || i != 0) &&   // '-' found not at beginning
            (str[i] != '.' || pointFound)  // '.' when one already found
           )
            return false;
        if (str[i] == '.')
            pointFound = true;
    }
    
    // no illegal chars found
    return true;
}

/********************************************************************
 *  bool isInteger(const string &str)
 *
 *  Purpose: This function determines whether a string is a valid integer.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns true if entire string is valid integer.
 ********************************************************************/
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

/********************************************************************
 *  vector<string> split(const string &text, char delim = ' ')
 *
 *  Purpose: This function splits a string into substrings based on the 
 *           specified delimiter. It defaults to a space if no delimiter 
 *           is specified.
 *
 *  Preconditions: none
 *
 *  Postconditions: Returns a vector containing the substrings.
 ********************************************************************/
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
