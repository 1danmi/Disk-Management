#pragma once
#pragma warning (disable:4996)
#include <iostream>
using namespace std;
class RecEntry
{
public:
	int recNr;
	char key[12];
	RecEntry()
	{
		recNr = 0;
		strcpy(key, "");
	}
	RecEntry(int recNum, char* _key, int size)
	{
		recNr = recNum;
		strncpy_s(this->key, size, _key, size - 1);
	}
	friend ostream& operator<<(ostream& out, RecEntry& rec)
	{
		out << rec.recNr << "\t" << rec.key << "\t" << endl;
		return out;
	}
};
class RecInfo
{
public:
	RecEntry records[45];
	int size;
	RecInfo(){}
	int findRecordNr(string& _key)
	{
		for (int i = 0; i < size; i++)
			if (!strcmp(_key.c_str(), records[i].key))
				return records[i].recNr;
		return -1;
	}
	friend ostream& operator<<(ostream& out, RecInfo& recInfo)
	{
		for (int i = 0; i < recInfo.size; i++)
			out << recInfo.records[i];
		out << endl;
		return out;
	}
};
