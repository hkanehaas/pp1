#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
#include "GradeReport.h"

void GradeReport::PrintGradeReport(string filename) {
	
   inputStudentFS.open(filename);
	   if (!inputStudentFS.is_open()) {
		  cout << "Could not open file. Check file path and try again." << filename << endl;
		  //return 1; // 1 indicates error
	   }
	
	//check number of lines in the file
	numLines = GetNumLines(filename);
	
	if (numLines > 30) {
		cout << "ERROR, over 30 students in file" << filename << ". Only the first 30 lines will be processed" 
		   << endl;
		numLines = 30;
		   
		}
	studentVctr.resize(numLines);
	
	
	
	i = 0;	
	while (i < numLines) {
		SetStudents(i, filename);
		SetStudentAvgAndLetter(i);
		++i;
	}
	
   inputStudentFS.close(); // Done with file, so close it
   
   HighestClassGrades();
   TestAverages();
   
   outputGradeReportFS.open("GradeReport.txt");

   if (!outputGradeReportFS.is_open()) {
      cout << "Could not generate GradeReport.txt file." << endl;
      //return 1;
   }

   // Write to output grade report file
   
   outputGradeReportFS << fixed << setprecision(2) << showpoint; //Set all doubles to 2 decimal points
   
   outputGradeReportFS << "First\t";
   outputGradeReportFS << "Last\t";
   outputGradeReportFS << "T1\t";
   outputGradeReportFS << "T2\t";
   outputGradeReportFS << "T3\t";
   outputGradeReportFS << "T4\t";
   outputGradeReportFS << "Final\t";
   outputGradeReportFS << "Average\t";
   outputGradeReportFS << "Letter Grade\t";
   outputGradeReportFS << endl;
   
   for (i = 0; i < numLines; ++i) {
 
	   outputGradeReportFS << studentVctr.at(i).firstName << "\t";
	   outputGradeReportFS << studentVctr.at(i).lastName << "\t";
	   outputGradeReportFS << studentVctr.at(i).test1 << "\t";
	   outputGradeReportFS << studentVctr.at(i).test2 << "\t";
	   outputGradeReportFS << studentVctr.at(i).test3 << "\t";
	   outputGradeReportFS << studentVctr.at(i).test4 << "\t";
	   outputGradeReportFS << studentVctr.at(i).finalExam << "\t";
	   outputGradeReportFS << studentVctr.at(i).gradeAvg << "\t";
	   outputGradeReportFS << studentVctr.at(i).letterGrade << "\t";
	   outputGradeReportFS << endl;
   }
   
   outputGradeReportFS << "Average Test Grades:" << endl;
   outputGradeReportFS << "T1\tT2\tT3\tT4\tFinal\tOverall\tHighest Grade" << endl;
   outputGradeReportFS << avgTest1 << "\t";
   outputGradeReportFS << avgTest2 << "\t";
   outputGradeReportFS << avgTest3 << "\t";
   outputGradeReportFS << avgTest4 << "\t";
   outputGradeReportFS << avgFinalExam << "\t";
   outputGradeReportFS << avgAllGrades << "\t";
   outputGradeReportFS << highestOverallGrade << endl;
   
   
   
   outputGradeReportFS << "Student(s) with the highest class grade:" << endl;
   for (i = 0; i < numLines; ++i) {
		
		if (studentVctr.at(i).gradeAvg == bestStudent) {
			outputGradeReportFS << studentVctr.at(i).firstName << " " << studentVctr.at(i).lastName << endl;
		}
	}
   
   // Done with file, so close
   outputGradeReportFS.close();
   
   return;
}

int GradeReport::GetNumLines(string filename) { //CREDIT This function is from StackOverflow user: Abhay link: https://stackoverflow.com/questions/3072795/how-to-count-lines-of-a-file-in-c 

ifstream inFile(filename); 
	numLines = count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n') + 1;
	
	return numLines;
}

