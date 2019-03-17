/*
Program the game of battleship against the computer. Each side has 2 grids. The first grid contains the location of the player’s ships. The second grid contains the location of the player’s shots and the outcome of the shot (hit or miss). The objective is to hit and sink all 5 enemy ships before they do the same to you. Each side receives ships listed in figure 1.

   Carrier 5
Battleship 4
   Cruiser 3
 Submarine 3
 Destroyer 2

• The human player will see 2 battlemaps every turn:
1) map of your ships and where the computer fired
2) map of where you have fired and the result (hit something or miss).

• Show the results of each turn enemy map indicating where the computer fired on you (and your ships) and a friendly map showing where you fired (and sunk) computer ships.

• You can use the Standard Template Library.

• Style guide elements apply: comments, layout, Program Greeting,
Source File Header, and variables etc. etc.
*/

// bb.cpp
// Erroll Abrahamian, CISP 400
// 03-24-2019

#include <iostream>
using namespace std;

enum Ships_Enum {CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER};
enum Player_Enum {USER, COMP};

struct Player
{
  string name;

  struct Ships
  {
    string shipType;
    int shipSize;
    bool shipSunk;
  } ship[5];

  struct Ocean
  {
    string board;
		struct result {

		};
  } ocean[11][11];

} player[2];

class Battleship
{
private:
  char normal[8] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char blue[8] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
  char red[8] = {0x1b, '[', '1', ';', '3', '1', 'm', 0};
public:
  void sayHi();
  void buildShips();
  void buildBoard();
  void placeShips();
  void printBoard();
	void hitEnter();
};

int main()
{
  Battleship hw4;

  hw4.buildShips();
  hw4.buildBoard();
	hw4.sayHi();

  hw4.placeShips();
  hw4.printBoard();

  return 0;
}

void Battleship::sayHi()
{
  cout << "Hi!\n\n";
	cout << "A missed shot will be marked with \"" << blue << "O" << normal << "\".\n";
	cout << "A hit will be marked with \"" << red << "X" << normal << "\".\n";
	cout << "Open ocean is indicated with \"" << blue << "~" << normal << "\".\n\n";
	cout << "Carriers have a size of 5 and are indicated with \"C\".\n";
	cout << "Battleships have a size of 4 and are incidated with \"B\".\n";
	cout << "Cruisers have a size of 3 and are indicated with \"Z\".\n";
	cout << "Submarines have a size of 3 and are indicated with \"S\".\n";
	cout << "Destroyers have a size of 2 and are indicated with \"D\".\n\n";

	hitEnter();

	cout << "You will see two maps: one of your ships with the results of shots from the computer,\n";
	cout << "and the computer's map, with the results of your shots.\n\n";

	printBoard();

	hitEnter();
}

void Battleship::buildShips()
{
  player[USER].name = "User";
  player[USER].ship[CARRIER].shipType = "Carrier";
  player[USER].ship[CARRIER].shipSize = 5,
  player[USER].ship[CARRIER].shipSunk = false,
  player[USER].ship[BATTLESHIP].shipType = "Battleship",
  player[USER].ship[BATTLESHIP].shipSize = 4,
  player[USER].ship[BATTLESHIP].shipSunk = false,
  player[USER].ship[CRUISER].shipType = "Cruiser",
  player[USER].ship[CRUISER].shipSize = 3,
  player[USER].ship[CRUISER].shipSunk = false,
  player[USER].ship[SUBMARINE].shipType = "Submarine",
  player[USER].ship[SUBMARINE].shipSize = 3,
  player[USER].ship[SUBMARINE].shipSunk = false,
  player[USER].ship[DESTROYER].shipType = "Destroyer",
  player[USER].ship[DESTROYER].shipSize = 2;
  player[USER].ship[DESTROYER].shipSunk = false;

  player[COMP].name = "Computer";
  player[COMP].ship[CARRIER].shipType = "Carrier";
  player[COMP].ship[CARRIER].shipSize = 5,
  player[COMP].ship[CARRIER].shipSunk = false,
  player[COMP].ship[BATTLESHIP].shipType = "Battleship",
  player[COMP].ship[BATTLESHIP].shipSize = 4,
  player[COMP].ship[BATTLESHIP].shipSunk = false,
  player[COMP].ship[CRUISER].shipType = "Cruiser",
  player[COMP].ship[CRUISER].shipSize = 3,
  player[COMP].ship[CRUISER].shipSunk = false,
  player[COMP].ship[SUBMARINE].shipType = "Submarine",
  player[COMP].ship[SUBMARINE].shipSize = 3,
  player[COMP].ship[SUBMARINE].shipSunk = false,
  player[COMP].ship[DESTROYER].shipType = "Destroyer",
  player[COMP].ship[DESTROYER].shipSize = 2;
  player[COMP].ship[DESTROYER].shipSunk = false;
}

