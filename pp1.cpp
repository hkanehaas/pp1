#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;	
#include "GradeReport.h"

int main() {
	//ifstream inputStudentFS;     // Input file stream
	GradeReport studentGrades;
	string filename;
	
	cout << "Enter File Name source for Student Grade Report:" << endl;
	cin >> filename;
	studentGrades.PrintGradeReport(filename);

   return 0;
}
