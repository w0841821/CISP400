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

You will also need to prompt for the total points possible. Assume each test is worth 100 points.

Enter the Student ID first

then prompt for grades

Keep prompting for grades until the client enters ’calc’

That triggers final processing.

*/

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

	*/
	rows = students;
	cols = scores + 1; // first column is student ID, followed by the number of tests
	gpaArray = new int* [rows];
	for (int i = 0; i < rows; i++)
		gpaArray[i] = new int [cols];
}

void GPA::ask()
{
	do {
		cout << "\nStudent ID: ";
		cin >> stuID;
		gpaArray[(students - 1)][0] = stuID;

		for (int i = 1; i < cols; i++)
		{
			cout << "Score #" << i << ": ";
			cin >> gpaArray[(students - 1)][i];
		}

		cout << "Another student? ";
		cin >> moreStudents;
		if (moreStudents == 'y')
			incArray();
	} while (moreStudents == 'y');
}

void GPA::incArray()
{
	students++;
	int** tempCopy = nullptr;

	tempCopy = new int* [students];

	for (int i = 0; i < students; i++)
		tempCopy[i] = new int [cols];

	for (int i = 0; i < rows; i++)
	{
		cout << "Checking for success" << endl;
		for (int j = 0; j < cols; j++)
			tempCopy[i][j] = gpaArray[i][j];
	}

	for (int i = 0; i < rows; i++)
		delete [] gpaArray[i];
	delete [] gpaArray;

	rows = students;
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
