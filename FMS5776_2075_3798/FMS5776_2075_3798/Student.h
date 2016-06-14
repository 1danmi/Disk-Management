#pragma once
#include <string>
using namespace std;

class Student
{
public:
	char ID[10];//key
	char firstName[11];
	char lastName[12];
	int grade;
	char street[12];
	int houseNo;
	char city[12];
	char zipCode[8];
	char phoneNo[11];
	Student() {};
	Student(string& ID, string& firstName, string& lastName, int grade, string& street, int houseNo, string& city, string& zipCode, string& phoneNo);
};
