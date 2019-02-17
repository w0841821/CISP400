// GPA.cpp
// Erroll Abrahamian, CISP 400
// 02-17-2019

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Specification A1 - OOP
class GPA
{
private:
  int* gpaArray = nullptr;
	int* scoreArray = nullptr;
  int strToInt, numScores, stuID, convInt;
	string scoreEntry;
  bool calcTime = false;
public:
  // function prototypes
  void sayHi();
  void buildArray();
	void incArray();
	void getID();
  bool checkID();
	void getScores();
	void sortScores();
  void convertString();
  char letterGrade(int);
  int computeGPA(int);
  void printArray();
};

int main()
{
  GPA gpaArr;
  gpaArr.sayHi();
  gpaArr.buildArray();
	gpaArr.getID();
  gpaArr.getScores();
  gpaArr.sortScores();
  gpaArr.printArray();
  return 0;
}

void GPA::sayHi()
{
  cout << "Hello! Are you ready to enter some scores and get some grades?\nI know you are...so let's do it!\n\n";
	cout << "At any point during the grade-recording process, you may enter 'calc' to begin\ngrade calculation.\n\n";
}

void GPA::buildArray()
{
	numScores = 0;

	// Specification C1 - REPLACED
	// Specification B1 - Dynamic Array
  gpaArray = new int[1];
	scoreArray = new int[1];
}

void GPA::incArray()
{
  numScores++;

  int* tmpGPA = nullptr;
	int* tmpScore = nullptr;

  tmpGPA = new int[numScores];
	tmpScore = new int[numScores];

  for (int i = 0; i < (numScores - 1); i++)
		tmpGPA[i] = gpaArray[i];

	delete [] gpaArray;
	delete [] scoreArray;

	gpaArray = tmpGPA;
	scoreArray = tmpScore;

	tmpGPA = nullptr;
	tmpScore = nullptr;
}

void GPA::getID()
{
	bool valid;

  cout << "Please enter the Student ID: ";

  // loop until a valid student ID is entered
  do {
			cin >> stuID;

			// plenty of things to check for...
			valid = checkID();

      if (!valid)
			{
				cout << "Student IDs must be 8 digits, even, and start with 127, 379, or 833.\n";
				cout << "What is the Student ID? ";
			}
		} while(!valid);
}

//Specification B2 - Validate Student ID
bool GPA::checkID()
{
	// is the Student ID even?...
	if ((stuID % 2) != 0)
		return false;

	// ...what about in range?
	else if ((stuID < 12700000) || (stuID >= 12800000 && stuID <= 37899999) || (stuID >= 38000000 && stuID <= 83299999) || (stuID >= 83400000))
		return false;

	// must be good then!
	else
		return true;
}

void GPA::getScores()
{
  do {
		cout << "Score #" << (numScores + 1) << ": ";
		cin >> scoreEntry;

    // check if it's time to calculate...
		if (scoreEntry == "calc")
		{
			calcTime = true;
			break;
		}

    // ...otherwise, convert to an int for gradekeeping
    convertString();

		// Specification C4 - Validate Test Scores
		if (convInt >= 0 && convInt <= 100)
		{
			incArray();

      // store the converted int as the grade element
			gpaArray[numScores - 1] = convInt;
		}
		else
			cout << "Not a valid score entry. Let's stick to 0-100 :)\n";

	} while(!calcTime);

  // populate the score number elements after we know how many scores were entered
  for (int i = 0; i < numScores; i++)
		scoreArray[i] = i + 1;
}

// Specification A2 - Sort Grades
void GPA::sortScores()
{
	bool swapped;
	int tmpSwap;

  // bubble sort goodness
	for (int i = 0; i < numScores; i++)
	{
		swapped = false;
		for (int j = 0; j < (numScores - 1); j++)
		{
			if (gpaArray[j] < gpaArray[j + 1])
			{
        // swap the grade/score array elements
				tmpSwap = gpaArray[j];
				gpaArray[j] = gpaArray[j + 1];
				gpaArray[j + 1] = tmpSwap;

        // swap the score number elements
        tmpSwap = scoreArray[j];
				scoreArray[j] = scoreArray[j + 1];
				scoreArray[j + 1] = tmpSwap;

				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void GPA::convertString()
{
  int count = 1;
	convInt = 0;

  // fun math to convert a string entry to an int
	int strLength = scoreEntry.length();
	for (int i = (strLength - 1); i >= 0; i--)
	{
		convInt += ((scoreEntry[i] - 48) * count);
		count *= 10;
	}
}

char GPA::letterGrade(int grade)
{
  if (grade >= 90)
    return 'A';
  else if (grade >= 80)
    return 'B';
  else if (grade >= 70)
    return 'C';
  else if (grade >= 60)
    return 'D';
  else
    return 'F';
}

int GPA::computeGPA(int grade)
{
  if (grade >= 90)
    return 4;
  else if (grade >= 80)
    return 3;
  else if (grade >= 70)
    return 2;
  else if (grade >= 60)
    return 1;
  else
    return 0;
}

// Specification C2 - Print Scores
void GPA::printArray()
{
  // ltrGr will be returned from letterGrade() to convert a number to letter grade (Spec B3 below)
  char ltrGr;
  int totalPoints = 0;

	// Specification A3 - Logfile
	ofstream scoresFile;
	scoresFile.open("scores.txt", ios::app);

  cout << "\nScores for Student ID: " << stuID << endl;
	scoresFile << "\n\nScores for Student ID: " << stuID << endl;

	for (int i = 0; i < numScores; i++)
	{
    // Specification B3 - Letter Grades
    ltrGr = letterGrade(gpaArray[i]);
		cout << "#" << right << setw(3) << scoreArray[i] << ": " << right << setw(3) << gpaArray[i] << " (" << ltrGr << ")";
		scoresFile << "#" << right << setw(3) << scoreArray[i] << ": " << right << setw(3) << gpaArray[i];

    // enter a line break after every three scores for readability
    if ((i + 1) % 3 == 0)
		{
			cout << endl;
			scoresFile << endl;
		}

    // if we aren't line breaking, then put some space between the scores
		else if (i != (numScores - 1))
		{
			cout << "        ";
			scoresFile << "        ";
		}

    // keep track of the total points as we loop thru the array
    totalPoints += gpaArray[i];
	}

  // Specification C3 - Compute GPA
  // Specification C5 - Print Letter Grade
  cout << "\nOverall grade: " << (totalPoints / numScores) << endl;
  scoresFile << "\nOverall grade: " << (totalPoints / numScores) << endl;

  cout << " Letter grade: " << letterGrade(totalPoints / numScores) << endl;
  scoresFile << " Letter grade: " << letterGrade(totalPoints / numScores) << endl;

  cout << "          GPA: " << computeGPA(totalPoints / numScores)<< endl;
  scoresFile << "          GPA: " << computeGPA(totalPoints / numScores)<< endl;

	scoresFile.close();
}
