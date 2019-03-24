/*
2. //Specification B2 - Log file to Disk
Record the battle in a time-stamped log file to disk. The timestamp should contain the run date and the time an activity occurred. Call the output file "log.txt".

2. // Specification A2 - MultiFire Game
This is a game option. Allow each side to fire once for each ship still afloat. Allow players to activate this option at the start of the game.

*/

// bb.cpp
// Erroll Abrahamian, CISP 400
// 03-24-2019

#include <iostream>
#include <thread>
using namespace std;

enum Ships_Enum {CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER};
enum Player_Enum {USER, COMP};

// Specification C1 - OOP
struct Player
{
  string name;
  int shipCount;

  struct Ships
  {
    string shipType, shipMark;
    int shipSize;
    bool shipSunk;//, placed;
    /*

    */
  } ship[5];

  struct Ocean
  {
    string board, hidden;
		bool taken, targeted;
  } ocean[11][11];

} player[2];

class Battleship
{
private:
  char normal[8] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
  char blue[8] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
  char red[8] = {0x1b, '[', '1', ';', '3', '1', 'm', 0};
  char colChar;
  int row, col, strLen;
  bool showHidden = false, gameOver = false, multifire;
  string coords;
public:
  void sayHi();
  void buildShips();
  void buildBoard();
  void placeShips();
  void printBoard();
  void gameMode();
  void playGame();
  bool coinToss();
  void getShot();
  void compShot();
  void convertCoords();
	void hitEnter();
};

int main()
{
  Battleship hw4;

  srand(time(0));

  hw4.buildShips();
  hw4.buildBoard();
	hw4.sayHi();

  hw4.placeShips();
  hw4.gameMode();
  hw4.playGame();

  return 0;
}

void Battleship::sayHi()
{
  cout << "Hi!\n\n";
	cout << "A missed shot will be marked with \"" << blue << "O" << normal << "\".\n";
	cout << "A hit will be marked with \"" << red << "X" << normal << "\".\n";
	cout << "Open ocean is indicated with \"" << blue << "≈" << normal << "\".\n\n";
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

  system("clear");
}

