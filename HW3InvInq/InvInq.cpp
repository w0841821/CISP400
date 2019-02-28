// InvInq.cpp
// Erroll Abrahamian, CISP 400
// 03-03-2019

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Inventory
{
  string itemDesc;
  double itemQuan;
  //float itemCost;
  double itemDollars;
  int itemCents;
  int itemDate[3];
};

// Specification B1 - OOP
class InvInq
{
private:
  Inventory* invArray = nullptr;
  int itemCount, currInvItem;
  const unsigned int maxLength = 22;

public:
  // function prototypes
  void newArray();
  void sayHi();
  void printMenu();
  void addInv();
  void incInv();
  void delInv();
  void editInv();
  void showInv();
  void getDate();
  void writeInv();
};

int main()
{
  InvInq hw3;

  hw3.newArray();
  hw3.sayHi();
  hw3.printMenu();
  hw3.writeInv();

  return 0;
}

void InvInq::newArray()
{
  // number of inventoried items = 0
  itemCount = 0;

  // Specification C1 - Dynamic Array
  invArray = new Inventory[0];
}

// program greeting
void InvInq::sayHi()
{
  cout << "You wanted another inventory management program?\n";
  cout << "WELL HERE IT IS. I HOPE THIS IS GOOD ENOUGH FOR YOU.\n";
}

void InvInq::printMenu()
{
  int menu;
  bool quit = false;
  char quitCheck;

  do {
    cout << "\n\n" << string(40, '*') << "\n";

    // Specification C4 - Main Menu
    cout << "1. Add Inventory\n";
    cout << "2. Delete Inventory\n";
    cout << "3. Edit Inventory\n";
    cout << "4. Display Inventory\n";
    cout << "5. Quit Program\n\n";

    cout << "Enter the number for your selection: ";
    cin >> menu;

    // Specification C5 - Validate Menu
    switch (menu)
    {
      case 1: addInv();
        break;
      case 2: delInv();
        break;
      case 3: editInv();
        break;
      case 4: showInv();
        break;
      case 5: cout << "Are you sure you'd like to quit? (y) to quit: ";
      cin >> quitCheck;
      if (toupper(quitCheck) == 'Y')
        quit = true;
      default: ;
    }
  } while(!quit);
}

// Specification C2 - Add Option
void InvInq::addInv()
{
  incInv();

  // current inventory item is 1 less than the number of items
  // when number of items = 1, array location must = 0, etc
  currInvItem = itemCount - 1;

  cin.ignore();

  cout << "\nDescription: ";
  do {
    getline(cin, invArray[currInvItem].itemDesc);

    // Specification A2 - Validate Inventory
    if (invArray[currInvItem].itemDesc.length() > maxLength)
      cout << "Description is too long. Enter 22 characters or less: ";
    if (invArray[currInvItem].itemDesc == "")
      cout << "Oops, that's a blank Description! Enter Description: ";

  // loop while we're over 22 characters, or if no description is entered
  } while(invArray[currInvItem].itemDesc.length() > maxLength || invArray[currInvItem].itemDesc == "");

  cout << "Quantity: ";
  do {
    cin >> invArray[currInvItem].itemQuan;

    // allowing ten digits for formatting quantity, so: no more than 9,999,999,999
    if (invArray[currInvItem].itemQuan < 0 || invArray[currInvItem].itemQuan > 9999999999)
      cout << "That doesn't sound like a proper quantity. Enter a proper amount: ";

  // loop while less than 0 (negative quantity?) or over the imposed limit
  } while(invArray[currInvItem].itemQuan < 0 || invArray[currInvItem].itemQuan > 9999999999);

/*
  cout << "Cost (x.xx): ";
  do {
    cin >> invArray[currInvItem].itemCost;

    if (invArray[currInvItem].itemCost < 0 || invArray[currInvItem].itemCost > 999999999.99)
      cout << "Price should be more than zero, and less than one billion: ";
  } while(invArray[currInvItem].itemCost < 0 || invArray[currInvItem].itemCost > 999999999.99);
  */

  cout << "Cost, dollars: ";
  do {
    cin >> invArray[currInvItem].itemDollars;

    // allowing nine digits for formatting dollars, so: no more than 999,999,999
    if (invArray[currInvItem].itemDollars < 0 || invArray[currInvItem].itemDollars > 999999999)
      cout << "Dollars should be at least 0 or less than one billion: ";

  // same as with quantity
  } while(invArray[currInvItem].itemDollars < 0 || invArray[currInvItem].itemDollars > 999999999);

  cout << "Cost, cents: ";
  do {
    cin >> invArray[currInvItem].itemCents;
    if (invArray[currInvItem].itemCents < 0 || invArray[currInvItem].itemCents > 99)
      cout << "Cents should be between 0 and 99: ";

  // same as with dollars and quantity
  } while(invArray[currInvItem].itemCents < 0 || invArray[currInvItem].itemCents > 99);


  // double the price for markup
  invArray[currInvItem].itemCents *= 2;
  invArray[currInvItem].itemDollars *= 2;

  // if cents go over 99, we need to add a dollar
  if (invArray[currInvItem].itemCents > 99)
  {
    invArray[currInvItem].itemCents -= 100;
    invArray[currInvItem].itemDollars += 1;
  }

//  invArray[currInvItem].itemCost *= 2;

  getDate();
}

