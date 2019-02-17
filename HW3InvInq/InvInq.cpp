// InvInq.cpp
// Erroll Abrahamian, CISP 400
// 03-03-2019

/*
Table 1 has the minimum fields you will need as well as the validation rules for Specification A2.

             Field Name -- Validation Rules
       Item Description -- 22 characters max
       Quantity at Hand -- Cannot be negative
            Retail Cost -- Automatically calculate 100% markup
Date Added to Inventory -- System should enter this

This is a menu driven program. You can decide if it uses a numeric or alphabetic menu. Keep prompting and running until the quit option is selected.
• Style guide elements apply: comments, layout, Program Greeting, Source File Header, and variables etc. etc.

// Specification C1 - Dynamic Array
// Create an array on the heap. Increase it automatically for every item the client adds. That is, this array should be as small as possible - always.

// Specification C2 - Add Option
// Allows you to add records to the inventory data structure you created.

// Specification C3 - Display Option
// Displays all the information in your inventory data structure.

// Specification C4 - Main Menu
// Create a main menu which lists the allowable behaviors. See figure 1 for an example menu.

1. Add Inventory
2. Display Inventory
3. Quit Program

// Specification C5 - Validate Menu
// Validation - Notice allowable options and if entry is incorrect.

// Specification B1 - OOP
// Code this assignment using at least one class. Put this comment above the class declaration.

// Specification B2 - Delete Inventory Item
// Allow the client to delete items in the inventory data structure. See figure 2 for the "B" menu. Don’t forget to update C5 to account for this new menu option.

1. Add Inventory
2. Delete Inventory
3. Display Inventory
4. Quit Program

// Specification B3 - Shrink Dynamic Array
// Resize the dynamic array when you delete inventory.

// Specification A1 - Edit Inventory
// Add the capability to edit the contents of any inventory item. Edit is different from delete. See figure 3 for the "A" menu. Don’t forget to update C5 to account for this new menu option.

1. Add Inventory
2. Delete Inventory
3. Edit Inventory
4. Display Inventory
5. Quit Program

// Specification A2 - Validate Inventory
// Only allow data which meets the input specifications in the inventory data structure.

// Specification A3 - Logfile
// Log all changes to the inventory data structure to a text file for archival purposes.
*/

#include <iostream>
#include <fstream>
using namespace std;

/*
Field Name -- Validation Rules
Item Description -- 22 characters max
Quantity at Hand -- Cannot be negative
Retail Cost -- Automatically calculate 100% markup
Date Added to Inventory -- System should enter this
*/

struct Inventory
{
  char itemDesc[23];
  int itemQuan;
  float itemCost;
  int itemDate[3];
};

class InvInq
{
private:
  Inventory* invArray = nullptr;
public:
  void buildArray();
  void printMenu();
  void addInv();
  void getDate();
  void incInventory();
};

int main()
{
  InvInq hw3;

  hw3.buildArray();

  hw3.printMenu();
  hw3.getDate();
  hw3.incInventory();
}

void InvInq::buildArray()
{

  invArray = new Inventory[1];
}

void InvInq::printMenu()
{
  int menu;
  cout << "1. Add Inventory\n";
  cout << "2. Delete Inventory\n";
  cout << "3. Edit Inventory\n";
  cout << "4. Display Inventory\n";
  cout << "5. Quit Program\n\n";

  cout << "Enter the number for your selection: ";
  cin >> menu;

  switch (menu)
  {
    case 1: addInv();
      break;
    case 2:
    case 3:
    case 4:
    case 5:
    default: ;
  }
}

void InvInq::addInv()
{
  cout << "Description: ";
  cin >> invArray[1].itemDesc;
  // cin >> invArray->itemDesc[1];
  cout << invArray[1].itemDesc << endl;
  cout << "Quantity: ";
  cin >> invArray[1].itemQuan;
  // cin >> invArray->itemQuan[1];
  cout << "Cost: ";
  cin >> invArray[1].itemCost;
  // cin >> invArray->itemCost[1];
  // get date entry
}

void InvInq::getDate()
{
  time_t now = time(0);
  cout << now << endl;
  tm *dateTime = localtime(&now);
  int dtYear = (1900 + dateTime->tm_year);
  int dtMonth = (1 + dateTime->tm_mon);
  int dtDay = dateTime->tm_mday;
  cout << "MONTH  DAY  YEAR" << endl;
  cout << dtMonth << dtDay << dtYear << endl;
}

void InvInq::incInventory()
{
}
