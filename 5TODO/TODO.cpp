// TODO.cpp
// Erroll Abrahamian
// 04-07-2019

/*
//Specification B2 - Save to disk
Save the TODOs so they persist when the program is restarted.

// Specification A2 - Copy Constructor
Decide how you want to deal with copying your TODO class(es). Then implement it.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Tasks
{
private:
  int taskNum;
  string taskName;
  string taskDate;

public:
  friend class ToDoList;

  // Specification A3 - Assignment
  Tasks() {taskNum = 0; taskName = ""; taskDate = "";}

  int getTaskNum() const {return taskNum;}
  string getTaskName() const {return taskName;}
  string getTaskDate() const {return taskDate;}
};

class ToDoList
{
private:
  vector<Tasks> taskVec;
  int taskNumMax = 1;

public:
  string getDate();
    void sayHi();

  ToDoList operator+ (const string &str);
  ToDoList operator- (const string &str);
  friend ostream &operator << (ostream &out, const ToDoList &t);
};

// Specification A1 - Overload symbols
ToDoList ToDoList::operator+ (const string &str)
{
  Tasks tempTask;

  tempTask.taskNum = taskNumMax;
  tempTask.taskName = str;
  tempTask.taskDate = getDate();

  taskVec.push_back(tempTask);
  taskNumMax++;

  cout << "Added: " << str << " to the list!\n";

  return *this;
}

ToDoList ToDoList::operator- (const string &str)
{
  int tempInt = stoi(str);

  vector<Tasks>::iterator it;

  for (it = taskVec.begin(); it != taskVec.end(); it++) {
    if (it->taskNum == tempInt) {
      cout << "Removed: " << it->taskName << endl;
      taskVec.erase(it);
      break;
    }
  }

  return *this;
}

// Specification B1 - Overload «
ostream &operator<< (ostream &out, const ToDoList &t)
{
  // format width of number column to make output consistent
  int wid = (t.taskNumMax / 10) + 1;

  cout << setw(wid) << "#" << "   " << "TASKS\n";
  for (size_t i = 0; i < t.taskVec.size(); i++)
    out << setw(wid) << t.taskVec[i].getTaskNum() << "   " << t.taskVec[i].getTaskDate() << "   " << t.taskVec[i].getTaskName() << endl;

  return out;
}

int main()
{
  ToDoList taskVec;

  taskVec.sayHi();

  string taskCommand = "null";
  string taskAdd = "";
  string taskDel = "";

  // Specification B3 - Quit symbol
  while (taskCommand != "!") {
    cout << "\nTask command: ";
    getline(cin, taskCommand);

    // Specification C1 - + Symbol
    if (taskCommand.compare(0, 1, "+") == 0) {
        // if user enters "+ "...
        if (taskCommand.compare(1, 1, " ") == 0) {
            taskAdd = taskCommand.substr(2);
            // ...and there is text afterward...
            if (!taskAdd.empty())
                taskVec = taskVec + taskAdd;
            // ...or there is no text
            else
                cout << "I don't think you meant to add an empty task, did you?\n";
        }
        // if the user doesn't include a space after +
        else
            cout << "If you'd like to enter a new task, don't forget a space after the +.\n";
    }

    // Specification C3 - - symbol
    else if (taskCommand.compare(0, 1, "-") == 0) {
        if (taskCommand.compare(1, 1, " ") == 0) {
            // remove task
            taskDel = taskCommand.substr(2);
            if (!taskDel.empty())
                taskVec = taskVec - taskDel;
        }
        else
            cout << "If you'd like to remove a task, don't forget a space after the -.\n";
    }

    // Specification C2 - ? Symbol
    else if (taskCommand.compare(0, 1, "?") == 0) {
      cout << taskVec;
    }

    else if (taskCommand.compare(0, 1, "!") == 0) {
      cout << "All done entering tasks!\n";
    }

    // any other input
    else
      cout << "Not valid input.\n";
  }

  return 0;
}

string ToDoList::getDate()
{
  string date = "";

  time_t now = time(0);
  tm *dateTime = localtime(&now);

    int dtYear = (1900 + dateTime->tm_year);
  int dtMonth = (1 + dateTime->tm_mon);
  int dtDay = dateTime->tm_mday;

  string strMonth;
  string strDay;

  if (dtMonth < 10) {
    strMonth = " " + to_string(dtMonth);
  }
  else
    strMonth = to_string(dtMonth);

  if (dtDay < 10) {
    strDay = " " + to_string(dtDay);
  }
  else
    strDay = to_string(dtDay);

    date = to_string(dtYear) + "/" + strMonth + "/" + strDay;

  return date;
}

void ToDoList::sayHi()
{
    cout << "Hello there!\n\n";

    cout << "It must be time to enter some tasks on your to-do list.\n";
    cout << "There are four commands in total.\n";
    cout << "A task will be entered using \"+ \" and the task name, for example:\n\n";
    cout << "+ New task here\n\n";
    cout << "All tasks and task numbers will be displayed using \"?\", for example:\n\n";
    cout << "1 First task\n";
    cout << "2 Another task\n\n";
    cout << "A task will be removed using \"- \" and the task number, for example:\n\n";
    cout << "- 1\n\n";
    cout << "When you're finished, enter \"!\" to quit!\n\n";
}