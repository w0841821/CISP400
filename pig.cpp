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

1. (R)oll
2. (H)old
3. (R)esign
4. (Q)uit

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

main(){
  srand(time(0));
}







#include <iostream>
#include <string>
#include <cctype>
#include <thread>
#include <fstream>
using namespace std;

enum Rooms_Enum {POOL, LOBBY, PARKINGLOT0, PARKINGLOT1, BRIDGE, STREET0, STREET1, STREET2, HOME};

enum Dirs_Enum {N, S, E, W};

enum Mons_Enum {DINOSAUR, ZOMBIE, HAPPYFACE, XENOMORPH};

// use sentinel if we don't have an exit from a room, kept separate from Rooms_Enum
const int NONE = -1;

// number of rooms
const int ROOMS = 9;

// number of potential exit directions
const int EXITS = 4;

// number of potential monsters
const int MONS = 4;

struct Rooms
{
  string title,
    desc,
    look;
  bool visited,
    monster;
  int exit[EXITS];
} room[ROOMS];

struct Directions
{
  char compass;
  int dirNum;
} dirs[EXITS];

// Specification A1 - Monsters in their own struct
struct Monsters
{
  string name,
    ability,
    art,
    win,
    check;
  char winKey;
  bool fought;
} monst[MONS];

class GetHome
{
private:
  // current room, based on room number and Rooms_Enum
  int curRoom;

  // booleans for having keys and car in order to go home
  bool hasKeys = false,
    hasCar = false,

    // winner for, well, yeah
    winner = false,

    // reset upon death
    reset = false;

  // input for movement
  char move,

    // input to quit
    forSure;

  string playerName;

public:
  // function prototypes
  void setRooms(Rooms *rm);
  void setDirs(Directions *dir);
  void setMons(Monsters *mon);
  void sayHi();
  void gameMenu();
  void getName();
  void play(Rooms *rm, Monsters *mon);
  char getMove();
  void fightMonster(Rooms *rm, Monsters *mon);
  bool playRoom(char move, Rooms *rm, Directions *dir);
  bool makeMove(Rooms *rm, Directions *dir);
  bool checkWin(Rooms *rm);
  bool checkQuit();
  void printMeal();
  void resetGame(Rooms *rm, Monsters *mon);
};

int main()
{
  GetHome game;

  // random seed for monster usage
  srand(time(0));

  // establish the layout of the rooms and exit directions
  game.setRooms(room);

  // establish the directions and associated key inputs
  game.setDirs(dirs);

  // generate monsters
  game.setMons(monst);

  // say hi!
  game.sayHi();
  this_thread::sleep_for(1500ms);

  // show menu
  game.gameMenu();
  this_thread::sleep_for(1500ms);

  // get player name
  game.getName();

  // play the game!!
  game.play(room, monst);
}

