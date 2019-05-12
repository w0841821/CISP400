// Hokeemon.cpp
// Erroll Abrahamian, CISP 400
// 05-05-2019

#include <iostream>
#include <fstream>
#include <thread>
#include <cassert>
using namespace std;

const string NORMAL("\033[0;39m");
const string TEAL("\033[1;36m");
const string GREEN("\033[0;32m");
const string YELLOW("\033[0;93m");
const string ORANGE("\033[0;91m");
const string RED("\033[0;35m");

// Specification C2 - Virtual Class Creature
class Creature {
protected:
    string name, colorBoredom, colorHunger, levelBoredom, levelHunger, playing, feeding, passing, listening;
    int hunger, boredom, happy;
    bool dead, coma;

public:
    Creature(string creatureName) {
        name = creatureName;
        hunger = (rand() % 6);
        boredom = (rand() % 6);
        happy = 0;
        dead = false;
        coma = false;
    }

    virtual int getHunger() = 0;
    virtual int getBoredom() = 0;
    void setName(string s) { name = s; }
    string getName() { return name; }
    void setHunger(int h);
    void setBoredom(int b);
    void setHappy(int h);
};

// Specification C3 - Child Class
class Hoke: public Creature {
public:
    Hoke(string name): Creature(name) {}

    virtual int getHunger() { return hunger; }
    virtual int getBoredom() { return boredom; }

    void textColor();
    void countHappy(int h);
    void listen();
    void play();
    void feed();
    void passTime();
    bool isDead() { return dead; }
    bool inComa() { return coma; }
    void savegame();
    void loadgame();
    friend ostream& operator<< (ostream &out, const Hoke &hk);
};

// replaces B3
// Specification X1 - Overload Operator<<
ostream& operator<< (ostream &out, const Hoke &hk)
{
    cout << hk.colorHunger << "Hunger:  " << hk.hunger << " (" << hk.levelHunger << ")" << NORMAL << endl;
    cout << hk.colorBoredom << "Boredom: " << hk.boredom << " (" << hk.levelBoredom << ")" << NORMAL << endl;
    cout << "Happy turns: " << hk.happy << endl;
    return out;
}

int main() {
    srand(time(0));
    string n;
    int menu;
    bool quit = false;

    // Program greeting
    cout << "Have you owned a Hokeemon before? They can get hungry (up to 10), and bored (up to 20).\n";

    this_thread::sleep_for(1s);
    cout << "You would rather take care of your Hokeemon though, right?\n";

    this_thread::sleep_for(1s);
    cout << "\n...right?\n\n";

    this_thread::sleep_for(1s);
    cout << "You have the magic ability to see exactly how bored,\n";

    this_thread::sleep_for(1s);
    cout << "and how hungry your Hokeemon is at any given time.\n\n";

    this_thread::sleep_for(1s);
    cout << "BUT!\n\n";

    this_thread::sleep_for(1s);
    cout << "Hokeemon like to sit around a lot, so they'll constantly get hungry and bored!\n";

    // Specification A1 - Critter Name
    cout << "What would you like to name your very own Hokeemon? ";
    cin >> n;
    Hoke hok(n);

    system("clear");
    cout << "Take good care of " << TEAL << hok.getName() << NORMAL << "!\n";

    do {
        // Specification B1 - Validate Input
        cout << "\n1. Listen to your Hokeemon\n";
        cout << "2. Feed (reduces hunger)\n";
        cout << "3. Play (reduces boredom)\n";
        cout << "4. Save\n";
        cout << "5. Load\n";
        cout << "6. Quit\n\n";
        cout << "Enter your choice: ";
        cin >> menu;

        switch (menu) {
            case 1:
                hok.listen();
                hok.passTime();
                break;
            case 2:
                hok.feed();
                hok.passTime();
                break;
            case 3:
                hok.play();
                hok.passTime();
                break;
            case 4:
                cout << "Saving\n";
                hok.savegame();
                break;
            case 5:
                cout << "Loading.\n";
                hok.loadgame();
                break;
            case 6:
                cout << "Hope you had fun!\n";
                quit = true;
                break;
            default:
                cout << "Not valid.\n";
        }
    } while(!quit && (!hok.isDead() && !hok.inComa()));

    return 0;
}

