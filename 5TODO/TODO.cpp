// TODO.cpp
// Erroll Abrahamian
// 04-07-2019
/*
Create a command line TODO list program.
Prompt your client.
The first character/symbol they enter will be the command.
Follow that with a space. Finally, enter the todo list item.
Example: "+ Study for Final" (don’t enter the quotes).
This causes Study for Final to be entered into the TODO list with today’s date.
You will need to have the following fields at a minimum: TODO itself, date added, and TODO Identification number, but you can add as many other fields as you wish.

// Specification C1 - + Symbol
Allow the user to enter tasks with a "+" symbol.

// Specification C2 - ? Symbol
Allow the user to display all tasks with a ? symbol.

// Specification C3 - - symbol
Allow the user to remove a task with a "-" symbol (use an ID number to remove the TODO). This doesn’t necessary mean you need to delete it immediately.

// Specification B1 - Overload «
Overload the insertion stream operator for output.

//Specification B2 - Save to disk
Save the TODOs so they persist when the program is restarted.

// Specification B3 - Quit symbol
Create a command symbol to quit the program.

// Specification A1 - Overload symbols
Overload the symbols in C1 and C3 to simplify coding those activities.

// Specification A2 - Copy Constructor
Decide how you want to deal with copying your TODO class(es). Then implement it.

// Specification A3 - Assignment
Similar to A2 above, decide how you want to deal with assignment for your TODO class(es). Then code your solution.
*/

#include <iostream>
#include <vector>
using namespace std;

struct Task {
  int tNum;
  string tName;
  string tDate;
}

class ToDoList {
private:
  int numToDo;
  string yr, mon, day;

public:
  void getDate();
}

int main() {
  ToDoList hw5;

  return 0;
}

void ToDoList::getDate() {
  time_t now = time(0);
  tm *dateTime = localtime(&now);
  int dtYear = (1900 + dateTime->tm_year);
  int dtMonth = (1 + dateTime->tm_mon);
  int dtDay = dateTime->tm_mday;
  yr = static_cast<string>(dtYear);
  mon = static_cast<string>(dtMonth);
  day = static_cast<string>(dtDay);
}
