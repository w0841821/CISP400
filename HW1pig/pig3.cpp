#include <iostream>
#include <ctime>
using namespace std;

class Pig
{
private:
  int gamesPlayed,
    gamescoreUser,
    gamescoreCPU;
public:
  void greeting();
  void playPig();
  void coinFlip(bool*);
  void userStarts();
  void compStarts();
  void printScore();
  void userMove();
  void compMove();
  void rollDie(int*);
  void rollCPU(int*);
  void userMenu();
  void playAgain(bool*);
};

int main()
{
  srand(time(0));

  Pig game;

  game.greeting();
  game.playPig();

  return 0;
}

void Pig::greeting()
{
  cout << "Welcome to Pig! If you're unfamiliar, here is a little refresher from our good friends at Wikipedia!\n\n";
  cout << "You are competing against the computer. First to 100 wins.\n\n";
  cout << "If you roll a 1, you lose your turn.\n\n";
  cout << "If you roll a 2 thru 6, it is added to your current turn's total, and your turn continues.\n\n";
  cout << "If you choose to hold, your current turn's total is added to your score.\n\n";
  cout << "Good luck!\n\n";
}

void Pig::playPig()
{
    bool userFirst;
    gamesPlayed = 0;

    // increment games played
    // reset gamescore for each
    //

    bool goingAgain;

    do {
      int die;

      gamesPlayed++;

      coinFlip(&userFirst);
      if (userFirst)
        userStarts();
      else
        compStarts();
      rollDie(&die);
      cout << "Dice roll is " << die << "\n";
      cout << "Games played: " << gamesPlayed << "\n";
      playAgain(&goingAgain);
    } while(goingAgain);
}

void Pig::coinFlip(bool* coin)
{
  int flip = (rand() % 2);
  if (flip == 0)
    *coin = true;
  else
    *coin = false;
}

void Pig::userStarts()
{
  bool gameOver;

  do {
    printScore();
    userMove();
    // gameOver if userscore is 100
    // or player forfeits
    // or player quits
    compMove();
    // gameOver if compscore is 100
    if (gamescoreCPU >= 100)
    {
      cout << "The computer wins! :(\n";
      gameOver = true;
      break;
    }
  } while(!gameOver);
}

void Pig::compStarts()
{
  cout << "Comp starts\n";
}

void Pig::printScore()
{
  cout << "The score is " << gamescoreUser << " - " << gamescoreCPU << ".\n";
}

void Pig::userMove()
{
  do {
    userMenu();

  } while(/* condition */);

}

void Pig::compMove()
{

}

void Pig::rollDie(int* roll)
{
  *roll = (rand() % 6) + 1;
}

void Pig::rollCPU(int* rollHoldCPU)
{
  *rollHoldCPU = (rand() % 6) + 1;
}

void Pig::userMenu()
{
  cout << "1. (R)oll\n";
  cout << "2. (H)old\n";
  cout << "3. (F)orfeit\n";
  cout << "4. (Q)uit\n";
}

void Pig::playAgain(bool* again)
{
  char playAgain;
  cout << "Would you like to play again? (y/n): ";
  do {
    cin >> playAgain;
    if (toupper(playAgain) == 'Y')
      *again = true;
    else if (toupper(playAgain) == 'N')
      *again = false;
    else
      cout << "Not a valid entry. Play again? (y/n): ";
  } while((toupper(playAgain) != 'N') && (toupper(playAgain) != 'Y'));
}
