// Student Grades.cpp : The structs version
// Put what the program does 

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_STUDENTS = 35;
const int MAX_SCORES = 5;
const string dataFile = "grades.txt";

struct studentInfo
{
	string name;
	double scores[MAX_SCORES];
	double average;
	char letterGrade;
};

//Reads data from the input file, expects the input file to be available. 
//Returns the actual number of records on the file.
//Places the data in predeclared storage in memory. 
//Only allows MAX_STUDENTS to be read from the file.  
int getStudentData(studentInfo students[], int maxRecords);

//Functions receives preloaded scores for each student, location for 
//calculated averages.
//Fills in the calculated averages for each student
void calcAverages(studentInfo students[], int numRec);

// Takes a score in the range of 0 - 100 and returns a letter grade (A, B, C, D, F)
char getLetterGrade(double score);

//Write formatted report displaying the name, average, letter grade for each student. 
//Report also calculate and displays the class average
void writeReport(studentInfo students[], int numRec);

int main()
{
	studentInfo students[MAX_STUDENTS];

	/*string studentNames[MAX_STUDENTS];
	double grades[MAX_STUDENTS][MAX_SCORES];
	char letterGrades[MAX_STUDENTS];
	double avgScore[MAX_STUDENTS];*/

	int numRecords;

	numRecords = getStudentData(students, MAX_STUDENTS);
	if (numRecords == -1)
	{
		cout << "Too many records on file" << endl;
		exit;
	}

	calcAverages(students, numRecords);

	writeReport(students, numRecords);
	
}

int getStudentData(studentInfo allStudents[], int maxRecords)
{
	ifstream inFile(dataFile);
	int rec = 0;

	if (!inFile)
	{
		cout << "Could not open " << dataFile << endl;
		exit;
	}

	//while (inFile >> names[rec])
	while (inFile >> allStudents[rec].name)
	{
		if (rec < MAX_STUDENTS)
		{
			for (int j = 0; j < MAX_SCORES; j++)
				inFile >> allStudents[rec].scores[j];
			rec++;
		}
		else
			return -1;
	}
		
	inFile.close();

	return rec;
			
}

void calcAverages(studentInfo students[], int numRec)
{
	double sum;
	for (int row = 0; row < numRec; row++)
	{
		sum = 0;
		for (int col = 0; col < MAX_SCORES; col++)
		{
			sum += students[row].scores[col];
		}
		students[row].average = sum / MAX_SCORES;
		students[row].letterGrade = getLetterGrade(students[row].average);
	}
}

char getLetterGrade(double score)
{
	if (score >= 90)
		return 'A';
	else if (score >= 80)
		return 'B';
	else if (score >= 70)
		return 'C';
	else if (score >= 60)
		return 'D';
	else
		return 'F';
}

void writeReport(studentInfo students[], int numRec)
{
	cout << fixed << setprecision(2) << showpoint;
	cout << "Class Report" << endl;
	cout << "Student     Average     Grade" << endl;
	double class_avg = 0;
	for (int row = 0; row < numRec; row++)
	{
		cout << setw(11) << left << students[row].name;
		cout << right <<  setw(7) << students[row].average << setw(7) << students[row].letterGrade << endl;
		class_avg += students[row].average;
	}
	cout << "Class average: " << class_avg / numRec << endl;
}

