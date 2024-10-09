// Student Grades.cpp : The parallel arrays version
// Put what the program does 

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_STUDENTS = 35;
const int MAX_SCORES = 5;
const string dataFile = "grades.txt";

//Reads data from the input file, expects the input file to be available. 
//Returns the actual number of records on the file.
//Places the data in predeclared storage in memory. 
//Only allows MAX_STUDENTS to be read from the file.  
int getStudentData(string names[], double grades[][MAX_SCORES], int maxRecords);

//Functions receives preloaded scores for each student, location for 
//calculated averages.
//Fills in the calculated averages for each student
void calcAverages(const double scores[][MAX_SCORES], double averages[], int numRec);

// Takes a score in the range of 0 - 100 and returns a letter grade (A, B, C, D, F)
char getLetterGrade(double score);

//Write formatted report displaying the name, average, letter grade for each student. 
//Report also calculate and displays the class average
void writeReport(string names[], double averages[], int numRec);

int main()
{
	string studentNames[MAX_STUDENTS];
	double grades[MAX_STUDENTS][MAX_SCORES];
	char letterGrades[MAX_STUDENTS];
	double avgScore[MAX_STUDENTS];

	int numRecords;

	numRecords = getStudentData(studentNames, grades, MAX_STUDENTS);
	if (numRecords == -1)
	{
		cout << "Too many records on file" << endl;
		exit;
	}

	calcAverages(grades, avgScore, numRecords);

	writeReport(studentNames, avgScore, numRecords);
	
}

int getStudentData(string names[], double grades[][MAX_SCORES], int maxRecords)
{
	ifstream inFile(dataFile);
	int rec = 0;

	if (!inFile)
	{
		cout << "Could not open " << dataFile << endl;
		exit;
	}

	while (inFile >> names[rec])
	{
		if (rec < MAX_STUDENTS)
		{
			for (int j = 0; j < MAX_SCORES; j++)
				inFile >> grades[rec][j];
			rec++;
		}
		else
			return -1;
	}
		
	inFile.close();

	return rec;
			
}

void calcAverages(const double scores[][MAX_SCORES], double averages[], int numRec)
{
	double sum;
	for (int row = 0; row < numRec; row++)
	{
		sum = 0;
		for (int col = 0; col < MAX_SCORES; col++)
		{
			sum += scores[row][col];
		}
		averages[row] = sum / MAX_SCORES;
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

void writeReport(string studentNames[], double avgScore[], int numRec)
{
	cout << fixed << setprecision(2) << showpoint;
	cout << "Class Report" << endl;
	cout << "Student     Average     Grade" << endl;
	double class_avg = 0;
	for (int row = 0; row < numRec; row++)
	{
		cout << setw(11) << left << studentNames[row];
		cout << right <<  setw(7) << avgScore[row] << setw(7) << getLetterGrade(avgScore[row]) << endl;
		class_avg += avgScore[row];
	}
	cout << "Class average: " << class_avg / numRec << endl;
}

