// pig.cpp
// Erroll Abrahamian, CISP 400
// 02-02-2019

#include <iostream>
#include <ctime>
using namespace std;

class Pig
{
private:
  int die,
    gamescoreCPU,
    gamescoreUser,
    gamesPlayed = 0,
    turnPoints,
    userTurnCount,
    compTurnCount;
  char* userRecord = nullptr;
  int* turnRecord = nullptr;
  int* userTurns = nullptr;
  int* compTurns = nullptr;
  string userName;
public:

  // function prototypes
  void newMainArrays();
  void sayHi();
  void getName();
  void playPig();
  void coinToss(bool*);
  void userMove(bool*, bool*, bool*, bool*);
  void compMove(bool*, bool*);
  void rollDie(int*);
  void playAgain(bool*);
  void printScore();
  void printTurnResults();
  void printStats();
  void incMainArrays();
  void incUserTurns();
  void incCompTurns();
  void delMainArrays();
};

int main()
{
  // Specification C1 - Time Seed
  srand(time(0));
  Pig game;
  game.newMainArrays();
  game.sayHi();
  game.getName();
  game.playPig();
  game.delMainArrays();
  return 0;
}

void Pig::sayHi()
{

  // Program greeting
  cout << "Welcome to Pig!\n\n";
  cout << "If you're unfamiliar, here is a refresher.\n\n";
  cout << "You are competing against the computer. First to 100 points wins.\n\n";
  cout << "If you roll a 1, you lose your turn.\n";
  cout << "If you roll a 2 thru 6, it is added to your turn's total, and you continue.\n";
  cout << "If you choose to hold, your current turn's total is added to your score.\n\n";

  // get the current date and time
  time_t now = time(0);
  char* dateTime = ctime(&now);

  // Specification A3 - Current Date
  cout << "It looks like we are starting at " << dateTime << " \n";
  cout << "Press Enter to continue.\n";
  cin.get();
}

void Pig::playPig()
{
  bool userTurn, forfeit, hold, loseTurn, quit, userWinner, compWinner;

  // Specification A1 - Main Event Loop
  do {
    // Specification B2 - Randomize Start
    coinToss(&userTurn);

    // reset everything at the start of each loop (new game)
    gamescoreUser = 0;
    gamescoreCPU = 0;
    userTurnCount = 0;
    compTurnCount = 0;
    gamesPlayed++;
    forfeit = false;
    quit = false;
    userWinner = false;
    compWinner = false;

    do {

      // if it is the user's turn
      if (userTurn)
      {
        // flag userTurn as false to run the computer's turn next time thru the loop
        userTurn = false;

        // add 1 to the number of moves
        userTurnCount++;

        // print the current game score
        printScore();

        // get the user's move
        userMove(&forfeit, &hold, &loseTurn, &quit);

        // if the player forfeits or quits the program...
        if (forfeit || quit)
        {
          userRecord[gamesPlayed-1] = 'F';
          break;
        }

        // if the player scores 100 and wins...
        if (gamescoreUser >= 100)
        {
          // flag the user as the winner
          userWinner = true;

          // mark the game as a win
          userRecord[gamesPlayed-1] = 'W';
          cout << "Congratulations, " << userName << ", you win!\n";
          break;
        }

        // increment the userTurns array to hold the score of the next move
        incUserTurns();
      }

      // computer's turn
      else
      {
        // flag userTurn as true to get the user's turn next time thru the loop
        userTurn = true;

        // add 1 to the number of moves
        compTurnCount++;

        // print the current game score
        printScore();

        // generate the computer's move
        compMove(&hold, &loseTurn);

        // did the computer win?
        if (gamescoreCPU >= 100)
        {
          compWinner = true;

          // mark the game as a loss
          userRecord[gamesPlayed-1] = 'L';
          cout << "Sorry, the computer won :(\n";
          break;
        }
        incCompTurns();
      }
    } while(!forfeit || !quit || !userWinner || !compWinner);

    // save the number of turns from the game
    turnRecord[gamesPlayed-1] = userTurnCount + compTurnCount;

    // print the results from each turn
    printTurnResults();

    // as long as we aren't quitting, increment the dynamic arrays
    if (!quit)
      incMainArrays();

    // as long as we aren't forfeiting AND NOT QUITTING, ask if we should play again
    if (!forfeit && !quit)
      playAgain(&quit);

    // if we ARE forfeiting, clear the screen to help differentiate between new and old games
    if (forfeit)
    {
      system("clear");
      cout << "Starting a new game.\n";
    }

  // keep looping as long as the user doesn't quit
  } while(!quit);

  // upon quitting, print the compiled stats
  printStats();

  // don't forget to clear the dynamic arrays!
  delMainArrays();
}

