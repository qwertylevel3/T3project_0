#include "Dungeon.h"
#include<sstream>


using namespace Field;

using namespace Field;

Dungeon::Dungeon()
{
	curFloor = 0;
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

Storey * Field::Dungeon::getStorey()
{
	return storeys[curFloor];
}

void Field::Dungeon::writeToFile()
{
	for (int i = 0; i < getFloorNum(); i++)
	{
		Storey* tempStorey = storeys[i];
		std::stringstream stream;
		stream << i;
		std::string f;
		stream >> f;
		tempStorey->writeToFile(f);
	}
}

void Field::Dungeon::changeFloor(int floor)
{
	if (floor >= 0 && floor < storeys.size())
	{
		curFloor = floor;
	}

}

void Field::Dungeon::nextFloor()
{
	if (curFloor < storeys.size() - 1)
	{
		curFloor++;
	}
}
