// pig.cpp
// Erroll Abrahamian
// 02-03-2019

/*
Requirements

Display the game score every time the active player changes.

Use whatever techniques you think best for creating reliable code which is easy to read and maintain. Do not optimize for computer performance. Choose data structures which are easy to expand, or preferably, automatically re-size themselves (if needed).

Make your output as clear and easy to understand as possible. Use structured programming or object oriented programming techniques.

You cannot use any data structures from the standard template library. No vectors or anything like that.

Make a simple AI with a random number. Each decision the computer rolls, 1-3 hold, 4-6 roll again.

Style guide elements apply: comments, layout, Program Greeting, Source File Header, and variables etc. etc.
• // Bulletproof 1, 2, etc.
Use this comment for every validation check you make with your program. A validation check should provide the client as specific an error message as possible. If you look for 4, rather specific input errors and you provide the client with 4 different error messages, then you should have // Bulletproof 1, // Bulletproof 2, // Bulletproof 3, and // Bulletproof 4 comments appearing right above each of the 4 sections of code. The general rule is to provide the client with as specific error correction information as possible.
*/

// Specification C1 - Time Seed
// Get the current time and use it for a random number seed.
// srand(time(0));

// Specification C2 - Student Name
// Allow name to accept first plus last name (ie 2 words). Display it somewhere in the output.
/* void GetHome::getName()
{
  // Specification C2 - Player Name
  cout << "Who are you, by the way? ";
  cin >> playerName;
}
*/

// Specification C3 - Numeric Menu
// Use a numeric menu to collect the human players actions. See figure 1 for an example menu.

// Specification C4 - Bulletproof Menu
// Detect and re-prompt if incorrect data is entered.

// Specification B1 - Track each turn
// Keep track of the points each player scores each turn.
// nullptr array, cpuMove[x], plMove[x]

// Specification B2 - Randomize Start
// Randomly determine which player starts the game.
/*
bool coinFlip()
{
    bool userFirst;

    // generate a random 0 or 1 to determine who goes first
    int theFlip = (rand() % 2);
    if (theFlip == 0)
        userFirst = true;
    else
        userFirst = false;
    return userFirst;
}
*/

// Specification B3 - Alpha Menu
// Switch to an alphanumeric menu. List specification C3 like this:
    // Specification C3 - REPLACED. Put this comment right above specification B3.
    // Note: Specification C4 now applies to this alphanumeric menu.

// Specification B4 – Resign Option
// The human can quit the current game and automatically restart a new one. See figure 2 for an example menu.

/*
1. (R)oll
2. (H)old
3. (R)esign
4. (Q)uit
*/

// Specification A1 - Main Event Loop
// Run the program in a main event loop. Prompt the player when the game ends if they want to play another game. Use a ’y’ or ’n’ prompt to stop playing games.

// Specification A2 - Group Stats
// Keep track of the number of games played, who won and lost each game and the number of turns each game took. Don’t forget to keep track of games resigned, too.

/* when grandPoints = 100
// gamesPlayed++
//

*/

// Specification A3 - Current Date
// Include in the program greeting the current date and time this program started. Use a library to automatically get this, do not ask the client to enter it.

#include <iostream>
using namespace std;

class Pig
{
private:
  int flip;
  bool playerStart;
public:
  void sayHi();
  void gameMenu();
  void coinFlip();
  void playPig();
  void playerMove();
  void compMove();
};

int main()
{
  srand(time(0));
  Pig game;
  game.sayHi();
  game.gameMenu();
  game.coinFlip();
  game.playPig();

  // bool playerStart = game.coinFlip();
}

void Pig::sayHi()
{
  cout << "Generic welcome.\n";
}

void Pig::gameMenu()
{
  cout << "Generic menu.\n";
}

void Pig::coinFlip()
{
  flip = (rand() % 2);

  if (flip == 0)
  {
    cout << "player\n";
    playerStart = true;
  }
  else
  {
    playerStart = false;
    cout << "cpu\n";
  }
}

void Pig::playPig()
{
  if (playerStart == true)
    playerMove();
  else
    compMove();
}

void Pig::playerMove()
{
  cout << "Here's the player move.\n";
}

void Pig::compMove()
{
  cout << "Here's the computer move.\n";
}

/*
bool Pig::coinFlip()
{
  bool playerStart;

  flip = (rand() % 2);

  if (flip == 0)
  {
    cout << "player\n";
    playerStart = true;
  }
  else
  {
    playerStart = false;
    cout << "cpu\n";
  }

  return playerStart;
}
*/