void Battleship::buildShips()
{
  player[USER].name = "User";

  player[USER].shipCount = 5;

  player[USER].ship[CARRIER].shipType = "Carrier";
  player[USER].ship[CARRIER].shipMark = "C";
  player[USER].ship[CARRIER].shipSize = 5;
  player[USER].ship[CARRIER].shipSunk = false;
  // player[USER].ship[CARRIER].placed = false;

  player[USER].ship[BATTLESHIP].shipType = "Battleship";
  player[USER].ship[BATTLESHIP].shipMark = "B";
  player[USER].ship[BATTLESHIP].shipSize = 4;
  player[USER].ship[BATTLESHIP].shipSunk = false;
  // player[USER].ship[BATTLESHIP].placed = false;

  player[USER].ship[CRUISER].shipType = "Cruiser";
  player[USER].ship[CRUISER].shipMark = "Z";
  player[USER].ship[CRUISER].shipSize = 3;
  player[USER].ship[CRUISER].shipSunk = false;
  // player[USER].ship[CRUISER].placed = false;

  player[USER].ship[SUBMARINE].shipType = "Submarine";
  player[USER].ship[SUBMARINE].shipMark = "S";
  player[USER].ship[SUBMARINE].shipSize = 3;
  player[USER].ship[SUBMARINE].shipSunk = false;
  // player[USER].ship[SUBMARINE].placed = false;

  player[USER].ship[DESTROYER].shipType = "Destroyer";
  player[USER].ship[DESTROYER].shipMark = "D";
  player[USER].ship[DESTROYER].shipSize = 2;
  player[USER].ship[DESTROYER].shipSunk = false;
  // player[USER].ship[DESTROYER].placed = false;

  player[COMP].name = "Computer";

  player[COMP].shipCount = 5;

  player[COMP].ship[CARRIER].shipType = "Carrier";
  player[COMP].ship[CARRIER].shipMark = "C";
  player[COMP].ship[CARRIER].shipSize = 5;
  player[COMP].ship[CARRIER].shipSunk = false;
  // player[COMP].ship[CARRIER].placed = false;

  player[COMP].ship[BATTLESHIP].shipType = "Battleship";
  player[COMP].ship[BATTLESHIP].shipMark = "B";
  player[COMP].ship[BATTLESHIP].shipSize = 4;
  player[COMP].ship[BATTLESHIP].shipSunk = false;
  // player[COMP].ship[BATTLESHIP].placed = false;

  player[COMP].ship[CRUISER].shipType = "Cruiser";
  player[COMP].ship[CRUISER].shipMark = "Z";
  player[COMP].ship[CRUISER].shipSize = 3;
  player[COMP].ship[CRUISER].shipSunk = false;
  // player[COMP].ship[CRUISER].placed = false;

  player[COMP].ship[SUBMARINE].shipType = "Submarine";
  player[COMP].ship[SUBMARINE].shipMark = "S";
  player[COMP].ship[SUBMARINE].shipSize = 3;
  player[COMP].ship[SUBMARINE].shipSunk = false;
  // player[COMP].ship[SUBMARINE].placed = false;

  player[COMP].ship[DESTROYER].shipType = "Destroyer";
  player[COMP].ship[DESTROYER].shipMark = "D";
  player[COMP].ship[DESTROYER].shipSize = 2;
  player[COMP].ship[DESTROYER].shipSunk = false;
  // player[COMP].ship[DESTROYER].placed = false;
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

  player[COMP].ocean[0][0].hidden = "   ";
  player[COMP].ocean[0][1].hidden = "A";
  player[COMP].ocean[0][2].hidden = "B";
  player[COMP].ocean[0][3].hidden = "C";
  player[COMP].ocean[0][4].hidden = "D";
  player[COMP].ocean[0][5].hidden = "E";
  player[COMP].ocean[0][6].hidden = "F";
  player[COMP].ocean[0][7].hidden = "G";
  player[COMP].ocean[0][8].hidden = "H";
  player[COMP].ocean[0][9].hidden = "I";
  player[COMP].ocean[0][10].hidden = "J";
  player[COMP].ocean[1][0].hidden = " 1 ";
  player[COMP].ocean[2][0].hidden = " 2 ";
  player[COMP].ocean[3][0].hidden = " 3 ";
  player[COMP].ocean[4][0].hidden = " 4 ";
  player[COMP].ocean[5][0].hidden = " 5 ";
  player[COMP].ocean[6][0].hidden = " 6 ";
  player[COMP].ocean[7][0].hidden = " 7 ";
  player[COMP].ocean[8][0].hidden = " 8 ";
  player[COMP].ocean[9][0].hidden = " 9 ";
  player[COMP].ocean[10][0].hidden = "10 ";


  // rows
  for (int i = 1; i < 11; i++)
    for (int j = 1; j < 11; j++)
    {
      // fill the user board with "ocean"
      player[USER].ocean[i][j].board = "≈";
      player[USER].ocean[i][j].taken = false;
      player[USER].ocean[i][j].targeted = false;

      // fill the comp board with filler space
      player[COMP].ocean[i][j].board = ".";
      player[COMP].ocean[i][j].hidden = "≈";
      player[COMP].ocean[i][j].taken = false;
      player[COMP].ocean[i][j].targeted = false;
    }
}

