#pragma once
#pragma warning (disable:4996)
#include <iostream>
using namespace std;
class RecEntry
{
public:
	int recNr;
	char type[2];
	int size;
	char* key;
	RecEntry()
	{
		recNr = 0;
		strcpy(type, "");
		size = 0;
		key = nullptr;
	}
	RecEntry(int recNum, char* _key, int size)
	{
		recNr = recNum;
		this->key = new char[size];
		strncpy_s(this->key, size, _key, size - 1);
		this->size = size;
	}
	~RecEntry()
	{
		delete key;
	}
	/*bool operator=(RecEntry& rec)
	{
		try
		{
			this->recNr = rec.recNr;
			this->size = rec.size;
			strncpy_s(this->type, 2, rec.type, 1);
			strncpy_s(this->key, this->size, rec.key, this->size - 1);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}*/
	friend ostream& operator<<(ostream& out, RecEntry& rec)
	{
		out << rec.recNr << "\t" << rec.key << "\t" << rec.type << "\t" << rec.size << endl;
		return out;
	}
};
class RecInfo
{
public:
	RecEntry records[46];
	int size;
	RecInfo(){}
	/*bool operator=(RecInfo& rec)
	{
		try
		{
			this->size = rec.size;
			for (int i = 0; i < 46; i++)
				records[i] = rec.records[i];
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
*/
	int findRecordNr(char* _key)
	{
		for (int i = 0; i < size; i++)
			if (!strcmp(_key, records[i].key))
				return i;
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
