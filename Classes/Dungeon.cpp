#include "Dungeon.h"
#include<sstream>


using namespace Field;

using namespace Field;

Dungeon::Dungeon()
{
}


Dungeon::~Dungeon()
{
}

int Field::Dungeon::getFloorNum()
{
	return storeys.size();
}

void Field::Dungeon::addStorey(Storey * storey)
{
	storeys.push_back(storey);
}

Storey * Field::Dungeon::getStorey(int floor)
{
	return storeys[floor];
}

void Field::Dungeon::writeToFile()
{
	for (int i = 0; i < getFloorNum(); i++)
	{
		Storey* tempStorey = getStorey(i);
		std::stringstream stream;
		stream << i;
		std::string f;
		stream >> f;
		tempStorey->writeToFile(f);
	}
}