void InvInq::incInv()
{
  // increase number of items by 1
  itemCount++;

  Inventory* tmpArr = nullptr;

  // set temp array to new size of items
  tmpArr = new Inventory[itemCount];

  for (int i = 0; i < (itemCount - 1); i++)
    tmpArr[i] = invArray[i];

  delete [] invArray;

  invArray = tmpArr;

  tmpArr = nullptr;
}

// Specification B2 - Delete Inventory Item
void InvInq::delInv()
{
  bool correctItem = false;
  int itemNum;
  char menu;

  do {
    cout << "\nEnter the Item # of the inventory item you would like to delete,\n";
    cout << "or enter 0 to return to the main menu: ";
    cin >> itemNum;

    // exit the delete if 0 is entered
    if (itemNum == 0)
      break;

    // can't delete an item if it doesn't exist!
    if (itemNum > itemCount)
      cout << "\nOops, we don't have that many items!";

    // otherwise we have the right item to delete
    else
    {
      cout << "\nItem #" << itemNum << " is " << invArray[itemNum - 1].itemDesc << ".\n";
      cout << "Is this the item you would like to delete?\n";
      cout << "(y), otherwise enter any other key: ";
      cin >> menu;
      if (toupper(menu) == 'Y')
        correctItem = true;
    }
  } while(!correctItem);

  // Specification B3 - Shrink Dynamic Array
  if (correctItem)
  {
    int j = 0;
    // the element to delete is offset by -1 to align with array
    int deleteEle = itemNum - 1;

    itemCount--;

    Inventory* delArr = nullptr;

    delArr = new Inventory[itemCount];

    for (int i = 0; i < (itemCount + 1); i++)
    {
      if (i != deleteEle)
      {
        delArr[j] = invArray[i];
        j++;
      }
    }

    delete [] invArray;

    invArray = delArr;

    delArr = nullptr;
  }
}

