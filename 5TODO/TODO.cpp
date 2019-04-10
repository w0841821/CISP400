// TODO.cpp
// Erroll Abrahamian, CISP 400
// 04-07-2019

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
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

  // Specification A2 - Copy Constructor
  Tasks(const Tasks &t) {
    taskNum = t.taskNum;
    taskName = t.taskName;
    taskDate = t.taskDate;
  }

  int getTaskNum() const {return taskNum;}
  string getTaskName() const {return taskName;}
  string getTaskDate() const {return taskDate;}
};

class ToDoList
{
private:
  vector<Tasks> taskVec;
  int taskNumMax;

public:
  string getDate();
  void sayHi();
  void openTasks();
  void saveTasks();
  void hitEnter();

  ToDoList operator+ (const string &str);
  ToDoList operator- (const string &str);
  friend ostream &operator << (ostream &out, const ToDoList &t);
};

// Specification A1 - Overload symbols
ToDoList ToDoList::operator+ (const string &str)
{
  Tasks tmp;

  tmp.taskNum = taskNumMax;
  tmp.taskName = str;
  tmp.taskDate = getDate();

  Tasks t = tmp;

  taskVec.push_back(t);
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
  // format width of number column to make output consistently aligned
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
  taskVec.openTasks();

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
      //  cout << "Looks like you don't have any tasks yet! Why don't you enter some?\n";
    }

    else if (taskCommand.compare(0, 1, "!") == 0) {
      cout << "All done entering tasks!\n";
    }

    // any other input
    else
      cout << "Not valid input.\n";
  }

  taskVec.saveTasks();

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
    hitEnter();
}

void ToDoList::openTasks()
{
  Tasks tempTask;
  ifstream taskFile;

  taskFile.open("task.txt");

  string catchString = "";
  if (!taskFile) {
    cout << "Looks like you don't have any saved tasks!\n\n";
    taskNumMax = 1;
  }
  else
  {
    while (!taskFile.eof()) {
      getline(taskFile, catchString, ',');

      if (!catchString.empty())
        tempTask.taskNum = stoi(catchString);
      else
        break;

      getline(taskFile, catchString, ',');
      tempTask.taskDate = catchString;
      getline(taskFile, catchString, ',');
      tempTask.taskName = catchString;

      taskVec.push_back(tempTask);
    }

  taskFile.close();

  taskNumMax = taskVec.back().taskNum + 1;
  }
}

//Specification B2 - Save to disk
void ToDoList::saveTasks()
{
  ofstream taskFile;

  if (taskVec.empty())
    return;
  else {
    taskFile.open("task.txt");
    for (size_t i = 0; i < taskVec.size(); i++) {
      taskFile << taskVec[i].taskNum << "," << taskVec[i].taskDate << "," << taskVec[i].taskName << ",";
    }
  }
}

void ToDoList::hitEnter()
{
  cout << "Press Enter to continue.\n";
  cin.ignore();
}
