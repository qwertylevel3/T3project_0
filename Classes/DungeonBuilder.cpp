#include<sstream>
#include<tinyxml2\tinyxml2.h>
#include "DungeonBuilder.h"
#include"StoreyBuilder.h"
#include<sstream>
#include"RandomNumber.h"
#include"Debug.h"
using namespace Field;

DungeonBuilder::DungeonBuilder()
{
	dungeon = NULL;
}

void DungeonBuilder::init()
{
}

Dungeon * Field::DungeonBuilder::generate(int floorNum)
{
	if (dungeon)
	{
		delete dungeon;
	}
	dungeon = new Dungeon();

	for (int i = 0; i < floorNum; i++)
	{
		//RandomNumber::instance()->setSeed(i+100);
		if (i == 2)
		{
			Debug::instance()->setDebugFlag(true);
		}
		Storey* tempStorey=StoreyBuilder::instance()->generate();
		dungeon->addStorey(tempStorey);
	}
	return dungeon;
}

void DungeonBuilder::writeToFile()
{
	for (int i = 0; i < dungeon->getFloorNum(); i++)
	{
		Storey* tempStorey=dungeon->getStorey(i);
		std::stringstream stream;
		stream << i;
		std::string f;
		stream >> f;
		tempStorey->writeToFile(f);
	}
}
