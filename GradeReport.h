#ifndef GRADEREPORT_H
#define GRADEREPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class GradeReport {
	public:
		void PrintGradeReport(string filename = "noName");
	private:
		void SetStudents(int i, string filename);
		void SetStudentAvgAndLetter(int i);
		void CalculateAverage();
		void TestAverages();
		void HighestClassGrades();
		string studentLine;
		ifstream inputStudentFS;
		ofstream outputGradeReportFS;
		struct GradeReportInfo {
					string firstName;
					string lastName;
					double test1;
					double test2;
					double test3;
					double test4;
					double finalExam;
					double gradeAvg;
					char letterGrade;
				};
		vector<GradeReportInfo>  studentVctr;
		int i;
		int numLines;
		int GetNumLines(string filename);
		string stringHolder;
		double doubleHolder;
		double sumHolder;
		double bestStudent;
		double highestOverallGrade;
		double avgTest1 = 0;
		double avgTest2 = 0;
		double avgTest3 = 0;
		double avgTest4 = 0;
		double avgFinalExam = 0;
		double avgAllGrades = 0;
	
};

#endif