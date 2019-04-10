// Hokeemon.cpp
// Erroll Abrahamian, CISP 400
// 05-06-2019

/*

2. If hunger exceeds 10, your Hokeemon will die of starvation! Each turn increases hunger by 1.
3. If boredom exceeds 20, your hokeemon will slip into an unresponsive catatonic state.


This is a menu driven program. Create a numeric menu which will allow you to select Listen, Play, Feed, or Quit. Do not accept any other options (unless you build those options into the game).

//Specification B2 - Moods
Boredom moods: >15: Mad,
        10-14: Frustrated,
        5-9: OK,
        0-4, Happy. Count how many turns your Hokeemon was happy.

// Specification B3 - Second Child Class
Implement a second, different, child class. You can choose which class to play with or play with both of them!

// Specification A2 - Copy Constructor/Assignment Operator
Decide how you want to handle these in your classes and code accordingly.

// Specification A3 - Code Protection
Use asserts or exceptions in at least one method/function to make your code more robust and reliable.

"X" Specification Bundle.
You can use these for any of the other specification categories. Do not comment the specification you are replacing with one of these and use the specification comment in this section instead.

// Specification X1 - Overload Operator?
Choose an operator to overload. Replace the ? with the symbol you overloaded.

// Specification X2 - Overload Operator??
Same as X1, but with a different symbol.

// Specification X3 - Save Game
Use file I/O to save and restore the game. This means you store the current values of the Hokeemon you have been playing with.
*/

#include <iostream>
#include <thread>
using namespace std;

// Base class
// Specification C2 - Virtual Class Creature
class Creature {
public:
  virtual int getHunger() = 0;
  virtual int getBoredom() = 0;
  virtual bool isDead() = 0;
  virtual bool inComa() = 0;
  void setName(string s) { name = s; }
  void setHunger(int h);
  void setBoredom(int b);
  void setDead(bool d) { dead = d; }
  void setComa(bool c) { coma = c; }

protected:
  int hunger;
  int boredom;
  int happy; // boredom of 0-4
  string name;
  bool dead;
  bool coma;
};

// Derived classes
// Specification C3 - Child Class
class Hokeemon: public Creature {
public:
  string getName() { return name; }
  int getHunger() { return hunger; }
  int getBoredom() { return boredom; }
  bool isDead() { return dead; }
  bool inComa() { return coma; }
  void game();
  void listen();
  void play();
  void feed();
  void passTime();
};

int main() {
  srand(time(0));
  Hokeemon hw6;
  hw6.game();
}

void Hokeemon::game()
{
  string hokName;
  Hokeemon h;

  // Specification A1 - Critter Name
  cout << "What would you like to name your Hokeemon?\n";
  cin >> hokName;

  h.setName(hokName);
  h.setHunger((rand() % 6));
  h.setBoredom((rand() % 6));
  h.setDead(false);
  h.setComa(false);

  cout << "Hokeemon name: " << h.getName() << endl;
  cout << "Hokeemon hunger: " << h.getHunger() << endl;
  cout << "Hokeemon boredom: " << h.getBoredom() << endl;

  int menu;
  bool quit = false;

  do {
    cout << "\n1. Listen\n2. Play\n3. Feed\n4. Quit\n\n";
    cin >> menu;
    // Specification B1 - Validate Input
    switch (menu) {
      case 1:
        h.listen();
        h.passTime();
        break;
      case 2:
        h.play();
        h.passTime();
        break;
      case 3:
        h.feed();
        h.passTime();
        break;
      case 4:
        quit = true;
      default:
        cout << "Not valid input. Try again.\n";
    }
  } while(!quit);
}

void Creature::setHunger(int h)
{
  if (h > 0) {
    hunger = h;
    if (h > 10)
      setDead(true);
  }
  else
    hunger = 0;
}

void Creature::setBoredom(int b)
{
  if (b > 0) {
    boredom = b;
    if (b > 20)
      setComa(true);
  }
  else
    boredom = 0;
  if (boredom < 5)
    happy++;
}

void Hokeemon::listen()
{
  cout << "\nListening...\n";
  cout << "Hunger: " << getHunger() << endl;
  cout << "Boredom: " << getBoredom() << endl;
}

void Hokeemon::play()
{
  cout << "\nPlaying...\n";
  cout << "Boredom goes from " << getBoredom() << " to ";
  setBoredom(getBoredom() - 4);
  cout << getBoredom() << "!\n";
}

void Hokeemon::feed()
{
  cout << "\nFeeding...\n";
  cout << "Hunger goes from " << getHunger() << " to ";
  setHunger(getHunger() - 4);
  cout << getHunger() << "!\n";
}

// Specification C1 - PassTime()
void Hokeemon::passTime()
{
  this_thread::sleep_for(500ms);
  cout << "\nSome time passes...\n";
  setHunger(getHunger() + 1);
  cout << "Hunger: " << getHunger() << endl;
  setBoredom(getBoredom() + 1);
  cout << "Boredom: " << getBoredom() << endl;

  if (isDead()) {
    cout << "It's dead! :(\n";
  }
  if (inComa()) {
    cout << "It's in a coma! :(\n";
  }
}
