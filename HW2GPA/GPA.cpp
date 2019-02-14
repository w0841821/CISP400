/*

// Specification C3 - Compute GPA
Compute the average grade for the client and display it.

// Specification C5 - Print Letter Grade
Print the letter grade for the overall gpa right next to it raw number.

// Specification B3 - Letter Grades
Include the letter grades for each individual test score you printed out under Specification C2.

*/

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
  void sayHi();
  void buildArray();
	void incArray();
	void getID();
  bool checkID();
	void getScores();
	void sortScores();
  void convertString();
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
	cout << "At any point during the grade-recording process, you may enter 'calc' to begin\ngrade calculation.\n";
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
		if (scoreEntry == "calc")
		{
			calcTime = true;
			break;
		}

		convertString();

		// Specification C4 - Validate Test Scores
		if (convInt >= 0 && convInt <= 100)
		{
			incArray();
			gpaArray[numScores - 1] = convInt;
		}
		else
			cout << "Not a valid score entry.\n";

	} while(!calcTime);

	for (int i = 0; i < numScores; i++)
		scoreArray[i] = i + 1;
}

// Specification A2 - Sort Grades
void GPA::sortScores()
{
	bool swapped;
	int tmpSwap;

	for (int i = 0; i < numScores; i++)
	{
		swapped = false;
		for (int j = 0; j < (numScores - 1); j++)
		{
			if (gpaArray[j] < gpaArray[j + 1])
			{
				tmpSwap = gpaArray[j];
				gpaArray[j] = gpaArray[j + 1];
				gpaArray[j + 1] = tmpSwap;

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

	int strLength = scoreEntry.length();
	for (int i = (strLength - 1); i >= 0; i--)
	{
		convInt += ((scoreEntry[i] - 48) * count);
		count *= 10;
	}
}

// Specification C2 - Print Scores
void GPA::printArray()
{
	// Specification A3 - Logfile
	ofstream scoresFile;
	scoresFile.open("scores.txt", ios::app);
  cout << "\nScores for Student ID: " << stuID << endl;
	scoresFile << "\n\nScores for Student ID: " << stuID << endl;
	for (int i = 0; i < numScores; i++)
	{
		cout << "#" << right << setw(3) << scoreArray[i] << ": " << right << setw(3) << gpaArray[i];
		scoresFile << "#" << right << setw(3) << scoreArray[i] << ": " << right << setw(3) << gpaArray[i];
		if ((i + 1) % 5 == 0)
		{
			cout << endl;
			scoresFile << endl;
		}
		else if (i != (numScores - 1))
		{
			cout << "     ";
			scoresFile << "     ";
		}
	}
	scoresFile.close();
}