void GetHome::setRooms(Rooms *rm)
{
  rm[POOL].title = "Swimming Pool";
  rm[POOL].desc = "You are floating in a swimming pool.\nThere is an exit to the south, but something doesn't feel right.\nIs there something in the water with you?\n\n";
  rm[POOL].look = "\nYou are floating in the swimming pool. Still.\nThere is an exit to the south.\n";
  rm[POOL].visited = true;
  rm[POOL].monster = true;
  rm[POOL].exit[N] = NONE;
  rm[POOL].exit[S] = LOBBY;
  rm[POOL].exit[E] = NONE;
  rm[POOL].exit[W] = NONE;

  rm[LOBBY].title = "Lobby";
  rm[LOBBY].desc = "You are in a hotel lobby. Did you stay here last night? It's all such a blur.\nYou see your (k)eys on the ground. Weird.\nNow, where did you park?\nOh, there's a parking lot to the south.\n\n";
  rm[LOBBY].look = "\nYou are in the hotel lobby.\nThe swimming pool is to the north.\nThe parking lot is to the south.\n";
  rm[LOBBY].visited = false;
  rm[LOBBY].monster = false;
  rm[LOBBY].exit[N] = POOL;
  rm[LOBBY].exit[S] = PARKINGLOT1;
  rm[LOBBY].exit[E] = NONE;
  rm[LOBBY].exit[W] = NONE;

  rm[PARKINGLOT0].title = "Parking Lot A";
  rm[PARKINGLOT0].desc = "You're in Parking Lot A.\nParking Lot B is to the east, and the rest is fenced.\nThat (c)ar over there looks familiar, though...\n\n";
  rm[PARKINGLOT0].look = "\nYou're in Parking Lot A.\nParking Lot B is to the east, and the rest is fenced.\n";
  rm[PARKINGLOT0].visited = false;
  rm[PARKINGLOT0].monster = false;
  rm[PARKINGLOT0].exit[N] = NONE;
  rm[PARKINGLOT0].exit[S] = NONE;
  rm[PARKINGLOT0].exit[E] = PARKINGLOT1;
  rm[PARKINGLOT0].exit[W] = NONE;

  rm[PARKINGLOT1].title = "Parking Lot B";
  rm[PARKINGLOT1].desc = "You're in Parking Lot B.\nTo the north is the lobby.\nTo the south is the street.\nTo the east is the parking lot fence.\nTo the west is Parking Lot A.\n\n";
  rm[PARKINGLOT1].look = "\nYou're in Parking Lot B.\nTo the north is the lobby.\nTo the south is the street.\nTo the east is the parking lot fence.\nTo the west is Parking Lot A.\n";
  rm[PARKINGLOT1].visited = false;
  rm[PARKINGLOT1].monster = false;
  rm[PARKINGLOT1].exit[N] = LOBBY;
  rm[PARKINGLOT1].exit[S] = STREET1;
  rm[PARKINGLOT1].exit[E] = NONE;
  rm[PARKINGLOT1].exit[W] = PARKINGLOT0;

  rm[BRIDGE].title = "Collapsed Bridge";
  rm[BRIDGE].desc = "You're at the edge of a collapsed bridge.\nThe only way out is the street to the east, but something's in the rubble...\n\n";
  rm[BRIDGE].look = "\nYou're at the edge of the collapsed bridge.\n";
  rm[BRIDGE].visited = false;
  rm[BRIDGE].monster = true;
  rm[BRIDGE].exit[N] = NONE;
  rm[BRIDGE].exit[S] = NONE;
  rm[BRIDGE].exit[E] = STREET0;
  rm[BRIDGE].exit[W] = NONE;

  rm[STREET0].title = "West Street";
  rm[STREET0].desc = "You're on the western-most part of the street.\nA bridge is to the west.\nThe street continues to the east, but your way is blocked!\n\n";
  rm[STREET0].look = "\nYou're on the western-most part of the street.\nA bridge is to the west.\nThe street continues to the east.\n";
  rm[STREET0].visited = false;
  rm[STREET0].monster = true;
  rm[STREET0].exit[N] = NONE;
  rm[STREET0].exit[S] = NONE;
  rm[STREET0].exit[E] = STREET1;
  rm[STREET0].exit[W] = BRIDGE;

  rm[STREET1].title = "Mid Street";
  rm[STREET1].desc = "You're on the middle of the street.\nThe street continues to the east and west.\nThe parking lot is to the north.\n\n";
  rm[STREET1].look = "\nYou're on the middle of the street.\nThe street continues to the east and west.\nThe parking lot is to the north.\n";
  rm[STREET1].visited = false;
  rm[STREET1].monster = false;
  rm[STREET1].exit[N] = PARKINGLOT1;
  rm[STREET1].exit[S] = NONE;
  rm[STREET1].exit[E] = STREET2;
  rm[STREET1].exit[W] = STREET0;

  rm[STREET2].title = "East Street";
  rm[STREET2].desc = "You're on the eastern-most part of the street.\nThe street continues to the west.\nYou see your house to the east! But what's that...\n\n";
  rm[STREET2].look = "\nYou're on the eastern-most part of the street.\nThe street continues to the west.\nYou see your house to the east.\n";
  rm[STREET2].visited = false;
  rm[STREET2].monster = true;
  rm[STREET2].exit[N] = NONE;
  rm[STREET2].exit[S] = NONE;
  rm[STREET2].exit[E] = HOME;
  rm[STREET2].exit[W] = STREET1;

  // Specification C1 - Five Rooms
  // Specification B3 - Add more rooms (9 total rooms)
  rm[HOME].title = "Home";
  rm[HOME].desc = "You're home! But do you have everything?\n\n";
  rm[HOME].look = "\nYou're home.\n";
  rm[HOME].visited = false;
  rm[HOME].monster = false;
  rm[HOME].exit[N] = NONE;
  rm[HOME].exit[S] = NONE;
  rm[HOME].exit[E] = NONE;
  rm[HOME].exit[W] = STREET2;

/* copypaste template
  rm[].title = "";
  rm[].desc = "";
  rm[].look = "";
  rm[].visited = false;
  rm[].monster = ;
  rm[].exit[N] = ;
  rm[].exit[S] = ;
  rm[].exit[E] = ;
  rm[].exit[W] = ;
*/
}