void Pig::getName()
{
  int count = 0,
    i;

  cout << "What's your name? ";
  do {
    // Specification C2 - Student Name
    getline(cin, userName);

    // check for a space to confirm first name/last name
    for (i = 0; i < static_cast<int>(userName.length()); i++)
      if (userName[i] == ' ')
        count++;

    if (count != 1)

      // Bulletproof 1
      cout << "\nPlease enter a first and last name, with one space between.\n";
    } while(count != 1);

}

void Pig::coinToss(bool* coin)
{
  int flip = (rand() % 2);
  if (flip == 0)
    *coin = true;
  else
    *coin = false;
}

void Pig::userMove(bool* forfeit, bool* hold, bool* loseTurn, bool* quit)
{
  // reset everything on each turn
  *forfeit = false;
  *hold = false;
  *loseTurn = false;
  *quit = false;
  turnPoints = 0;
  char move;

  do {
    // Specification C3 - REPLACED
    // Specification B3 - Alpha Menu
    cout << "1. (R)oll\n";
    cout << "2. (H)old\n";

    // Specification B4 – Resign Option (triggers forfeit bool flag)
    cout << "3. (F)orfeit\n";
    cout << "4. (Q)uit\n";
    cin >> move;

    if (move == '1' || (toupper(move) == 'R'))
    {
      rollDie(&die);
      if (die == 1)
      {
        *loseTurn = true;
        userTurns[userTurnCount - 1] = 0;
        cout << "Oops, you lost your turn by rolling a 1.\n";
      }
      else
      {
        turnPoints += die;
        cout << "\nYou rolled a " << die << ", and currently have " << turnPoints << " turn points.\n\n";
      }
    }
    else if (move == '2' || (toupper(move) == 'H'))
    {
      *hold = true;
      gamescoreUser += turnPoints;

      // Specification B1 - Track each turn
      userTurns[userTurnCount - 1] = turnPoints;
      cout << "You hold, with " << turnPoints << " turn points.\n";
    }
    else if (move == '3' || (toupper(move) == 'F'))
      {
        // Bulletproof 2 - checking for a yes is most important
        cout << "Are you sure you'd like to forfeit? (y/n) ";
        char forfCheck;
        cin >> forfCheck;
        if (toupper(forfCheck) == 'Y')
        {
          *forfeit = true;
          userTurns[userTurnCount - 1] = 0;
          break;
        }
      }
    else if (move == '4' || (toupper(move) == 'Q'))
    {
      // Bulletproof 3 - checking for a yes, again, is most important
      cout << "\nAre you sure you'd like to quit to the game? (y/n) ";
      char quitCheck;
      cin >> quitCheck;
      if (toupper(quitCheck) == 'Y')
      {
        *quit = true;
        userTurns[userTurnCount - 1] = 0;
        break;
      }
    }
    // Bulletproof
    // Specification C4 - Bulletproof Menu
    else
    {
      cout << "\nOops, not a valid selection. Try again.\n";
      cout << "Valid selections are 1 thru 4, R, H, F, or Q.\n";
    }
  } while(!(*hold) && !(*forfeit) && !(*quit) && !(*loseTurn));
}

