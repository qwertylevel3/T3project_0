#include "Dungeon.h"


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
