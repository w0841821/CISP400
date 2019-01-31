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
    turns;
  char* userRecord = nullptr;
  int* turnRecord = nullptr;
  string userName;
public:
  void playPig();
  void getName();
  void coinToss(bool*);
  void userMove(bool*, bool*, bool*, bool*);
  void compMove(bool*, bool*);
  void rollDie(int*);
  void playAgain(bool*);
  void printScore();
  void printStats();
  void newArray();
  void incArray();
  void delArray();
};

int main()
{
  srand(time(0));
  Pig game;
  game.newArray();
  game.playPig();
  game.delArray();
  return 0;
}

void Pig::playPig()
{
  bool userTurn, forfeit, hold, loseTurn, quit, userWinner, compWinner;
  getName();
  do {
    coinToss(&userTurn);
    gamescoreUser = 0;
    gamescoreCPU = 0;
    turns = 0;
    gamesPlayed++;
    forfeit = false;
    quit = false;
    userWinner = false;
    compWinner = false;
    do {
      if (userTurn)
      {
        userTurn = false;
        turns++;
        printScore();
        userMove(&forfeit, &hold, &loseTurn, &quit);
        if (forfeit || quit)
        {
          userRecord[gamesPlayed-1] = 'F';
          break;
        }
        if (gamescoreUser >= 100)
        {
          userWinner = true;
          userRecord[gamesPlayed-1] = 'W';
          cout << "Congratulations, " << userName << ", you win!\n";
          break;
        }
      }
      else
      {
        userTurn = true;
        turns++;
        printScore();
        compMove(&hold, &loseTurn);
        if (gamescoreCPU >= 100)
        {
          compWinner = true;
          userRecord[gamesPlayed-1] = 'L';
          cout << "Sorry, the computer won :(\n";
          break;
        }
      }
    } while(!forfeit || !quit || !userWinner || !compWinner);
    turnRecord[gamesPlayed-1] = turns;
    playAgain(&quit);
    if (!quit)
      incArray();
  } while(!quit);

  printStats();
}

void Pig::getName()
{
  int count = 0,
    i;

  cout << "What's your name? ";
  cin.ignore();
  do {
    getline(cin, userName);

    for (i = 0; i < static_cast<int>(userName.length()); i++)
      if (userName[i] == ' ')
        count++;

    if (count != 1)
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
  *forfeit = false;
  *hold = false;
  *loseTurn = false;
  *quit = false;
  turnPoints = 0;
  char move;

  do {
    cout << "1. (R)oll\n";
    cout << "2. (H)old\n";
    cout << "3. (F)orfeit\n";
    cout << "4. (Q)uit\n";
    cin >> move;

    if (move == '1' || (toupper(move) == 'R'))
    {
      rollDie(&die);
      if (die == 1)
      {
        *loseTurn = true;
        cout << "Oops, you lost your turn by rolling a 1.\n";
      }
      else
      {
        turnPoints += die;
        cout << "You rolled a " << die << ", and currently have " << turnPoints << " turn points.\n";
      }
    }
    else if (move == '2' || (toupper(move) == 'H'))
    {
      *hold = true;
      gamescoreUser += turnPoints;
      cout << "You hold, with " << turnPoints << " turn points.\n";
    }
    else if (move == '3' || (toupper(move) == 'F'))
      {
        cout << "Are you sure you'd like to forfeit? (y/n) ";
        char forfCheck;
        cin >> forfCheck;
        if (toupper(forfCheck) == 'Y')
        {
          *forfeit = true;
          break;
        }
      }
    else if (move == '4' || (toupper(move) == 'Q'))
    {
      cout << "Are you sure you'd like to quit to the game? (y/n) ";
      char quitCheck;
      cin >> quitCheck;
      if (toupper(quitCheck) == 'Y')
      {
        *quit = true;
        break;
      }
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

void Pig::printStats()
{
  cout << "\nTotal games played: " << gamesPlayed << ".\n";
  for (int i = 0; i < gamesPlayed; i++)
    cout << "Game #" << i + 1 << " -- " << "Result: " << userRecord[i] << " -- " << "Turns: " << turnRecord[i] << ".\n";
}

void Pig::newArray()
{
  userRecord = new char[1];
  turnRecord = new int[1];
}

void Pig::incArray()
{
  char* tmpGames = nullptr;
  tmpGames = new char[gamesPlayed+1];
  int* tmpTurns = nullptr;
  tmpTurns = new int[gamesPlayed+1];

  for (int i = 0; i < (gamesPlayed+1); i++)
  {
    tmpGames[i] = userRecord[i];
    tmpTurns[i] = turnRecord[i];
  }

  delArray();

  userRecord = tmpGames;
  tmpGames = nullptr;
  turnRecord = tmpTurns;
  tmpTurns = nullptr;
}

void Pig::delArray()
{
  delete [] userRecord;
  delete [] turnRecord;
}