void Battleship::placeShips()
{
  bool vertical, valid;
  int lowX, highX, lowY, highY;
  char vert;

  // for each player...
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      cout << "When placing ships vertically, the ship will be placed downward from that point\n";
      cout << "otherwise they will be placed to the right from that point.\n";
      cout << "Directions will be flipped if the ship would run off the board.\n\n";
    }

    // place all their ships
    for (int j = 0; j < 5; j++) {
      do {
        valid = true;
        // player ships
        if (i == 0) {
          printBoard();

          // Specification A3 - Random Human Start
          cout << "Where would you like to place your " << player[USER].ship[j].shipType << "?" << endl;

          convertCoords();

          if (player[USER].ocean[row][col].taken) {
            cout << "The ship can't be placed here!\n\n";
            valid = false;
            break;
          }

          cout << "Would you like your ship placed vertically? (y, or any other key for no)\n";
          cin >> vert;
          cin.ignore();
          cout << endl;

          if (toupper(vert) == 'Y')
            vertical = true;
          else
            vertical = false;
        }

        // computer ships
        else {
          vertical = (rand() % 2);
          do {
            col = (rand() % 10) + 1;
            row = (rand() % 10) + 1;
          } while(player[COMP].ocean[row][col].taken);
        }

        if (vertical) {

          // if the ship would overrun the board, place it upward instead of downward
          if (row + (player[i].ship[j].shipSize - 1) > 10) {
            lowY = row - (player[i].ship[j].shipSize - 1);
            highY = row;
          }
          else {
            lowY = row;
            highY = row + (player[i].ship[j].shipSize - 1);
          }
        }

        // ..or if the ship will be placed horizontally
        else {
          if (col + (player[i].ship[j].shipSize - 1) > 10) {
            lowX = col - (player[i].ship[j].shipSize - 1);
            highX = col;
          }
          else {
            lowX = col;
            highX = col + (player[i].ship[j].shipSize - 1);
          }
        }

        // check if each of the cells are taken
        for (int k = 0; k < player[i].ship[j].shipSize; k++) {
          if (vertical) {
            for (int l = lowY; l <= highY; l++) {
              if (player[i].ocean[l][col].taken) {
                if (i == 0)
                  cout << "The ship can't be placed here!\n\n";
                valid = false;
                break;
              }
            }
          }
          else {
            for (int l = lowX; l <= highX; l++) {
              if (player[i].ocean[row][l].taken) {
                if (i == 0)
                  cout << "The ship can't be placed here!\n\n";
                valid = false;
                break;
              }
            }
          }
        }
      } while(!valid);

      // ship is able to be placed
      if (vertical) {
        for (int m = lowY; m <= highY; m++) {
          player[i].ocean[m][col].taken = true;
          if (i == 0)
            player[i].ocean[m][col].board = player[i].ship[j].shipMark;
          else
            player[i].ocean[m][col].hidden = player[i].ship[j].shipMark;
        }
      }
      else {
        for (int m = lowX; m <= highX; m++) {
          player[i].ocean[row][m].taken = true;
          if (i == 0)
            player[i].ocean[row][m].board = player[i].ship[j].shipMark;
          else
            player[i].ocean[row][m].hidden = player[i].ship[j].shipMark;
        }
      }





    } // end of ship
  } // end of player

  printBoard();

  cout << "Are you ready to sink some ships?\n";
  hitEnter();
  system("clear");
}

void Battleship::printBoard()
{
  cout << "                   YOUR MAP                       COMPUTER MAP\n";

  // loop the rows
  for (int i = 0; i < 11; i++)
  {
    // loop the cols

    cout << "          ";

    for (int j = 0; j < 11; j++) {
      if (player[USER].ocean[i][j].board == "≈")
        cout << blue << player[USER].ocean[i][j].board << normal;

      // if user has been hit
      else if (player[USER].ocean[i][j].board == "X")
        cout << red << player[USER].ocean[i][j].board << normal;

      // if a shot splashes the ocean
      else if (player[USER].ocean[i][j].board == "O")
        cout << blue << player[USER].ocean[i][j].board << normal;
      else
        cout << player[USER].ocean[i][j].board;
      if (j != 10)
        cout << " ";
    }

    cout << "          ";

    if (showHidden) {
      for (int j = 0; j < 11; j++) {
        if (player[COMP].ocean[i][j].hidden == "≈")
          cout << blue << player[COMP].ocean[i][j].hidden << normal;
        else if (player[COMP].ocean[i][j].hidden == "X")
          cout << red << player[COMP].ocean[i][j].hidden << normal;
        else if (player[COMP].ocean[i][j].hidden == "O")
          cout << blue << player[COMP].ocean[i][j].hidden << normal;
        else
          cout << player[COMP].ocean[i][j].hidden;
        if (j != 10)
          cout << " ";
      }
    }
    else {
      for (int j = 0; j < 11; j++) {
        if (player[COMP].ocean[i][j].board == "≈")
          cout << blue << player[COMP].ocean[i][j].board << normal;
        else if (player[COMP].ocean[i][j].board == "X")
          cout << red << player[COMP].ocean[i][j].board << normal;
        else if (player[COMP].ocean[i][j].board == "O")
          cout << blue << player[COMP].ocean[i][j].board << normal;
        else
          cout << player[COMP].ocean[i][j].board;
        if (j != 10)
          cout << " ";
      }
    }

    cout << endl;
  }

  cout << endl;
}