void GetHome::setDirs(Directions *dir)
{
  // compass is the key input of the direction
  // dirNum refers to the integer (set with Dirs_Enum)
  dir[N].compass = 'N';
  dir[N].dirNum = N;
  dir[S].compass = 'S';
  dir[S].dirNum = S;
  dir[E].compass = 'E';
  dir[E].dirNum = E;
  dir[W].compass = 'W';
  dir[W].dirNum = W;
}

void GetHome::setMons(Monsters *mon)
{
  mon[DINOSAUR].name = "Dinosaur";
  mon[DINOSAUR].ability = "\nThis thing is huge! Remember that one movie though?\nSome of the big ones don't see very well. What if you (c)rouched out of sight...\n";
  mon[DINOSAUR].art = "                              __\n                             /oo\\\n                            |    |\n                        ^^  (vvvv)   ^^\n                        \\\\  /\\__/\\  //\n                         \\\\/      \\//\n                          /        \\\n                         |          |    ^\n                        /          \\___/ |\n                       (            )     |\n                        \\----------/     /\n                          //    \\\\_____/\n                         W       W\n";
  mon[DINOSAUR].win = "\nYou managed to crouch long enough for the Dinosaur to move along.\nIt's someone else's problem now.\n";
  mon[DINOSAUR].check = "You should have (c)rouched.\n";
  mon[DINOSAUR].winKey = 'C';
  mon[DINOSAUR].fought = false;

  mon[ZOMBIE].name = "Zombie";
  mon[ZOMBIE].ability = "\nEw. How fast can you (g)et away?\n";
  mon[ZOMBIE].art = "                                 .....\n                                C C  /\n                               /<   /\n                ___ __________/_#__=o\n               /(- /(\\_\\________   \\\n               \\ ) \\ )_      \\o     \\\n               /|\\ /|\\       |'     |\n                             |     _|\n                             /o   __\\\n                            / '     |\n                           / /      |\n                          /_/\\______|\n                         (   _(    <\n                          \\    \\    \\\n                           \\    \\    |\n                            \\____\\____\\\n                            ____\\_\\__\\_\\\n                           /`   /`     o\\\n                          |___ |_______|\n";
  mon[ZOMBIE].win = "\nWow, you got away pretty fast.\n";
  mon[ZOMBIE].check = "You should have tried to (g)et away.\n";
  mon[ZOMBIE].winKey = 'G';
  mon[ZOMBIE].fought = false;

  mon[HAPPYFACE].name = "Happy Face";
  mon[HAPPYFACE].ability = "\nThis guy isn't even scary. All he wants is to bring (j)oy!\n";
  mon[HAPPYFACE].art = "                            _.-'''''-._\n                          .'  _     _  '.\n                         /   (_)   (_)   \\\n                        |  ,           ,  |\n                        |  \\`.       .`/  |\n                         \\  '.`'''''`.'  /\n                          '.  `'---'`  .'\n                            '-._____.-'\n";
  mon[HAPPYFACE].win = "\nBoy, you're sure pretty joyous!\n";
  mon[HAPPYFACE].check = "You should have tried to look (j)oyful. It is the holidays, after all.\n";
  mon[HAPPYFACE].winKey = 'J';
  mon[HAPPYFACE].fought = false;

  // Specification B1 - Extra Monster
  mon[XENOMORPH].name = "Xenomorph";
  mon[XENOMORPH].ability = "\nReminds me of a movie where they used a (f)lamethrower. Happen to have one?\n";
  mon[XENOMORPH].art = "         __.,,------.._\n      ,''   _      _   '`.\n     /.__, ._  -=- _'`    Y\n    (.____.-.`      ''`   j\n     VvvvvvV`.Y,.    _.,-'       ,     ,     ,\n        Y    ||,   ''\\         ,/    ,/    ./\n        |   ,'  ,     `-..,'_,'/___,'/   ,'/   ,\n   ..  ,;,,',-''\\,'  ,  .     '     ' ''' '--,/    .. ..\n ,'. `.`---'     `, /  , Y -=-    ,'   ,   ,. .`-..||_|| ..\nff\\\\`. `._        /f ,'j j , ,' ,   , f ,  \\=\\ Y   || ||`||_..\nl` \\` `.`.'`-..,-' j  /./ /, , / , / /l \\   \\=\\l   || `' || ||...\n `  `   `-._ `-.,-/ ,' /`'/-/-/-/-'''''`.`.  `'.\\--`'--..`'_`' || ,\n            '`-_,',  ,'  f    ,   /      `._   ``._     ,  `-.`'//         ,\n          ,-''' _.,-'    l_,-'_,,'          '`-._ . '`. /|     `.'\\ ,       |\n        ,',.,-''          \\=) ,`-.         ,    `-'._`.V |       \\ // .. . /j\n        |f\\\\               `._ )-.'`.     /|         `.| |        `.`-||-\\\\/\n        l` \\`                 '`._   '`--' j          j' j          `-`---'\n         `  `                     '`,-  ,'/       ,-''  /\n                                 ,'',__,-'       /,, ,-'\n                                 Vvv'            VVv'\n";
  mon[XENOMORPH].win = "\nThat's a pretty crispy Xenomorph. Maybe that can be lunch tomorrow.\n";
  mon[XENOMORPH].check = "You should have used the (f)lamethrower that you just happen to have.\n";
  mon[XENOMORPH].winKey = 'F';
  mon[XENOMORPH].fought = false;

/* copypaste template
  mon[].name = "";
  mon[].ability = "";
  mon[].art = "";
  mon[].win = "";
  mon[].check = "";
  mon[].winKey = '';
  mon[].fought = false;
*/
}