void Pig::compMove(bool* hold, bool* loseTurn)
{
  turnPoints = 0;
  *hold = false;
  *loseTurn = false;

  do {
    // check for hold or point roll
    rollDie(&die);

    // 1-3 results in a comp hold
    if (die >= 1 && die <= 3)
    {
      *hold = true;
      gamescoreCPU += turnPoints;
      compTurns[compTurnCount - 1] = turnPoints;
      cout << "The computer holds, with " << turnPoints << " turn points.\n";
      break;
    }

    // 4-6 results in a points roll
    else
    {
      rollDie(&die);
      if (die == 1)
      {
        *loseTurn = true;
        compTurns[compTurnCount - 1] = 0;
        cout << "The computer lost its turn.\n";
      }
      else
        turnPoints += die;
    }
  } while(!(*hold) && !(*loseTurn));
}

void Pig::rollDie(int* roll)
{
  *roll = (rand() % 6) + 1;
}

void Pig::playAgain(bool* quit)
{
  char playAgain;
  cout << "Would you like to play again? (y/n): ";
  do {
    cin >> playAgain;
    if (toupper(playAgain) == 'Y')
      *quit = false;
    else if (toupper(playAgain) == 'N')
      *quit = true;
    else
      cout << "Not a valid entry. Play again? (y/n): ";
  } while((toupper(playAgain) != 'N') && (toupper(playAgain) != 'Y'));
}

void Pig::printScore()
{
  cout << "\n" << userName << " " << gamescoreUser << " - Computer " << gamescoreCPU << ".\n";
}

void Pig::printTurnResults()
{
  cout << "\nUser rolls: ";
  for (int i = 0; i < userTurnCount; i++)
    cout << userTurns[i] << ", ";

  for (int i = 0; i < compTurnCount; i++)
    cout << compTurns[i] << ", ";
  cout << "END!\n";

  if (userRecord[gamesPlayed-1] == 'W')
    cout << "You won!\n";
  else
    cout << "You lost :(\n";

      // cout << userRecord[gamesPlayed-1] << "\n";
}

// Specification A2 - Group Stats
void Pig::printStats()
{
  cout << "\nTotal games played: " << gamesPlayed << ".\n";
  for (int i = 0; i < gamesPlayed; i++)
    cout << "Game #" << i + 1 << " -- " << "Result: " << userRecord[i] << " -- " << "Turns: " << turnRecord[i] << ".\n";
}

void Pig::newMainArrays()
{
  userRecord = new char[1];
  turnRecord = new int[1];
  userTurns = new int[1];
  compTurns = new int[1];
}

void Pig::incMainArrays()
{
  char* tmpGames = nullptr;
  tmpGames = new char[gamesPlayed + 1];
  int* tmpTurns = nullptr;
  tmpTurns = new int[gamesPlayed + 1];

  for (int i = 0; i < (gamesPlayed + 1); i++)
  {
    tmpGames[i] = userRecord[i];
    tmpTurns[i] = turnRecord[i];
  }

  delMainArrays();

  userRecord = tmpGames;
  tmpGames = nullptr;
  turnRecord = tmpTurns;
  tmpTurns = nullptr;
}

void Pig::incUserTurns()
{
  int* tmpUser = nullptr;
  tmpUser = new int[userTurnCount + 1];

  for (int i = 0; i < (userTurnCount + 1); i++)
    tmpUser[i] = userTurns[i];

  delete [] userTurns;

  userTurns = tmpUser;
  tmpUser = nullptr;
}

void Pig::incCompTurns()
{
  int* tmpComp = nullptr;
  tmpComp = new int[compTurnCount + 1];

  for (int i = 0; i < (compTurnCount + 1); i++)
    tmpComp[i] = compTurns[i];

  delete [] compTurns;

  compTurns = tmpComp;
  tmpComp = nullptr;
}

void Pig::delMainArrays()
{
  delete [] userRecord;
  delete [] turnRecord;
}