// Specification A1 - Edit Inventory
void InvInq::editInv()
{
  bool correctItem = false;
  int itemNum;
  char menu;

  do {
    cout << "\nEnter the Item # of the inventory item you would like to edit,\n";
    cout << "or enter 0 to return to the main menu: ";
    cin >> itemNum;
    if (itemNum == 0)
      break;
    if (itemNum > itemCount)
      cout << "\nOops, we don't have that many items!";
    else
    {
      cout << "\nItem #" << itemNum << " is " << invArray[itemNum - 1].itemDesc << ".\n";
      cout << "Is this the item you would like to edit?\n";
      cout << "(y), otherwise enter any other key: ";
      cin >> menu;
      if (toupper(menu) == 'Y')
        correctItem = true;
    }
  } while(!correctItem);

  if (correctItem)
  {
    currInvItem = itemNum - 1;

    cout << "Old Description: " << invArray[currInvItem].itemDesc << ".\n";
    cout << "New Description: ";
    cin.ignore();
    do {
      getline(cin, invArray[currInvItem].itemDesc);
      if (invArray[currInvItem].itemDesc.length() > maxLength)
        cout << "Description is too long. Enter 22 characters or less:\n";
      if (invArray[currInvItem].itemDesc == "")
        cout << "Oops, that's a blank Description! Enter Description: ";
    } while(invArray[currInvItem].itemDesc.length() > maxLength || invArray[currInvItem].itemDesc == "");

    cout << "Previous Quantity: " << invArray[currInvItem].itemQuan << ".\n";
    cout << "New Quantity: ";
    do {
      cin >> invArray[currInvItem].itemQuan;
      if (invArray[currInvItem].itemQuan < 0 || invArray[currInvItem].itemQuan > 9999999999)
        cout << "That doesn't sound like a proper quantity. Enter a proper amount: ";
    } while(invArray[currInvItem].itemQuan < 0 || invArray[currInvItem].itemQuan > 9999999999);
/*
    cout << "Previous Cost, BEFORE MARKUP: $" << invArray[currInvItem].itemCost / 2 << ".\n";
    cout << "Cost (x.xx): ";
    do {
      cin >> invArray[currInvItem].itemCost;

      if (invArray[currInvItem].itemCost < 0 || invArray[currInvItem].itemCost > 999999999.99)
        cout << "Price should be more than zero, and less than one billion: ";
    } while(invArray[currInvItem].itemCost < 0 || invArray[currInvItem].itemCost > 999999999.99);

    invArray[currInvItem].itemCost *= 2;
  }
  */

    cout << "Previous Cost, AFTER MARKUP: $" << invArray[currInvItem].itemDollars << "." << setw(2) << setfill('0') << invArray[currInvItem].itemCents << setfill(' ') << ".\n";
    cout << "New Cost, BEFORE MARKUP, $: ";
    do {
      cin >> invArray[currInvItem].itemDollars;
      if (invArray[currInvItem].itemDollars < 0 || invArray[currInvItem].itemDollars > 999999999)
        cout << "Dollars should be at least 0 or less than one billion: ";
    } while(invArray[currInvItem].itemDollars < 0 || invArray[currInvItem].itemDollars > 999999999);

    cout << "New Cost, cents: ";
    do {
      cin >> invArray[currInvItem].itemCents;
      if (invArray[currInvItem].itemCents < 0 || invArray[currInvItem].itemCents > 99)
        cout << "Cents should be between 0 and 99: ";
    } while(invArray[currInvItem].itemCents < 0 || invArray[currInvItem].itemCents > 99);
  }

  // double the price for markup
  invArray[currInvItem].itemCents *= 2;
  invArray[currInvItem].itemDollars *= 2;

  // if cents go over 99, we need to add a dollar
  if (invArray[currInvItem].itemCents > 99)
  {
    invArray[currInvItem].itemCents -= 100;
    invArray[currInvItem].itemDollars += 1;
  }

}

// Specification C3 - Display Option
void InvInq::showInv()
{
  cout << "\nITEM #  DESCRIPTION                   QUANTITY              COST      ENTRY DATE\n";
  for (int i = 0; i < itemCount; i++)
    cout << right << setw(6) << i + 1 << "  " << left << setw(22) << invArray[i].itemDesc << "      " << right << setw(10) << invArray[i].itemQuan << "      " << setw(9) << invArray[i].itemDollars << "." << setw(2) << setfill('0') << invArray[i].itemCents << setfill(' ') << "      " << setw(2) << invArray[i].itemDate[0] << "/" << setw(2) << invArray[i].itemDate[1] << "/" << invArray[i].itemDate[2] << endl;
}

void InvInq::getDate()
{
  time_t now = time(0);
  tm *dateTime = localtime(&now);
  int dtYear = (1900 + dateTime->tm_year);
  int dtMonth = (1 + dateTime->tm_mon);
  int dtDay = dateTime->tm_mday;

  invArray[currInvItem].itemDate[0] = dtMonth;
  invArray[currInvItem].itemDate[1] = dtDay;
  invArray[currInvItem].itemDate[2] = dtYear;
}

// Specification A3 - Logfile
void InvInq::writeInv()
{
  ofstream invFile;
  invFile.open("inv.txt", ios::app);

  invFile << "\nITEM #  DESCRIPTION                   QUANTITY              COST      ENTRY DATE\n";

  for (int i = 0; i < itemCount; i++)
  {
    invFile << right << setw(6) << i + 1 << "  " << left << setw(22) << invArray[i].itemDesc << "      " << right << setw(10) << invArray[i].itemQuan << "      " << setw(9) << invArray[i].itemDollars << "." << setw(2) << setfill('0') << invArray[i].itemCents << setfill(' ') << "      " << setw(2) << invArray[i].itemDate[0] << "/" << setw(2) << invArray[i].itemDate[1] << "/" << invArray[i].itemDate[2] << endl;
  }

  invFile.close();
}
