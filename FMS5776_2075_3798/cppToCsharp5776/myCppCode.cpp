#include <iostream>
#include <fstream>
#include <list>
using namespace std;


struct ComplexNumber
{
	int a;
	int b;
};

struct StringArray
{
public:
	int size;
	char** arr;
};


extern "C"
{
	__declspec(dllexport) int __stdcall sum(int x, int y)
	{
		return x + y;
	}

	__declspec(dllexport) void __stdcall swap(int &x, int &y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	__declspec(dllexport) void __stdcall swap2(int * x, int * y)
	{
		int temp = *x;
		*x = *y;
		*y = temp;
	}

	__declspec(dllexport) int __stdcall strLength(char* str)
	{
		int i = 0;
		while (str[i] != NULL)
			i++;
		return i;
	}

	__declspec(dllexport) void __stdcall changeString(char*& str)
	{
		int i = 0;
		while (str[i] != NULL)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] + 'A' - 'a';
			i++;
		}
	}

	__declspec(dllexport) char* __stdcall getChangeString(char*& str)
	{
		int i = 0;
		while (str[i] != NULL)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] + 'A' - 'a';
			i++;
		}
		return str;
	}

	//__declspec(dllexport) char* __stdcall getString()
	//{
	//	char* str = "abcd";	
	//	return str;
	//}

	//char str[] = "abcd";
	//__declspec(dllexport) char* __stdcall getString()
	//{
	//	return str;
	//}

	string str = "abcde";
	__declspec(dllexport) const char* __stdcall getString()
	{
		const char* result = str.c_str();
		return result;
	}

	char* dynamicArr;
	__declspec(dllexport) void __stdcall deleteDynamicArray()
	{
		if (dynamicArr != NULL)
			delete[] dynamicArr;
		dynamicArr = NULL;
	}
	__declspec(dllexport) char* __stdcall getDynamicArray(int x)
	{
		deleteDynamicArray();
		dynamicArr = new char[x + 1]; // +1 to '\0'
		for (int i = 0; i<x; i++)
			dynamicArr[i] = i + 'a';

		dynamicArr[x] = '\0';
		return dynamicArr;
	}

	__declspec(dllexport) void __stdcall deleteDynamicArray_v2(char*& arr)
	{
		if (arr != NULL)
			delete[] arr;
		arr = NULL;
	}

	__declspec(dllexport) char* __stdcall getDynamicArray_v2(char*& arr, int x)
	{
		deleteDynamicArray_v2(arr);
		arr = new char[x + 1]; // +1 to '\0'
		for (int i = 0; i<x; i++)
			arr[i] = i + 'a';

		arr[x] = '\0';
		return arr;
	}

	string exceptionInfo;
	__declspec(dllexport) void __stdcall getException()
	{
		try
		{
			throw exception("my exception");
		}
		catch (exception ex)
		{
			exceptionInfo = ex.what();
			throw ex;
		}
	}
	__declspec(dllexport) const char* __stdcall getExceptionInfo()
	{
		return exceptionInfo.c_str();
	}


	__declspec(dllexport) ComplexNumber __stdcall sumComplex(ComplexNumber x, ComplexNumber y)
	{
		ComplexNumber c;
		c.a = x.a + y.a;
		c.b = x.b + y.b;
		return c;
	}

	__declspec(dllexport) int __stdcall getBigNumber(int* arr, int size)
	{
		int max = arr[0];

		for (int i = 0; i<size; i++)
			if (arr[i] > max)
				max = arr[i];

		return max;
	}

	__declspec(dllexport) char* __stdcall getBigWordLength(char** arr, int size)
	{
		char* bigWordLength = "";

		for (int i = 0; i<size; i++)
			if (strLength(bigWordLength) < strLength(arr[i]))
				bigWordLength = arr[i];

		return bigWordLength;
	}
	/*__declspec(dllexport) char** __stdcall getStringArray()
	{
	char* arr[4];
	arr[0] = "ezra";
	arr[1] = "oshri";
	arr[2] = "abcd";
	arr[3] = "ABCDEFGHI";

	return arr;
	}*/


	StringArray stringArrayResult;
	list<string> myList;
	__declspec(dllexport) void __stdcall deleteStringArray_v2()
	{
		if (stringArrayResult.arr != NULL)
			delete[] stringArrayResult.arr;
	}
	__declspec(dllexport) StringArray __stdcall getStringArray_v2()
	{
		myList.push_back("abc");
		myList.push_back("efg");

		stringArrayResult.size = myList.size();
		deleteStringArray_v2();
		stringArrayResult.arr = new char*[stringArrayResult.size];

		list<string>::iterator it;
		int i = 0;
		for (it = myList.begin(); it != myList.end(); it++)
			stringArrayResult.arr[i++] = (char*)(*it).c_str();

		return stringArrayResult;
	}

	__declspec(dllexport) char* __stdcall getBigWordLength_v2(StringArray stringarray)
	{
		char* bigWordLength = "";

		int arr_length = stringarray.size;
		for (int i = 0; i<arr_length; i++)
			if (strLength(bigWordLength) < strLength(stringarray.arr[i]))
				bigWordLength = stringarray.arr[i];

		return bigWordLength;
	}

	__declspec(dllexport) void __stdcall writeBuffer(char* fileName, int start, int size, char* buffer)
	{
		fstream f;
		f.open(fileName, ios::binary | ios::out | ios::in);
		f.seekp(start);
		f.write(buffer, size);
		f.close();
	}

	__declspec(dllexport) void __stdcall readBuffer(char* fileName, int start, int size, char* buffer)
	{
		fstream f;
		f.open(fileName, ios::binary | ios::in);
		f.seekg(start);
		f.read(buffer, size);
		f.close();
	}
}