void GetHome::sayHi()
{
  system("clear");

  // program greeting
  cout << "Welcome to GET HOME, a text adventure!\nWill you be able to find your way home?\n";
}

void GetHome::gameMenu()
{
  cout << "\nYou will have the option to move north, south, east, or west.\n";
  cout << "You can do this using the N, S, E, and W keys.\n";
  cout << "You can look around the room using the L key.\n";
  cout << "You can bring up this menu again using the H key.\n";
  cout << "You can quit at any time using the Q key, unless in combat!\n\n";
  this_thread::sleep_for(1500ms);
  cout << "HINT: Sometimes there might be an action to (P)erform...\n\n";
}

void GetHome::getName()
{
  // Specification C2 - Player Name
  cout << "Who are you, by the way? ";
  cin >> playerName;
  cout << "\nAlright " << playerName << ", now let's get home!!!\n\n";
  this_thread::sleep_for(2000ms);
  system("clear");
}

void GetHome::play(Rooms *rm, Monsters *mon)
{
  bool validMove,
    quit = false;

  // default starting position
  curRoom = POOL;
  cout << rm[curRoom].title << "\n";
  cout << rm[curRoom].desc << "\n";

  do {
    // reset the reset bool upon relooping after reset (say that five times fast)
    reset = false;

    // fight a monster if the room has one
    if (rm[curRoom].monster == true)
      fightMonster(room, monst);

    // only get a move if the game isn't reset, aka we're still alive
    if (reset == false)
    {
      do {
      move = getMove();
      if (move != 'Q')
        validMove = playRoom(move, room, dirs);
      else
        quit = checkQuit();
      } while(!validMove && !quit);
    }

    // uh oh, we died
    else
    {
      validMove = true;
      curRoom = POOL;
      cout << "You died. Back to the start!\n\n";
      cout << rm[curRoom].title << "\n";
      cout << rm[curRoom].desc << "\n";
    }
  } while(!quit && !winner);
}

char GetHome::getMove()
{
  cout << "Now, what would you like to do? ";
  cin >> move;
  move = (toupper(move));
  return move;
}

void GetHome::fightMonster(Rooms *rm, Monsters *mon)
{
  bool validMonst;
  int x;

  do {
    // pick a random monster
    x = (rand() % 4);

    // if it's one we haven't fought, fight it...
    if (mon[x].fought == false)
      validMonst = true;

    // ...otherwise, pick another monster
    else
      validMonst = false;
  } while(!validMonst); // loop until we get a valid monster

  // mark the monster as fought to take it out of the rotation
  mon[x].fought = true;

  // mark the room as not having a monster, in case we return to the room later
  rm[curRoom].monster = false;
  this_thread::sleep_for(1500ms);
  cout << "\n\n";
  cout << string(10, ' ') << mon[x].name << string(10, ' ') << "VERSUS" << string(10, ' ') << playerName << "\n\n";

  // display the monster ascii art
  cout << mon[x].art;

  // and the monster's ability
  cout << mon[x].ability;

  cout << "\nWhat will you do??? ";
  cin >> move;
  move = (toupper(move));
  cout << string(80, '-') << "\n";

  // Specification A2 - Add combat (a different key to win the fight vs each monster)
  if (move == mon[x].winKey) // if we hit the key to beat the monster...
  {
    // display the victory line
    cout << mon[x].win;

    // remind what room we're in...still need to get out
    cout << rm[curRoom].look;
  }
  else // ...or if we don't
  {
    // print "death" message
    cout << mon[x].check;

    // run the reset function to start over
    resetGame(room, monst);
  }
}

