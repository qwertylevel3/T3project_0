#include "StoreyBuilder.h"
#include"FieldEnum.h"
#include"RandomNumber.h"
#include"cocos2d.h"
#include"Debug.h"
#include"MonsterFactory.h"

using namespace Field;
USING_NS_CC;

StoreyBuilder::StoreyBuilder()
{
	storey = NULL;
}


StoreyBuilder::~StoreyBuilder()
{
}

void StoreyBuilder::init()
{
}

Storey* StoreyBuilder::generate()
{
	rooms.clear();
	exits.clear();
	storey = new Storey(100,100);

	int maxFeatures=33;
	// place the first room in the center
	if (!makeRoom(storey->getWidth() / 2, storey->getHeight() / 2, static_cast<Direction>(RandomNumber::getInstance()->randomInt(4), true)))
	{
		CCAssert(false, "Unable to place the first room\n");
	}
	if (!placeObject(UpStair))
	{
		CCAssert(false, "Unable to place up staris\n");
	}
	
	if (Debug::getInstance()->getDebugFlag())
	{
		storey->writeToFile("firstRoom");
	}


	// we already placed 1 feature (the first room)
	for (int i = 1; i < maxFeatures; ++i)
	{
		if (!createFeature())
		{
			CCAssert(false, "Unable to place more features\n");
		}
		if (Debug::getInstance()->getDebugFlag())
		{
			storey->writeToFile("temp");
		}

	}

	

	if (!placeObject(DownStair))
	{
		CCAssert(false, "Unable to place down stairs\n");
	}
//  //起点到终点的路径
//	std::vector<cocos2d::Point> path = ToolFunction::findPath(storey, storey->getUpCoord(), storey->getDownCoord());
//	for (int i = 0; i < path.size(); i++)
//	{
//		Character* monster = MonsterManager::getInstance()->getMonster("testMonster");
//		CCAssert(monster, "get a null monster");
//		storey->setCharacter(path[i].x, path[i].y, monster);
//	}
	return storey;
}


bool StoreyBuilder::createFeature()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (exits.empty())
			break;

		//从当前所有的可能出口矩形中随机选一个，再在这个矩形中选一个随机的xy坐标
		int r =RandomNumber::getInstance()->randomInt(exits.size());
		int x =RandomNumber::getInstance()->randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
		int y =RandomNumber::getInstance()->randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

		//用这个xy坐标和4个可能方向生成
		for (int j = 0; j < DirectionCount; ++j)
		{
			if (createFeature(x, y, static_cast<Direction>(j)))
			{
				exits.erase(exits.begin() + r);
				return true;
			}
		}
	}

	return false;
}

bool StoreyBuilder::createFeature(int x, int y, Direction dir)
{
	static const int roomChance = 33; // corridorChance = 100 - roomChance

	int dx = 0;
	int dy = 0;

	if (dir == North)
		dy = 1;
	else if (dir == South)
		dy = -1;
	else if (dir == West)
		dx = 1;
	else if (dir == East)
		dx = -1;

	if (storey->getTile(x + dx, y + dy) != Floor && storey->getTile(x + dx, y + dy) != Corridor)
		return false;

	if (RandomNumber::getInstance()->randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			storey->setTile(x, y, ClosedDoor);

			return true;
		}
	}
	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (storey->getTile(x + dx, y + dy) == Floor)
				storey->setTile(x, y, ClosedDoor);
			else // don't place a door between corridors
				storey->setTile(x, y, Corridor);

			return true;
		}
	}

	return false;
}

