// CourseGradeProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/*const int MAX_STUDENTS = 100;
const int MAX_TEST_SCORES = 100;

string studentNames[MAX_STUDENTS];
double testScores[MAX_STUDENTS][MAX_TEST_SCORES];
double averages[MAX_STUDENTS];

int numStudents = 0;
int numTestScores = 0;
*/


struct student {
    string studentName;
    int studentID;
    double* testScores;
    double average;
    char letterGrade;
};

//Read the number of student records and tests from file.
student* getData(ifstream& file, int& studentCnt, int& testsCnt);

//Take test scores and calculate an average.
void calcAverage(student students[], int studentCnt, int testsCnt);
//Use assigned grading chart to assign letter grade.
char calculateLetterGrade(double average);
//Format a report.
void reportCard(student students[], int studentCnt);
//Deallocate memory
void cleanUp(student* students, int studentCnt);



int main() {
    ifstream inputFile("StudentGrades.txt");
    if (!inputFile) {
        cout << "Error opening file! Check path and file name." << endl;
        return 1;
    }
    int studentCnt, testsCnt;
    student* students = getData(inputFile, studentCnt, testsCnt);
    inputFile.close();

    calcAverage(students, studentCnt, testsCnt);
    reportCard(students, studentCnt);
    cleanUp(students, studentCnt);

    return 0;
}

/* Commenting out the block to test new functionality.
void readData(ifstream& inputFile) {
    numStudents = 0;
    string name;
    double score;

    while (inputFile >> name) {
        studentNames[numStudents] = name;
        int i = 0;

        // Read test scores until end of line or maximum test scores
        while (i < MAX_TEST_SCORES && inputFile >> score) {
            testScores[numStudents][i] = score;
            i++;
            if (inputFile.peek() == '\n' || inputFile.peek() == EOF) {
                break;
            }
        }

        // Base number of scores on the first student's scores
        if (numTestScores == 0) {
            numTestScores = i;
        }

        numStudents++;
    }
}*/



// Iterate through the array of students and the array of test scores, calculating averages per student.
void calcAverage(student students[], int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; ++i) {
        double total = 0;
        for (int j = 0; j < testsCnt; ++j) {
            total += students[i].testScores[j];
        }
        students[i].average = total / testsCnt;
        students[i].letterGrade = calculateLetterGrade(students[i].average);


    }
}

/*       if (numTestScores != 0) {
           averages[i] = total / numTestScores;
       }
       else {
           averages[i] = 0; // In case of division by zero
       }*/


char calculateLetterGrade(double average) {
    if (average >= 90) return 'A';
    else if (average >= 80) return 'B';
    else if (average >= 70) return 'C';
    else if (average >= 60) return 'D';
    else return 'F';
}


// Report formatting
void reportCard(student students[], int studentCnt) {
    cout << left << setw(20) << "Student Name"
        << setw(10) << "ID"
        << setw(10) << "Score"
        << setw(10) << "Grade" << endl;
    cout << "************************************************" << endl;
    // Loop through the studentNames array based on the numStudents value to output names, averages, and letter grade.
    for (int i = 0; i < studentCnt; ++i) {


        cout << left << setw(20) << students[i].studentName
            << setw(10) << students[i].studentID
            << setw(10) << fixed << setprecision(2) << students[i].average
            << setw(10) << students[i].letterGrade << endl;
    }
}


student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt;
    student* students = new student[studentCnt];

    for (int i = 0; i < studentCnt; ++i) {
        file >> students[i].studentName >> students[i].studentID;
        students[i].testScores = new double[testsCnt];
        for (int j = 0; j < testsCnt; ++j) {
            file >> students[i].testScores[j];
        }
    }

    return students;
}


void cleanUp(student* students, int studentCnt) {
    for (int i = 0; i < studentCnt; ++i) {
        delete[] students[i].testScores;

    }
    delete[] students;
}