// Specification C3 - Input Validation (the entire function, really)
bool GetHome::playRoom(char move, Rooms *rm, Directions *dir)
{
  // mark the room as visited to change output if we return to the room
  rm[curRoom].visited = true;

  // scenario if we are in lobby and pick up keys
  if (curRoom == LOBBY && move == 'K')
  {
    // if we don't have them already...
    if (hasKeys == false)
    {
      hasKeys = true;
      cout << string(80, '-') << "\n";
      cout << "\nYou picked up your car keys!\n";
      cout << "Oh, they have a little flashlight attached. Could be handy.\n\n";
    }

    // ...or if we do, oops
    else
      cout << "\nYou already have your keys.\n";
    return false;
  }

  // scenario if we are in the parking lot where the car is, we have our keys, and try to get in
  else if (curRoom == PARKINGLOT0 && move == 'C' && hasKeys)
  {
    // if we don't have the car already...
    if (hasCar == false)
    {
      hasCar = true;
      cout << string(80, '-') << "\n";
      cout << "\nYou got in your car!\n\n";
    }

    // or if we're already in it, oops
    else
      cout << "\nYou're already in your car.\n";
    return false;
  }

  // scenario: in parking lot, try to get in car, but without keys
  else if (curRoom == PARKINGLOT0 && move == 'C' && !hasKeys)
  {
    cout << string(80, '-') << "\n";
    cout << "\nYour car is locked. Where'd you leave your keys?\n\n";
    return false;
  }

  // l for look
  // Specification C5 - Detailed Look (reemphasizing the (k)eys and (c)ar)
  else if (move == 'L')
  {
    // reiterate that the keys are in the lobby, and the car is in the parking lot
    if ((curRoom == LOBBY && !hasKeys) || (curRoom == PARKINGLOT0 && !hasCar))
      cout << rm[curRoom].desc;
    else
      cout << rm[curRoom].look;
    return false;
  }

  // Specification B2 - Add more command options (just using H to bring up help again)
  else if (move == 'H')
  {
    gameMenu();
    return false;
  }

  // directionals
  else if (move == 'N' || move == 'S' || move == 'E' || move == 'W')
  {
    for (int i = 0; i < EXITS; i++)
    {
      // check the compass/direction
      if (move == dir[i].compass)
      {
        // scenario: if we are heading home on the move...
        if (rm[curRoom].exit[i] == HOME)
          // ...then check to see if we meet the requirements
          winner = checkWin(room);

        // otherwise we're moving in a valid direction
        else if (rm[curRoom].exit[i] != NONE)
        {
          curRoom = rm[curRoom].exit[i];
          cout << string(80, '-') << "\n";
          cout << "\nYou are now in " << rm[curRoom].title << ".\n\n";
          // Specification C4 - Abbreviated Room Description
          if (rm[curRoom].visited == false || (curRoom == LOBBY && !hasKeys) || (curRoom == PARKINGLOT0 && !hasCar))
            cout << rm[curRoom].desc;
          return true;
        }

        // or we're not moving in a valid direction
        else
        {
          cout << "You can't go that way!!\n";
          return false;
        }
      }
    }
    return true;
  }

  // invalid
  else
  {
    cout << "Not valid input. If you need a reminder, enter H for help!\n";
    return false;
  }
}

