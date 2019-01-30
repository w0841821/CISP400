// pig.cpp
// Erroll Abrahamian
// 02-03-2019

/*
Display the game score every time the active player changes.

Style guide elements apply: comments, layout, Program Greeting, Source File Header, and variables etc. etc.
• // Bulletproof 1, 2, etc.
Use this comment for every validation check you make with your program. A validation check should provide the client as specific an error message as possible. If you look for 4, rather specific input errors and you provide the client with 4 different error messages, then you should have // Bulletproof 1, // Bulletproof 2, // Bulletproof 3, and // Bulletproof 4 comments appearing right above each of the 4 sections of code. The general rule is to provide the client with as specific error correction information as possible.
*/

// Specification C4 - Bulletproof Menu
// Detect and re-prompt if incorrect data is entered.




// Specification A1 - Main Event Loop
// Run the program in a main event loop. Prompt the player when the game ends if they want to play another game. Use a ’y’ or ’n’ prompt to stop playing games.

// Specification A2 - Group Stats

#include <iostream>
#include <ctime>
using namespace std;

class Pig
{
private:
  bool playerStart;
  int gamesPlayed = 0;
  int* gameResult = nullptr;
  int playerForfeit = 0;
  int* gameTurns = nullptr;
public:
  void sayHi();
  void playerName();
  void coinFlip();
  void playPig();
  void playerMove();
  void compMove();
  void printScore();
  int rollDie();
  bool rollCPU();
};

int main()
{
  // Specification C1 - Time Seed
  srand(time(0));

  Pig game;

  game.sayHi();
  game.playerName();
  game.buildArrays();
  game.coinFlip();
  game.playPig();
}

void Pig::sayHi()
{
  time_t now = time(0);
  char* dateTime = ctime(&now);

  cout << "Welcome to Pig! Who will get to 100 points first?\n\n";

  // Specification A3 - Current Date
  cout << "It is currently " << dateTime << "\n";
}

void Pig::playerName()
{
  // get player name
  // Specification C2 - Student Name
}

void Pig::buildArrays()
{

}

void Pig::coinFlip()
{
  int flip;

  // Specification B2 - Randomize Start
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
  // do while not quit/forfeit
  // playerMove
  // show score
  // computer move
  // repeat
    playerMove();
  else
    compMove();
}

void Pig::playerMove()
{
  char playMove;

  // Specification C3 - REPLACED
  // Specification B3 - Alpha Menu
  cout << "1. (R)oll\n";
  cout << "2. (H)old\n";
  cout << "3. (F)orfeit\n";
  cout << "4. (Q)uit\n\n";
  cout << "Enter the number or letter for your move: ";
  cin >> playMove;

  if (playMove == '1' || toupper(playMove) == 'R')
  {
    rollDie();
    // add 1 total turn
    // if 1, lose turn
    // if 2 thru 6, playerScore += dice roll
    // add new element to keep track of turn score
  }
  else if (playMove == '2' || toupper(playMove) == 'H') {
    // add 1 total turn
    // add new element to keep track of turn score
  }

  // Specification B4 – Resign Option
  // The human can quit the current game and automatically restart a new one. See figure 2 for an example menu.
  else if (playMove == '3' || toupper(playMove) == 'F') {
    // declare forfeit
  }
  else if (playMove == '4' || toupper(playMove) == 'Q') {
    /* code */
  }
  else
  {

  }

  // Specification B1 - Track each turn
  // Keep track of the points each player scores each turn.

  // if playerScore >= 100, declare win
  // else go to compMove

}

void Pig::compMove()
{
  bool roll = rollCPU();

  if (roll)
    rollDie();
  else
    // code for holding

  // if compScore >= 100, declare loss
  // else go to playerMove
}

void Pig::printScore()
{

}

int Pig::rollDie()
{
  int dieRoll = (rand() % 6);
}

bool Pig::rollCPU()
{
  bool roll;
  int dieRoll = (rand() % 6);

  if (dieRoll >= 1 && flip <= 3)
    roll = false;
  else
    roll = true;
  return roll;
}