void Battleship::buildBoard()
{
  player[USER].ocean[0][0].board = "   ";
  player[USER].ocean[0][1].board = "A";
  player[USER].ocean[0][2].board = "B";
  player[USER].ocean[0][3].board = "C";
  player[USER].ocean[0][4].board = "D";
  player[USER].ocean[0][5].board = "E";
  player[USER].ocean[0][6].board = "F";
  player[USER].ocean[0][7].board = "G";
  player[USER].ocean[0][8].board = "H";
  player[USER].ocean[0][9].board = "I";
  player[USER].ocean[0][10].board = "J";
  player[USER].ocean[1][0].board = " 1 ";
  player[USER].ocean[2][0].board = " 2 ";
  player[USER].ocean[3][0].board = " 3 ";
  player[USER].ocean[4][0].board = " 4 ";
  player[USER].ocean[5][0].board = " 5 ";
  player[USER].ocean[6][0].board = " 6 ";
  player[USER].ocean[7][0].board = " 7 ";
  player[USER].ocean[8][0].board = " 8 ";
  player[USER].ocean[9][0].board = " 9 ";
  player[USER].ocean[10][0].board = "10 ";

  player[COMP].ocean[0][0].board = "   ";
  player[COMP].ocean[0][1].board = "A";
  player[COMP].ocean[0][2].board = "B";
  player[COMP].ocean[0][3].board = "C";
  player[COMP].ocean[0][4].board = "D";
  player[COMP].ocean[0][5].board = "E";
  player[COMP].ocean[0][6].board = "F";
  player[COMP].ocean[0][7].board = "G";
  player[COMP].ocean[0][8].board = "H";
  player[COMP].ocean[0][9].board = "I";
  player[COMP].ocean[0][10].board = "J";
  player[COMP].ocean[1][0].board = " 1 ";
  player[COMP].ocean[2][0].board = " 2 ";
  player[COMP].ocean[3][0].board = " 3 ";
  player[COMP].ocean[4][0].board = " 4 ";
  player[COMP].ocean[5][0].board = " 5 ";
  player[COMP].ocean[6][0].board = " 6 ";
  player[COMP].ocean[7][0].board = " 7 ";
  player[COMP].ocean[8][0].board = " 8 ";
  player[COMP].ocean[9][0].board = " 9 ";
  player[COMP].ocean[10][0].board = "10 ";

  // rows
  for (int i = 1; i < 11; i++)
    for (int j = 1; j < 11; j++)
    {
      // fill the user board with "ocean"
      player[USER].ocean[i][j].board = "~";

      // fill the comp board with filler space
      player[COMP].ocean[i][j].board = ".";
    }
}

void Battleship::placeShips()
{
	// place comp ships


  player[USER].ocean[1][1].board = "C";
  player[USER].ocean[2][1].board = "C";
  player[USER].ocean[3][1].board = "C";
  player[USER].ocean[4][1].board = "C";
  player[USER].ocean[5][1].board = "C";

  player[USER].ocean[8][1].board = "B";
  player[USER].ocean[9][1].board = "B";
  player[USER].ocean[10][1].board = "B";
  player[USER].ocean[7][1].board = "B";

  player[USER].ocean[3][3].board = "Z";
  player[USER].ocean[3][4].board = "Z";
  player[USER].ocean[3][5].board = "Z";

  player[USER].ocean[5][7].board = "S";
  player[USER].ocean[5][8].board = "S";
  player[USER].ocean[5][9].board = "S";

  player[USER].ocean[6][4].board = "D";
  player[USER].ocean[7][4].board = "D";
}

void Battleship::printBoard()
{
//                    10 ~ ~ ~ D ~ ~ G ~ ~ ~          10 ~ ~ ~ D ~ ~ G ~ ~ ~
  cout << "                   YOUR MAP                       COMPUTER MAP\n";
/*
  player[USER].ocean[3][6].board = "O";
  player[USER].ocean[3][7].board = "O";
  player[USER].ocean[3][8].board = "O";
  player[COMP].ocean[3][6].board = "O";
  player[COMP].ocean[4][6].board = "O";
  player[COMP].ocean[5][6].board = "O";
  player[COMP].ocean[7][6].board = "~";
  player[COMP].ocean[8][6].board = "~";
  player[COMP].ocean[9][6].board = "~";
*/

  // loop the rows
  for (int i = 0; i < 11; i++)
  {
    // loop the cols

    cout << "          ";

    for (int j = 0; j < 11; j++)
    {
      if (player[USER].ocean[i][j].board == "~")
        cout << blue << player[USER].ocean[i][j].board << normal;

      // if user has been hit
      else if (player[USER].ocean[i][j].board == "X")
        cout << red << player[USER].ocean[i][j].board << normal;
      else
        cout << player[USER].ocean[i][j].board;
      if (j != 10)
        cout << " ";
    }

    cout << "          ";

    for (int j = 0; j < 11; j++)
    {
      if (player[COMP].ocean[i][j].board == "~")
        cout << blue << player[COMP].ocean[i][j].board << normal;
      else if (player[COMP].ocean[i][j].board == "O")
          cout << red << player[COMP].ocean[i][j].board << normal;
      else
        cout << player[COMP].ocean[i][j].board;
      if (j != 10)
        cout << " ";
    }

    cout << "\n\n";
  }
}

void Battleship::hitEnter()
{
  cout << "Press Enter to continue.\n";
  cin.ignore();
}

/*
 0 1 2
0  A B C D E F G H I J
 1 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 2 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 3 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 4 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 5 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 6 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 7 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 8 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
 9 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
10 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
*/
