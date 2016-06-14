#include "Student.h"

Student::Student(string & id, string & _firstName, string & _lastName, int _grade, string & _street, int _houseNo, string & _city, string & _zipCode, string & _phoneNo)
{
	strncpy_s(this->ID, 10, id.c_str(), 9);
	strncpy_s(this->firstName, 11, _firstName.c_str(), 10);
	strncpy_s(this->lastName, 10, _lastName.c_str(), 9);
	this->grade = _grade;
	strncpy_s(this->street, 12, _street.c_str(), 11);
	this->houseNo = _houseNo;
	strncpy_s(this->city, 12, _city.c_str(), 11);
	strncpy_s(this->zipCode, 8, _zipCode.c_str(), 7);
	strncpy_s(this->phoneNo, 11, _phoneNo.c_str(), 10);
}

ostream & operator<<(ostream & out, Student & stu)
{
	out << stu.ID << "\t" << stu.firstName << "\t" << stu.lastName << "\t" << stu.grade << "\t" << stu.street << "\t" << stu.houseNo << "\t" << stu.city << "\t" << stu.zipCode << "\t" << stu.phoneNo << endl;
	return out;
}
