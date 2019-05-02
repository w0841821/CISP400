// Hokeemon.cpp
// Erroll Abrahamian, CISP 400
// 05-05-2019

/*

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

const string NORMAL("\033[0;39m");
const string TEAL("\033[1;36m");
const string GREEN("\033[0;32m");
const string YELLOW("\033[0;93m");
const string ORANGE("\033[0;91m");
const string RED("\033[0;35m");

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
  int happy = 0; // boredom of 0-4
  string name;
  string listening;
  string playing;
  string passing;
  string colorBoredom;
  string levelBoredom;
  string colorHunger;
  bool dead;
  bool coma;
};

// Derived classes
// Specification C3 - Child Class
class Hokeemon: public Creature {
public:
	Hokeemon();
	string getName() { return name; }
    int getHunger() { return hunger; }
    int getBoredom() { return boredom; }
    void printHunger();
    void printBoredom();
    void printHappiness();
    bool isDead() { return dead; }
    bool inComa() { return coma; }
    void game();
    void listen();
    void play();
    void feed();
    void passTime();
    friend ostream& operator<< (ostream &out, const Hokeemon &hk);
};

ostream& operator<< (ostream &out, const Hokeemon &hk)
{
    cout << hk.name << "'s " << hk.colorBoredom << "boredom: " << hk.boredom << NORMAL << endl;
    cout << hk.name << "'s " << hk.colorHunger << "hunger:  " << hk.hunger << NORMAL << endl;
    return out;
}

Hokeemon::Hokeemon()
{
	hunger = (rand() % 6);
	boredom = (rand() % 6);
    setDead(false);
    setComa(false);
}

int main() {
    srand(time(0));

    // say Hi!!!!!

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
  cout << "\nYour Hokeemon is " << TEAL << h.name << NORMAL << "!" << endl;
  cout << TEAL << h.name << NORMAL << " is born with " << h.hunger << " hunger and " << h.boredom << " boredom." << endl;
  // cout << "Hokeemon boredom: " << h.getBoredom() << endl;
//  cout << h.name << "'s boredom: " << h.boredom << endl;

  int menu;
  bool quit = false;


    do {
        cout << "\n1. Listen\n2. Play\n3. Feed\n4. Quit\n\n";
        cout << "Enter your choice: ";
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
                break;

            default:
                cout << "Not valid input. Try again.\n";
        }
    } while(!quit && (!h.dead && !h.coma));
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
        if (b < 5)
            happy++;
        if (b > 20)
            setComa(true);
    }
    else
        boredom = 0;
}

void Hokeemon::printHunger()
{
    if (hunger < 2)
        colorHunger = GREEN;
    else if (hunger < 5)
        colorHunger = YELLOW;
    else if (hunger < 8)
        colorHunger = ORANGE;
    else
        colorHunger = RED;

    //cout << name << "'s " << colorHunger << "hunger:  " << hunger << NORMAL << endl;
}

void Hokeemon::printBoredom()
{
    if (boredom < 5) {
        colorBoredom = GREEN;
        levelBoredom = "happy";
    }
    else if (boredom < 10) {
        colorBoredom = YELLOW;
        levelBoredom = "OK";
    }
    else if (boredom < 15) {
        colorBoredom = ORANGE;
        levelBoredom = "frustrated";
    }
    else {
        colorBoredom = RED;
        levelBoredom = "mad";
    }

    //cout << name << "'s " << colorBoredom << "boredom: " << boredom << NORMAL << endl;
}

void Hokeemon::printHappiness()
{
    if (happy == 1)
        cout << "Happy time: " << happy << " turn!" << endl;
    else
        cout << "Happy time: " << happy << " turns!" << endl;
}

void Hokeemon::listen()
{
    listening = TEAL + "Listening to " + name + "..." + NORMAL;
    cout << endl << listening << endl;
    cout << string(listening.length() - 14, '-') << endl;
  // cout << "\nListening...\n";
  // cout << "Hunger: " << getHunger() << endl;
//  cout << "Hunger: " << hunger << endl;
 // cout << TEAL << name << "'s boredom: " << boredom << NORMAL << endl;


    cout << *this;
}

void Hokeemon::play()
{
    playing = "Playing with " + TEAL + name + NORMAL + "...";
    cout << endl << playing << endl;
    cout << string(playing.length() - 14, '-') << endl;

    cout << "\nPlaying...\n";
    // printBoredom


  cout << "Boredom goes from " << boredom << " to ";
  setBoredom(boredom - 4);
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
    passing = TEAL + "Some time passes, making " + name + " hungrier and more bored..." + NORMAL;

    this_thread::sleep_for(500ms);
    cout << endl << passing << endl;
    cout << string(passing.length() - 14, '-') << endl;
    this_thread::sleep_for(500ms);

    setHunger(getHunger() + 1);
    setBoredom(getBoredom() + 1);
    //cout << TEAL << name << NORMAL << endl;
    //cout << string(name.length(), '-') << endl;
    printHunger();
    printBoredom();
    cout << *this;
    printHappiness();

    if (isDead() && !inComa()) {
        cout << "...but, it seems " << TEAL << name << NORMAL << " died from hunger! :(\n";
        cout << "Better luck with your next Hokeemon :(\n\n";
    }
    else if (inComa() && !isDead()) {
        cout << "...but, it seems " << TEAL << name << NORMAL << " fell into a coma from boredom! :(\n";
        cout << "Better luck with your next Hokeemon :(\n\n";
    }
    else if (isDead() && inComa()) {
        cout << "I don't think you should get a pet. " << TEAL << name << NORMAL << " fell into a coma from boredom,\n";
        cout << "AND died from hunger.\n\n";
    }
}
