
#include <iostream>
#include <ctime>
using namespace std;

class Pig
{
private:
  bool userStart,
    goingAgain;
  int gamesPlayed,
    gamescoreUser,
    gamescoreCPU,
    die;
public:
  void sayHi();
  void coinFlip();
  void playPig();
  bool playAgain();
  void userStarts();
  void compStarts();
  int rollDie();
  bool rollCPU();
  void userMove();
  void compMove();
  void printScore();
};

int main() {
  srand(time(0));

  Pig game;

  game.sayHi();
  game.playPig();

  return 0;
}

void Pig::sayHi()
{
  cout << "Welcome to Pig! First one to 100 wins!\n";
}

void Pig::coinFlip()
{
  int flip = (rand() % 2);

  if (flip == 0)
    userStart = true;
  else
    userStart = false;
}

void Pig::playPig()
{
  gamesPlayed = 0;

  do {
    // increment number of games played by 1
    gamesPlayed++;
    gamescoreUser = 0;
    gamescoreCPU = 0;

    // coin flip to determine who starts
    coinFlip();

    // whoever starts, goes first
    if (userStart)
      userStarts();
    else
      compStarts();

    goingAgain = playAgain();
  } while(goingAgain);
}

bool Pig::playAgain()
{
  char playAgain;

  cout << "Play again? (y/n): ";
  do {
    cin >> playAgain;
    if (toupper(playAgain) == 'Y')
            goingAgain = true;
        else if (toupper(playAgain) == 'N')
            goingAgain = false;
        else
            cout << "\nNot a valid entry. Play again? (y/n)\n";
} while((toupper(playAgain) != 'N') && (toupper(playAgain) != 'Y'));

  return goingAgain;
}

void Pig::userStarts()
{
  int gameOver = 0;

  cout << "User starts.\n";

  do {
    printScore();
    userMove();
    if (gamescoreUser >= 100)
    {
      cout << "User wins!\n";
      gameOver = 1;
      break;
    }
    printScore();
    compMove();
    if (gamescoreCPU >= 100)
    {
      cout << "Comp wins!\n";
      gameOver = 1;
      break;
    }
  } while(gameOver == 0);
}

void Pig::compStarts()
{
  cout << "Comp starts.\n";
}

int Pig::rollDie()
{
  die = (rand() % 6) + 1;
  return die;
}

bool Pig::rollCPU()
{
  bool roll;
  die = (rand() % 6) + 1;
  if (die >= 1 && die <= 3)
    roll = true;
  else
    roll = false;
  return roll;
}

void Pig::userMove()
{
  char key;
  cout << "Enter 1 to roll die: ";
  cin >> key;
  if (key == '1')
    die = rollDie();
  gamescoreUser += die;
}

void Pig::compMove()
{
  cout << "\nWill be a comp move.\n";
  bool roll = rollCPU();
  if (roll)
  {
    die = rollDie();
    gamescoreCPU += die;
  }
  else
    cout << "No roll!\n";
}

void Pig::printScore()
{
  cout << "The score is " << gamescoreUser << " - " << gamescoreCPU << ".\n";
}