void Creature::setHunger(int h)
{
    if (h > 0) {
        hunger = h;
        if (h > 10)
            dead = true;
    }
    else
        hunger = 0;

    // Specification A3 - Code Protection
    assert(hunger >= 0);
}

void Creature::setBoredom(int b)
{
    if (b > 0) {
        boredom = b;
        if (b > 20)
            coma = true;
    }
    else
        boredom = 0;

    assert(boredom >= 0);
}

void Creature::setHappy(int h)
{
    happy = h;
}

void Hoke::textColor()
{
    if (hunger < 2) {
        colorHunger = GREEN;
        levelHunger = "full";
    }
    else if (hunger < 5) {
        colorHunger = YELLOW;
        levelHunger = "snacky";
    }
    else if (hunger < 8) {
        colorHunger = ORANGE;
        levelHunger = "hungry";
    }
    else {
        colorHunger = RED;
        levelHunger = "starving";
    }

    if (boredom < 5) {
        colorBoredom = GREEN;
        // Specification B2 - Moods
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
}

void Hoke::countHappy(int h)
{
    if (h < 5)
        happy++;
}

void Hoke::listen()
{
    listening = TEAL + "Listening to " + name + "..." + NORMAL;
    cout << "\n\n" << listening << endl;
    cout << string(listening.length() - 14, '-') << endl;

    textColor();
    cout << *this;
}

void Hoke::play()
{
    playing = "Playing with " + TEAL + name + NORMAL + "...";
    cout << endl << playing << endl;
    cout << string(playing.length() - 14, '-') << endl;

    cout << "Boredom goes from " << boredom << " to ";
    setBoredom(boredom - 4);
    cout << boredom << "!\n";
}

void Hoke::feed()
{
    feeding = "Feeding " + TEAL + name + NORMAL + "...";
    cout << endl << feeding << endl;
    cout << string(feeding.length() - 14, '-') << endl;

    cout << "Hunger goes from " << hunger << " to ";
    setHunger(hunger - 4);
    cout << hunger << "!\n";
}

// Specification C1 - PassTime()
void Hoke::passTime()
{
    passing = TEAL + "Some time passes, making " + name + " hungrier and more bored..." + NORMAL;

    this_thread::sleep_for(1s);
    cout << "\n\n" << passing << endl;
    cout << string(passing.length() - 14, '-') << endl;

    setHunger(hunger + 1);
    setBoredom(boredom + 1);
    countHappy(boredom);

    textColor();
    cout << *this;

    if (dead && !coma) {
        cout << "...but, it seems " << TEAL << name << NORMAL << " died from hunger! :(\n";
        cout << "Better luck with your next Hokeemon :(\n\n";
    }
    else if (coma && !dead) {
        cout << "...but, it seems " << TEAL << name << NORMAL << " fell into a coma from maddening boredom! :(\n";
        cout << "Better luck with your next Hokeemon :(\n\n";
    }
    else if (dead && coma) {
        cout << "I don't think you should get a pet. " << TEAL << name << NORMAL << " fell into a coma from boredom,\n";
        cout << "AND died from hunger.\n\n";
    }
}

// replaces A2
// Specification X3 - Save Game
void Hoke::savegame()
{
    ofstream saveFile;
    saveFile.open("save.txt");

    saveFile << name << "," << hunger << "," << boredom << "," << happy;

    saveFile.close();

    cout << "\nGame saved!\n\n";
}

void Hoke::loadgame()
{
    ifstream saveFile;
    saveFile.open("save.txt");

    string catchString = "";
    if (!saveFile) {
        cout << "Looks like you don't have a Hokeemon yet!\n\n";
    }
    else {
        while (!saveFile.eof()) {
            getline(saveFile, catchString, ',');
            setName(catchString);

            getline(saveFile, catchString, ',');
            setHunger(stoi(catchString));

            getline(saveFile, catchString, ',');
            setBoredom(stoi(catchString));

            getline(saveFile, catchString, ',');
            setHappy(stoi(catchString));
        }

    saveFile.close();

    cout << "\nGame loaded!\n\n";
    }
}