void Battleship::gameMode()
{
  int menu;
  cout << "You have the option to...\n\n";
  cout << "1. Play a regular game or...\n";
  cout << "2. Have the ability to fire once for each enemy ship still afloat.\n";
  cout << "Which do you choose?\n\n";
  cin >> menu;
  cin.ignore();
  switch (menu) {
    case 1: multifire = false;
      break;
    case 2: multifire = true;
      break;
    default: cout << "Oops, not a valid option.\n";
  }

  cout << "Alright, let's play!!\n\n";
  hitEnter();
}

void Battleship::playGame()
{
  bool userTurn;//, quit;
  int numShots;

  // main game loop
  userTurn = coinToss();
  showHidden = false;
  gameOver = false;
  do {
    // if it's the user's turn...
    if (userTurn) {
      if (multifire)
        numShots = player[COMP].shipCount;
      else
        numShots = 1;
      do {
        userTurn = false;
        cout << "IT IS YOUR TURN!\n\n";

        // ...ask for coordinates...
        getShot();
        if (gameOver) {
          cout << "Congratulations, you sank their fleet!\n\n";
          break;
        }
        else {
          cout << "You have " << player[USER].shipCount << " ships remaining,\n";
          cout << "and the computer has " << player[COMP].shipCount << " ships remaining.\n\n";
        }
        // printBoard();
        hitEnter();
        numShots--;
        if (multifire)
          cout << "You have " << numShots << " shots remaining.\n";
      } while(numShots > 0);
    }
    else {
      if (multifire)
        numShots = player[USER].shipCount;
      else
        numShots = 1;
      do {
        userTurn = true;
        cout << "IT IS THE COMPUTER'S MOVE\n";
        compShot();
        if (gameOver) {
          cout << "The computer sank your fleet.\n\n";
          break;
        }
        printBoard();
        hitEnter();
        numShots--;
        if (multifire)
          cout << "The computer has " << numShots << " shots remaining.\n";
      } while(numShots > 0);
    }
  } while(!gameOver);// || !quit);



  //} while(!quit);
}

bool Battleship::coinToss()
{
  bool coin = (rand() % 2);
  return coin;
}

