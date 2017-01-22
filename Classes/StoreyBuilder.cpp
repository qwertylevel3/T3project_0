#include "StoreyBuilder.h"
#include "Character.h"
#include "InventoryListGenerator.h"
#include"FieldEnum.h"
#include "ToolFunction.h"
#include"RandomNumber.h"
#include"cocos2d.h"
#include"Debug.h"
#include"GameActorFactory.h"

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

Storey* StoreyBuilder::generate(int level)
{
	curLevel = level;

	rooms.clear();
	exits.clear();

	int storeySize = 16 + level / 2;

	storey = nullptr;

	int maxFeatures = 33;
	bool flag = true;

	do
	{
		if (storey)
		{
			delete storey;
		}
		storey = new Storey(storeySize, storeySize);
		// place the first room in the center
		if (!makeRoom(storey->getWidth() / 2, storey->getHeight() / 2, static_cast<Direction>(RandomNumber::getInstance()->randomInt(4), true)))
		{
			continue;
		}
		if (!placeObject(UpStair))
		{
			continue;
		}

		// we already placed 1 feature (the first room)
		for (int i = 1; i < maxFeatures; ++i)
		{
			if (!createFeature())
			{
				//CCAssert(false, "Unable to place more features\n");
				break;
			}
		}

		if (!placeObject(DownStair))
		{
			continue;
		}

		//放置游戏演员
		placeFeatureForRoom();

		flag = false;
	} while (flag);

	return storey;
}

bool StoreyBuilder::createFeature()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (exits.empty())
			break;

		//从当前所有的可能出口矩形中随机选一个，再在这个矩形中选一个随机的xy坐标
		int r = RandomNumber::getInstance()->randomInt(exits.size());
		int x = RandomNumber::getInstance()->randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
		int y = RandomNumber::getInstance()->randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

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
	static const int roomChance = 90; // corridorChance = 100 - roomChance

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
	Rect room = makeRoomRect(x, y, dir);

	if (placeRect(room))
	{
		rooms.emplace_back(room);

		//placeGameActor(room);

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

	if (placeRect(corridor))
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

bool StoreyBuilder::placeRect(const Field::Rect& rect)
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
			{
				storey->setTile(x, y, Wall);
				//				Character* wall = GameActorFactory::getInstance()->getActor("wall");
				//				storey->addCharacter(cocos2d::Point(x, y), wall);
			}

			else
			{
				storey->setTile(x, y, Floor);
			}
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

	int temp = storey->getTile(x, y);
	if (storey->getTile(x, y) == Floor
		|| storey->getTile(x, y) == Ice
		|| storey->getTile(x, y) == Trap)
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

void Field::StoreyBuilder::placeGameActorLevel1(const Rect & rect)
{
	placeBuilding(rect);
	//房间内怪物数量(1-3之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(1, 3);

	//	int monsterNumber = 8;

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		Character* monster = GameActorFactory::getInstance()->getActor("slime");
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}

	//////////////////////////////////////////////////////////////////////////
}