void GradeReport::SetStudents(int i, string filename) {	//Input data from a text file and save into Vector studentVctr.
		
	inputStudentFS >> stringHolder;
	studentVctr.at(i).firstName = stringHolder;
	
	inputStudentFS >> stringHolder;
	studentVctr.at(i).lastName = stringHolder;
	
	inputStudentFS >> doubleHolder;
	studentVctr.at(i).test1 = doubleHolder;
	
	inputStudentFS >> doubleHolder;
	studentVctr.at(i).test2 = doubleHolder;
	
	inputStudentFS >> doubleHolder;
	studentVctr.at(i).test3 = doubleHolder;
	
	inputStudentFS >> doubleHolder;
	studentVctr.at(i).test4 = doubleHolder;
	
	inputStudentFS >> doubleHolder;
	studentVctr.at(i).finalExam = doubleHolder;
	
	return;
}
void GradeReport::SetStudentAvgAndLetter(int i) { //Add students letter grade to vector list for each student.

	studentVctr.at(i).gradeAvg = (studentVctr.at(i).test1 + 
								  studentVctr.at(i).test2 +  
								  studentVctr.at(i).test3 +  
								  studentVctr.at(i).test4 +  
								  studentVctr.at(i).finalExam) / 5;

	if (studentVctr.at(i).gradeAvg >= 90) {studentVctr.at(i).letterGrade = 'A';}
	else if (studentVctr.at(i).gradeAvg >= 80) {studentVctr.at(i).letterGrade = 'B';}
	else if (studentVctr.at(i).gradeAvg >= 70) {studentVctr.at(i).letterGrade = 'C';}
	else if (studentVctr.at(i).gradeAvg >= 60) {studentVctr.at(i).letterGrade = 'D';}
	else  {studentVctr.at(i).letterGrade = 'F';}
	
	return;
}


void GradeReport::TestAverages() { //Calculate averages for 3 tests and 1 final and add them to apropriate variables.
	for (i = 0; i < numLines; ++i) {
		avgTest1 = studentVctr.at(i).test1 + avgTest1;
		avgTest2 = studentVctr.at(i).test2 +  avgTest2;
		avgTest3 = studentVctr.at(i).test3 +  avgTest3;
		avgTest4 = studentVctr.at(i).test4 + avgTest4;
		avgFinalExam = studentVctr.at(i).finalExam + avgFinalExam;	
	}	
	
	avgTest1 = avgTest1 / numLines;
	avgTest2 = avgTest2 / numLines;
	avgTest3 = avgTest3 / numLines;
	avgTest4 = avgTest4 / numLines;
	avgFinalExam = avgFinalExam / numLines;
	avgAllGrades = (avgTest1 + avgTest2 + avgTest3 + avgTest4 + avgFinalExam) / 5;
	
	return;
}

void GradeReport::HighestClassGrades() { //Run through vector and mark highest grade to apropriate variable.
	
	bestStudent = studentVctr.at(0).gradeAvg;
	highestOverallGrade = studentVctr.at(0).test1;
	for (i = 0; i < numLines; ++i) {
		
		if (studentVctr.at(i).gradeAvg > bestStudent) {
			bestStudent = studentVctr.at(i).gradeAvg;
		}
		
		if (highestOverallGrade < studentVctr.at(i).test1) {
			
			highestOverallGrade = studentVctr.at(i).test1;
		}
		
		if (highestOverallGrade < studentVctr.at(i).test2) {
			highestOverallGrade = studentVctr.at(i).test2;
		}
		
		if (highestOverallGrade < studentVctr.at(i).test3) {
			highestOverallGrade = studentVctr.at(i).test3;
		}
		
		if (highestOverallGrade < studentVctr.at(i).test4) {
			highestOverallGrade = studentVctr.at(i).test4;
		}
		
		if (highestOverallGrade < studentVctr.at(i).finalExam) {
			highestOverallGrade = studentVctr.at(i).finalExam;
		}		
	}
	
	return;
}


