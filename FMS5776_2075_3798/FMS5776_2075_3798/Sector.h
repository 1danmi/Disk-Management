#pragma once

class Sector
{
public:
	Sector() {};
	Sector(unsigned int, char[1020]);
	~Sector() {};

private:
	unsigned int sectorNr;
	char rawData[1020];
}; 