void Field::StoreyBuilder::placeGameActorLevel2(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(1-4之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(1, 4);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 2);
		Character* monster;
		if (monsterType == 1)
		{
			monster = GameActorFactory::getInstance()->getActor("slime");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("snack");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel3(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(1-4之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(1, 4);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 3);
		Character* monster;
		if (monsterType == 1)
		{
			monster = GameActorFactory::getInstance()->getActor("slime");
		}
		else if (monsterType == 2)
		{
			monster = GameActorFactory::getInstance()->getActor("snack");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("ghost");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel4(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType == 1)
		{
			monster = GameActorFactory::getInstance()->getActor("slime");
		}
		else if (monsterType == 2)
		{
			monster = GameActorFactory::getInstance()->getActor("snack");
		}
		else if (monsterType == 3)
		{
			monster = GameActorFactory::getInstance()->getActor("ghost");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("ents");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel5(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType <= 3)
		{
			monster = GameActorFactory::getInstance()->getActor("blackSnack");
		}
		else if (monsterType <= 6)
		{
			monster = GameActorFactory::getInstance()->getActor("snack");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("ghost");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel6(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType <= 3)
		{
			monster = GameActorFactory::getInstance()->getActor("blackSnack");
		}
		else if (monsterType <= 6)
		{
			monster = GameActorFactory::getInstance()->getActor("demon");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("ghost");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel7(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType <= 2)
		{
			monster = GameActorFactory::getInstance()->getActor("ghost");
		}
		else if (monsterType <= 8)
		{
			monster = GameActorFactory::getInstance()->getActor("demon");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("summonWizard");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel8(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType <= 6)
		{
			monster = GameActorFactory::getInstance()->getActor("demon");
		}
		else if (monsterType <= 8)
		{
			monster = GameActorFactory::getInstance()->getActor("summonWizard");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("destroyWizard");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

void Field::StoreyBuilder::placeGameActorLevel9(const Rect& rect)
{
	placeBuilding(rect);
	//房间内怪物数量(2-5之间)
	int monsterNumber = RandomNumber::getInstance()->randomInt(2, 5);

	for (int i = 0; i < monsterNumber; i++)
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
		int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

		//		int x = rect.x;
		//		int y = rect.y;
		//		int x = rect.x+rect.width - 1;
		//		int y = rect.y+rect.height - 1;

		int monsterType = RandomNumber::getInstance()->randomInt(1, 10);
		Character* monster;
		if (monsterType <= 6)
		{
			monster = GameActorFactory::getInstance()->getActor("demon");
		}
		else if (monsterType <= 7)
		{
			monster = GameActorFactory::getInstance()->getActor("summonWizard");
		}
		else
		{
			monster = GameActorFactory::getInstance()->getActor("destroyWizard");
		}
		CCAssert(monster, "get a null monster");

		placeGameActor(x, y, monster);
	}
}

Field::Rect Field::StoreyBuilder::makeRoomRect(int x, int y, Direction dir)
{
	int minRoomSize = 3;
	int maxRoomSize = 5;

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

	return room;
}

void Field::StoreyBuilder::placeSpecialTile(const Rect& rect)
{
	//5层向上出现trap
	if (curLevel >= 5)
	{
		//trap数量(0-2之间)
		int trapNumber = RandomNumber::getInstance()->randomInt(0, 2);
		for (int i = 0; i < trapNumber; i++)
		{
			int x = RandomNumber::getInstance()->randomInt(rect.x, rect.x + rect.width - 1);
			int y = RandomNumber::getInstance()->randomInt(rect.y, rect.y + rect.height - 1);

			//		int x = rect.x;
			//		int y = rect.y;
			//		int x = rect.x+rect.width - 1;
			//		int y = rect.y+rect.height - 1;
			storey->setTile(x, y, Field::Trap);
		}
	}

	//7层向上出现ice
	if (curLevel >= 7)
	{
		//房间内ice数量(0-2之间)
		int iceNumber = RandomNumber::getInstance()->randomInt(0, 2);

		for (int i = 0; i < iceNumber; i++)
		{
			//这里的ice位置不贴墙，防止出现ai队友无法走出房间的bug
			int x = RandomNumber::getInstance()->randomInt(rect.x + 1, rect.x + rect.width - 2);
			int y = RandomNumber::getInstance()->randomInt(rect.y + 1, rect.y + rect.height - 2);

			//		int x = rect.x;
			//		int y = rect.y;
			//		int x = rect.x+rect.width - 1;
			//		int y = rect.y+rect.height - 1;
			storey->setTile(x, y, Field::Ice);
		}
	}
}

void Field::StoreyBuilder::placeGameActor(int x, int y, Character* character)
{
	cocos2d::Point coord(x, y);
	if (storey->isValid(coord)
		&& storey->isMoveAble(coord)
		&& storey->getCharacter(coord) == nullptr
		&& storey->getTile(coord.x, coord.y) != Field::Trap)
	{
		storey->addCharacter(coord.x, coord.y, character);
	}
	else
	{
		cocos2d::Point tempCoord;
		//如果该点已近被占用，找一个附近的点
		tempCoord = ToolFunction::findValidPlaceWithoutTrap(
			storey,
			cocos2d::Point(x, y)
		);

		//附近有合适的点
		if (tempCoord.x != x || tempCoord.y != y)
		{
			storey->addCharacter(tempCoord.x, tempCoord.y, character);
		}
		//如果没有直接退出，不放置这个character
	}
}

void Field::StoreyBuilder::placeBuilding(const Rect& rect)
{
	//0.2概率生成星塔
	if (RandomNumber::getInstance()->randomBool(1))
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x + 1, rect.x + rect.width - 2);
		int y = RandomNumber::getInstance()->randomInt(rect.y + 1, rect.y + rect.height - 2);

		Character* shine = GameActorFactory::getInstance()->getActor("shrine");
		CCAssert(shine, "get a null shine");

		placeBuilding(x, y, shine);
	}

	//0.1概率生成神像

	if (RandomNumber::getInstance()->randomBool(0.1))
	{
		int x = RandomNumber::getInstance()->randomInt(rect.x + 1, rect.x + rect.width - 2);
		int y = RandomNumber::getInstance()->randomInt(rect.y + 1, rect.y + rect.height - 2);

		Character* statue = GameActorFactory::getInstance()->getActor("statue");
		CCAssert(statue, "get a null statue");

		placeBuilding(x, y, statue);
	}
}

void Field::StoreyBuilder::placeBuilding(int x, int y, Character* building)
{
	if (storey->getTile(x, y) == Field::Trap)
	{
		storey->setTile(x, y, Field::Floor);
	}
	if (storey->getCharacter(x, y))
	{
		//如果已经放置了，放弃
		return;
	}
	storey->addCharacter(x, y, building);
}

void Field::StoreyBuilder::placeFeatureForRoom()
{
	//设置起始点神像
	Character* statue = GameActorFactory::getInstance()->getActor("statue");
	CCAssert(statue, "get a null portal");
	storey->addCharacter(storey->getUpCoord().x, storey->getUpCoord().y, statue);

	//test
	if (curLevel == 9)
	{
		//最后一层放置Boss
		Character* persephone = GameActorFactory::getInstance()->getActor("persephone");
		CCAssert(persephone, "get a null portal");
		storey->addCharacter(storey->getDownCoord().x, storey->getDownCoord().y, persephone);
	}
	else
	{
		//否则设置向下一层的传送门
		Character* portal = GameActorFactory::getInstance()->getActor("portal");
		CCAssert(portal, "get a null portal");
		storey->addCharacter(storey->getDownCoord().x, storey->getDownCoord().y, portal);
	}

	//设置宝箱
	for (int i = 1; i < storey->getWidth() - 1; i++)
	{
		for (int j = 1; j < storey->getHeight() - 1; j++)
		{
			if (storey->getTile(i, j) == Field::Floor)
			{
				int count = 0;
				if (storey->getTile(i - 1, j) == Field::Wall)
				{
					count++;
				}
				if (storey->getTile(i + 1, j) == Field::Wall)
				{
					count++;
				}
				if (storey->getTile(i, j - 1) == Field::Wall)
				{
					count++;
				}
				if (storey->getTile(i, j + 1) == Field::Wall)
				{
					count++;
				}

				if (count == 3)
				{
					int roll = RandomNumber::getInstance()->randomInt(1, 10);
					if (roll == 1)
					{
						continue;
					}
					std::string chestName = "chest" + ToolFunction::int2string(curLevel);
					Character* chest = GameActorFactory::getInstance()->getActor(chestName);
					CCAssert(chest, "get a null chest");

					placeGameActor(i, j, chest);
				}
			}
		}
	}

	for each (Rect room in rooms)
	{
		placeSpecialTile(room);

		if (curLevel == 1)
		{
			placeGameActorLevel1(room);
		}
		else if (curLevel == 2)
		{
			placeGameActorLevel2(room);
		}
		else if (curLevel == 3)
		{
			placeGameActorLevel3(room);
		}
		else if (curLevel == 4)
		{
			placeGameActorLevel4(room);
		}
		else if (curLevel == 5)
		{
			placeGameActorLevel5(room);
		}
		else if (curLevel == 6)
		{
			placeGameActorLevel6(room);
		}
		else if (curLevel == 7)
		{
			placeGameActorLevel7(room);
		}
		else if (curLevel == 8)
		{
			placeGameActorLevel8(room);
		}
		else if (curLevel == 9)
		{
			placeGameActorLevel9(room);
		}
	}
}