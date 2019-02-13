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

You will also need to prompt for the total points possible. Assume each test is worth 100 points.

Enter the Student ID first

then prompt for grades

Keep prompting for grades until the client enters ’calc’

That triggers final processing.

*/

// GPA.cpp
// Erroll Abrahamian, CISP 400
// 02-17-2019

#include <iostream>
using namespace std;

class GPA
{
private:
	int** gpaArray = nullptr;
	int totalPoints, scores, rows, cols, stuID, students = 1;
	char moreStudents;

public:
	void sayHi();
	void getTotal();
	void buildArray();
	void ask();
	bool checkID();
	void incArray();
	void printArray();
};

int main()
{
	GPA gpaArr;
	gpaArr.sayHi();
	gpaArr.getTotal();
	gpaArr.buildArray();
	gpaArr.ask();
	gpaArr.printArray();

	return 0;
}

void GPA::sayHi()
{
	cout << "At any point during the grade-recording process, you may enter 'calc' to begin\ngrade calculation.\n";
	cout << "Caution: if 'calc' is entered before the current student's grades are entered,\nthey will be assigned a 0 for all remaining tests!\n\n";
}

void GPA::getTotal()
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

	scores = totalPoints / 100;

	cout << "\nWith " << totalPoints << " total points for the class, and each test worth 100 points, we will entering " << scores << " test scores.\n\n";
}

void GPA::buildArray()
{
	/*
	Array is built in the form of...

							col0				col1				col2		-->
	row0  |  Student1  |	score1  | 	score2	etc
	row1  |  Student2  |	score1  | 	score2
	row2  |  Student3  |	score1  | 	score2
	 \/			etc

	Number of rows is always equal to number of students.
	First column is student ID, followed by the number of tests.
	*/

	rows = students;
	cols = scores + 1;
	gpaArray = new int* [rows];
	for (int i = 0; i < rows; i++)
		gpaArray[i] = new int [cols];
}

void GPA::ask()
{
	do {
		bool valid;

		cout << "Please enter Student ID #" << students << ": ";

		// check for a valid student ID
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
		// first student is row 0, second is row 1 etc, so "students - 1"
		gpaArray[(students - 1)][0] = stuID;

		for (int i = 1; i < cols; i++)
		{
			cout << "Score #" << i << ": ";
			cin >> gpaArray[(students - 1)][i];
		}

		cout << "Would you like to enter another student? ('y' or any other key to decline)";
		cin >> moreStudents;

		// increment the array if we want to enter another student
		if (toupper(moreStudents == 'Y'))
			incArray();
	} while (toupper(moreStudents == 'Y'));
}

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

void GPA::incArray()
{
	// one extra student...otherwise why are we incrementing an array?!
	students++;

	// create temp array for copying purposes
	int** tempCopy = nullptr;
	tempCopy = new int* [students];

	// larger array needs student count for rows
	for (int i = 0; i < students; i++)
		tempCopy[i] = new int [cols];

	// original, smaller array has one less row
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			tempCopy[i][j] = gpaArray[i][j];

	// delete those arrays!
	for (int i = 0; i < rows; i++)
		delete [] gpaArray[i];
	delete [] gpaArray;

	// number of rows can now be set to number of students
	rows = students;

	// array cleanup
	gpaArray = tempCopy;
	tempCopy = nullptr;
}

void GPA::printArray()
{
	for (int i = 0; i < students; i++)
	{
		cout << "\nStudent: " << gpaArray[i][0] << endl;
		for (int j = 1; j <= scores; j++)
			cout << "Score #" << j << ": " << gpaArray[i][j] << endl;
	}
}