bool GetHome::checkWin(Rooms *rm)
{
  // checking that we have our keys and the car
  if (hasKeys && hasCar)
  {
    cout << string(80, '-') << "\n";
    cout << "\n\nYou made it home safe, and have your keys to get in.\n";
    this_thread::sleep_for(1500ms);
    cout << "Unfortunately, your porch light is out, and you can't see.\n";
    this_thread::sleep_for(1500ms);
    cout << "Oh! You have a flashlight on your keychain!\n";
    this_thread::sleep_for(1500ms);

    // Specification A3 - Dark room
    bool vision = false;
    char lightOn;
    cout << "Would you like to turn on the (f)lashlight so you can see? ";
    cin >> lightOn;
    lightOn = (toupper(lightOn));
    if (lightOn == 'F')
      vision = true;
    else
    {
      do {
        cout << "Stop fumbling with your (f)lashlight and turn it on! ";
        cin >> lightOn;
        lightOn = (toupper(lightOn));
        if (lightOn == 'F')
          vision = true;
      } while(!vision);
    }

    this_thread::sleep_for(1500ms);
    cout << "With your flashlight on, you're able to unlock the door.\n";
    this_thread::sleep_for(1500ms);
    cout << "Now that you're home after such a long day,\n";
    this_thread::sleep_for(1500ms);
    cout << "it's time to enjoy a sandwich...\n";
    this_thread::sleep_for(1500ms);
    printMeal();
    return true;
  }

  // or we don't have them
  else
  {
    cout << "\nYou just realized you left your house keys in your car. Oops.\n";
    cout << "Seems like you saw your car in the parking lot.\n";
    return false;
  }
}

bool GetHome::checkQuit()
{
  cout << "Are you sure? (Y to quit, any other key continues the journey) ";
  cin >> forSure;
  forSure = (toupper(forSure));
  if (forSure == 'Y')
    return true;
  else
    return false;
}

void GetHome::printMeal()
{
  cout << string(58, ' ') << "//\n";
  cout << string(57, ' ') << "//\n";
  cout << string(41, ' ') << "_______________//___\n";
  cout << string(39, ' ') << ".(______________//____).\n";
  cout << string(39, ' ') << "|              /       |\n";
  cout << string(39, ' ') << "|. . . . . . . / . . . |\n";
  cout << string(39, ' ') << "\\ . . . . . ./. . . . ./\n";
  cout << string(40, ' ') << "|           /        |\n";
  cout << string(20, ' ') << "_.---._             |::......./.........:|\n";
  cout << string(16, ' ') << "_.-~       ~-._         |:::::/  \\::/  \\:::::|\n";
  cout << string(12, ' ') << "_.-~               ~-._     |:::::\\__/::\\__/:::::|\n";
  cout << string(8, ' ') << "_.-~                       ~---.;::::::::::::::::::::|\n";
  cout << string(4, ' ') << "_.-~                                 ~\\::::\\______/::::::|\n";
  cout << string(1, ' ') << ".-~                                    _.;::::::::::::::::::/\n";
  cout << string(1, ' ') << ":-._                               _.-~ ./:::::::::::::::::|\n";
  cout << string(1, ' ') << "`-._~-._                   _..__.-~ _.-~|::/:::::::::::::::|\n";
  cout << string(2, ' ') << "/  ~-._~-._              / .__..--~----.WWWWWWWWWWWWWWWWWW'\n";
  cout << string(1, ' ') << "\\_____(_;-._\\.        _.-~_/       ~).. . \\\n";
  cout << string(4, ' ') << "/(_____  \\`--...--~_.-~______..-+_______)\n";
  cout << string(2, ' ') << ".(_________/`--...--~/    _/           /\\\n";
  cout << string(1, ' ') << "/-._     \\_     (___./_..-~__.....__..-~./\n";
  cout << string(1, ' ') << "`-._~-._   ~\\--------~  .-~_..__.-~ _.-~\n";
  cout << string(5, ' ') << "~-._~-._ ~---------'  / .__..--~\n";
  cout << string(9, ' ') << "~-._\\.        _.-~_/\n";
  cout << string(13, ' ') << "\\`--...--~_.-~\n";
  cout << string(14, ' ') << "`--...--~\n";
}

// Specification A4 - GAME OVER (start at the beginning if you "die")
void GetHome::resetGame(Rooms *rm, Monsters *mon)
{
  // make all rooms unvisited
  for (int i = 0; i < ROOMS; i++)
    rm[i].visited = false;

  // make all monsters available again
  for (int i = 0; i < MONS; i++)
    mon[i].fought = false;

  // reset the rooms to spawn monsters
  rm[0].monster = true;
  rm[4].monster = true;
  rm[5].monster = true;
  rm[7].monster = true;

  // "drop" the items
  hasKeys = false;
  hasCar = false;

  // boolean to trigger reset
  reset = true;
}