void Battleship::getShot()
{
  bool turnOver;
  //  int count;
  // int x, y;

  do {
    turnOver = false;

    printBoard();
    showHidden = false;

    cout << "Where would you like to fire? (ex: A10)\n";

    convertCoords();

    if (colChar == 'X' && row == 0) {
      // Specification C3 - Secret Option
      showHidden = true;
      cout << "\nCheater cheater!!\n\n";
    }
    else if (strLen == 0 || strLen > 3) {
      cout << "\nDoesn't seem like proper coordinates.\n";
    }
    // Specification B1 - Validate Input
    else if (coords[0] < 65 || (coords[0] > 74 && coords[0] < 97) || coords[0] > 106) {
      cout << "\nI don't think we have that column on the board!\n";
    }
    else if (row > 10) {
      cout << "\nWe don't have that many rows on the board!\n";
    }
    else {
      // if we have targeted the coordinates before...
      // Specification A1 - Adv Input Validation
      if (player[COMP].ocean[row][col].targeted)
        cout << "\nYou've already fired at those coordinates!\n\n";

      // ...or if we haven't targeted
      else {
        turnOver = true;
        // mark the coords as targeted
        player[COMP].ocean[row][col].targeted = true;

        // if there is a ship present...
        if (player[COMP].ocean[row][col].taken) {
          cout << red << "\nYou hit an enemy ship!" << normal << "\n\n";
          if (player[COMP].ocean[row][col].hidden == "C") {
            player[COMP].ship[CARRIER].shipSize -= 1;
            if (player[COMP].ship[CARRIER].shipSize == 0) {
              player[COMP].ship[CARRIER].shipSunk = true;
              player[COMP].shipCount -= 1;
              cout << red << "...and you sank their Carrier!" << normal << "\n\n";
            }
          }
          else if (player[COMP].ocean[row][col].hidden == "B") {
            player[COMP].ship[BATTLESHIP].shipSize -= 1;
            if (player[COMP].ship[BATTLESHIP].shipSize == 0) {
              player[COMP].ship[BATTLESHIP].shipSunk = true;
              player[COMP].shipCount -= 1;
              cout << red << "...and you sank their Battleship!" << normal << "\n\n";
            }
          }
          else if (player[COMP].ocean[row][col].hidden == "Z") {
            player[COMP].ship[CRUISER].shipSize -= 1;
            if (player[COMP].ship[CRUISER].shipSize == 0) {
              player[COMP].ship[CRUISER].shipSunk = true;
              player[COMP].shipCount -= 1;
              cout << red << "...and you sank their Cruiser!" << normal << "\n\n";
            }
          }
          else if (player[COMP].ocean[row][col].hidden == "S") {
            player[COMP].ship[SUBMARINE].shipSize -= 1;
            if (player[COMP].ship[SUBMARINE].shipSize == 0) {
              player[COMP].ship[SUBMARINE].shipSunk = true;
              player[COMP].shipCount -= 1;
              cout << red << "...and you sank their Submarine!" << normal << "\n\n";
            }
          }
          else {
            player[COMP].ship[DESTROYER].shipSize -= 1;
            if (player[COMP].ship[DESTROYER].shipSize == 0) {
              player[COMP].ship[DESTROYER].shipSunk = true;
              player[COMP].shipCount -= 1;
              cout << red << "...and you sank their Destroyer!" << normal << "\n\n";
            }
          }

          player[COMP].ocean[row][col].board = "X";
          player[COMP].ocean[row][col].hidden = "X";
          if (player[COMP].shipCount == 0)
            gameOver = true;
        }

        // ...or not
        else {
          cout << blue << "\nMiss! You hit open ocean!" << normal << "\n\n";
          player[COMP].ocean[row][col].board = "O";
          player[COMP].ocean[row][col].hidden = "O";
        }
      }
    }
  } while(!turnOver);
}

void Battleship::compShot()
{
  bool goodCoords = false;
  colChar = ' ';

  do {
    col = (rand() % 10) + 1;
    row = (rand() % 10) + 1;

    // Specification C2 - Prohibit AI wasted shots
    if (player[USER].ocean[row][col].targeted == false)
      goodCoords = true;
  } while(!goodCoords);

  colChar = col + 64;

  player[USER].ocean[row][col].targeted = true;

  cout << "\nThe computer aims at " << colChar << row << "\n";
  for (int i = 1; i <= 3; i++) {
    cout << string(i, '.') << "\n";
    this_thread::sleep_for(500ms);
  }

  if (player[USER].ocean[row][col].taken) {
    cout << red << "\nThe computer hit one of your ships!" << normal << "\n\n";
    player[USER].ocean[row][col].board = "X";
  }
  else {
    cout << "\nThe computer missed your fleet.\n\n";
    player[USER].ocean[row][col].board = "O";
  }
}

void Battleship::convertCoords()
{
  int count = 1;
  coords = "";
  colChar = ' ';
  col = 0;
  row = 0;

  getline(cin, coords);
  strLen = coords.length();

  for (int i = (strLen - 1); i >= 1; i--) {
    row += ((coords[i] - 48) * count);
    count *= 10;
  }

  colChar = toupper(coords[0]);
  col = colChar - 64;
}

void Battleship::hitEnter()
{
  cout << "Press Enter to continue.\n";
  cin.ignore();
}
/*
a1, y
g3, no
d6, y
h8, no
b10, y*/
