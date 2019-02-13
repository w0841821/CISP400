#include <iostream>
using namespace std;

/*

// Specification C1 - Pseudo Dynamic Array
Create a fixed sized array in the heap. In this case, unlimited number of scores means 100.

// Specification C2 - Print Scores
After all the grades have been entered again, print them all to screen.

// Specification C3 - Compute GPA
Compute the average grade for the client and display it.

// Specification C4 - Validate Test Scores
Determine if each score is within the range of 0 - 100. Reprompt if that’s not the case.

// Specification C5 - Print Letter Grade
Print the letter grade for the overall gpa right next to it raw number.

// Specification B1 - Dynamic Array
Create an array on the heap. Increase it automatically for every score the client adds. That is, this array should be as small as possible - always. This replaces specification C1. Put this comment either above or below C1 and change C1 to this: // Specification C1 - REPLACED

//Specification B2 - Validate Student ID
Only allow entry of a valid Student ID. See figure 1 for the criteria for a valid student ID. Quit if the Student ID is invalid.

Student ID Business Logic.
1. The Student ID must have 8 digits.
2. The last digit must be even.
3. The first 3 digits must be one of the
following major codes: 127, 379, or
833. That is, the ID must start with
one of these three numbers.
Figure 1: Business logic to validate
Student ID.

// Specification B3 - Letter Grades
Include the letter grades for each individual test score you printed out under Specification C2.

// Specification A1 - OOP
Code this assignment using at least one class. Put this comment
above the class declaration.

// Specification A2 - Sort Grades
Sort the grades before printing them under specification C2. High
to low. Use any sort you wish, but code your own sort.

// Specification A3 - Logfile
Log the grades to a text file for archival purposes.
*/


/*
Create a program which will accept an unlimited number of scores and calculates the average score.

You will also need to prompt for the total points possible. Assume each test is worth 100 points.

Enter the Student ID first

then prompt for grades

Keep prompting for grades until the client enters ’calc’

That triggers final processing.

*/

class Grades
{
private:
	int* scoreArr = nullptr;
	int numStudents,
		totalPoints,
		totalScores,
		totalRows;
public:
	void newScoreArr();
	void incScoreArr();
	void sayHi();
	void getTotal();
	void addScores();
	void getID();
	void getScores();
};

int main() {
	Grades hw2;
	hw2.newScoreArr();
	hw2.sayHi();
	hw2.getTotal();

	char done;
	do {
		do {
			hw2.getID();
			hw2.getScores();
			cout << "Done? ";
			cin >> done;
		} while(done != 'y');
		hw2.incScoreArr();
	} while(done != 'y');


}

void Grades::newScoreArr()
{
	// initialize array and counter for 1 student
	scoreArr = new int [1][];
	numStudents = 1;
}

void Grades::incScoreArr()
{
	numStudents++;
	int** tmpSize = nullptr;
	tmpSize = new int* [totalRows];

	for (int i = 0; i < totalRows; i++)
		tmpSize[i] = new int[numStudents];

	for (int i = 0; i < (numStudents - 1); i++)
		for (int j = 0; j < totalRows; j++)
			tmpSize[j][i] = scoreArr[j][i];

	/*
	int** tmpSize = new int* [totalRows];
	for (int i = 0; i < totalRows; i++)
		tmpSize[i] = new int[numStudents];
		*/

	// copy original array to temp/incremented array

	// delete temp array
	delete [] scoreArr;

	scoreArr = tmpSize;
	tmpSize = nullptr;
}

void Grades::sayHi()
{
	cout << "At any point during the grade-recording process, you may enter 'calc' to begin\ngrade calculation.\n";
	cout << "Caution: if 'calc' is entered before the current student's grades are entered,\nthey will be assigned a 0 for all remaining tests!\n\n";
}

void Grades::getTotal()
{
	cout << "What is the total amount of points for the class?\n";
	do {
		cin >> totalPoints;
		if ((totalPoints % 100) != 0)
		{
			cout << "\nAs each test is worth 100 points, there should be a multiple of 100 for the total amount of points.\n";
			cout << "What is the total amount?\n";
		}
	} while((totalPoints % 100) != 0);

	totalScores = totalPoints / 100;
	totalRows = totalScores + 1;

	cout << "\nWith " << totalPoints << " total points for the class, and each test worth 100 points, we will entering " << totalScores << " test scores.\n\n";
}

void Grades::addScores()
{
	int* tmpSize = nullptr;
	tmpSize = new int[totalRows];
	delete [] scoreArr;
	scoreArr = tmpSize;
	tmpSize = nullptr;
}

void Grades::getID()
{
	cout << "Enter student ID: ";
	cin >> scoreArr[0];
	cout << "Student 0: " << scoreArr[0] << endl;
}

void Grades::getScores()
{
	for (int i = 1; i < totalRows; i++)
	{
		cout << "Test score #" << i << ": ";
		cin >> scoreArr[i];
	}

	cout << "Student ID\n";

	for (int i = 0; i < totalRows; i++)
		cout << scoreArr[i] << "\t";
}