bool StoreyBuilder::makeRoom(int x, int y, Direction dir, bool firstRoom /*= false*/)
{
	static const int minRoomSize = 3;
	static const int maxRoomSize = 13;

	Rect room;
	room.width = RandomNumber::getInstance()->randomInt(minRoomSize, maxRoomSize);
	room.height = RandomNumber::getInstance()->randomInt(minRoomSize, maxRoomSize);

	//room并非以xy为中心生成，而是根据朝向，偏移一半的width或者heigh
	if (dir == North)
	{
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}

	else if (dir == South)
	{
		room.x = x - room.width / 2;
		room.y = y + 1;
	}

	else if (dir == West)
	{
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}

	else if (dir == East)
	{
		room.x = x + 1;
		room.y = y - room.height / 2;
	}

	if (placeRect(room, Floor))
	{
		rooms.emplace_back(room);

		placeMonster(room);

		//房间的出口在非朝向的三个方向，如果是第一个房间，那么4个方向都可作为出口
		//将当前步骤生成的可能的所有出口放入exits里面
		if (dir != South || firstRoom) // north side
			exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
		if (dir != North || firstRoom) // south side
			exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
		if (dir != East || firstRoom) // west side
			exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
		if (dir != West || firstRoom) // east side
			exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

		return true;
	}

	return false;
}

bool StoreyBuilder::makeCorridor(int x, int y, Direction dir)
{
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (RandomNumber::getInstance()->randomBool()) // horizontal corridor
	{
		corridor.width = RandomNumber::getInstance()->randomInt(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North)
		{
			corridor.y = y - 1;

			if (RandomNumber::getInstance()->randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == South)
		{
			corridor.y = y + 1;

			if (RandomNumber::getInstance()->randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == West)
			corridor.x = x - corridor.width;

		else if (dir == East)
			corridor.x = x + 1;
	}

	else // vertical corridor
	{
		corridor.width = 1;
		corridor.height = RandomNumber::getInstance()->randomInt(minCorridorLength, maxCorridorLength);

		if (dir == North)
			corridor.y = y - corridor.height;

		else if (dir == South)
			corridor.y = y + 1;

		else if (dir == West)
		{
			corridor.x = x - 1;

			if (RandomNumber::getInstance()->randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}

		else if (dir == East)
		{
			corridor.x = x + 1;

			if (RandomNumber::getInstance()->randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}
	}

	if (placeRect(corridor, Corridor))
	{
		if (dir != South && corridor.width != 1) // north side
			exits.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
		if (dir != North && corridor.width != 1) // south side
			exits.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
		if (dir != East && corridor.height != 1) // west side
			exits.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
		if (dir != West && corridor.height != 1) // east side
			exits.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

		return true;
	}

	return false;
}

bool StoreyBuilder::placeRect(const Field::Rect& rect, int tile)
{
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > storey->getWidth() - 1 || rect.y + rect.height > storey->getHeight() - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (storey->getTile(x, y) != Unused)
				return false; // the area already used
		}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				storey->setTile(x, y, Wall);
			else
				storey->setTile(x, y, tile);
		}

	return true;
}

bool StoreyBuilder::placeObject(int tile)
{
	if (rooms.empty())
		return false;

	int r = RandomNumber::getInstance()->randomInt(rooms.size()); // choose a random room
	int x = RandomNumber::getInstance()->randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = RandomNumber::getInstance()->randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);


	int temp=storey->getTile(x, y);
	if (storey->getTile(x, y) == Floor)
	{
		if (tile == UpStair)
		{
			storey->setUpCoord(cocos2d::Point(x, y));
		}
		else if (tile == DownStair)
		{
			storey->setDownCoord(cocos2d::Point(x, y));
		}
		storey->setTile(x, y, tile);

		// place one object in one room (optional)
		rooms.erase(rooms.begin() + r);

		return true;
	}

	return false;
}

void Field::StoreyBuilder::placeMonster(const Rect & rect)
{
	int x = RandomNumber::getInstance()->randomInt(rect.x + 1, rect.x + rect.width - 2);
	int y = RandomNumber::getInstance()->randomInt(rect.y + 1, rect.y + rect.height - 2);

	Character* monster = MonsterFactory::getInstance()->getMonster("Slime");

	CCAssert(monster, "get a null monster");

	storey->addCharacter(x, y, monster);

//	for (int i=rect.x+1;i<rect.x+rect.width-2;i++)
//	{
//		for (int j=rect.y+1;j<rect.y+rect.height-2;j++)
//		{
//			Character* monster = MonsterFactory::getInstance()->getMonster("Slime");
//			storey->setCharacter(i, j, monster);
//		}
//	}
}
