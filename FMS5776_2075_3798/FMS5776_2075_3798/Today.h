//#pragma warning (disable:4996)
//#include <ctime>
//#include <iostream>
//#define _CRT_NONSTDC_NO_WARNINGS
//using namespace std;
//
//string today(void)
//{
//	// current date/time based on current system
//	time_t now = time(0);
//	char date[20], temp[5];
//	string d;
//
//	// convert now to string form
//	tm ltm;
//	localtime_s(&ltm, &now);
//	itoa(ltm.tm_mday, date, 10);
//	strcat_s(date, "/");
//	itoa(ltm.tm_mon + 1, temp, 10);
//	strcat_s(date, temp);
//	strcat_s(date, "/");
//	itoa(ltm.tm_year + 1900, temp, 10);
//	strcat_s(date, temp);
//	d.assign(date);
//	return d;
//}
