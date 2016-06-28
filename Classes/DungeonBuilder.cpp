#include<sstream>
#include<tinyxml2\tinyxml2.h>
#include "DungeonBuilder.h"

DungeonBuilder::DungeonBuilder()
{
}

void DungeonBuilder::init(unsigned seed)
{
	mt.seed(seed);
	width = 100;
	height = 100;
	for (int i = 0; i < width*height; i++)
	{
		tiles.push_back(Unused);
	}
}

void DungeonBuilder::generate()
{
	int maxFeatures=50;
	// place the first room in the center
	if (!makeRoom(width / 2, height / 2, static_cast<Direction>(randomInt(4), true)))
	{
		std::cout << "Unable to place the first room.\n";
		return;
	}

	// we already placed 1 feature (the first room)
	for (int i = 1; i < maxFeatures; ++i)
	{
		if (!createFeature())
		{
			std::cout << "Unable to place more features (placed " << i << ").\n";
			break;
		}
		//print();
		//std::cin.get();

	}

	if (!placeObject(UpStairs))
	{
		std::cout << "Unable to place up stairs.\n";
		return;
	}

	if (!placeObject(DownStairs))
	{
		std::cout << "Unable to place down stairs.\n";
		return;
	}

//	for (int& tile : tiles)
//	{
//		if (tile == Unused)
//			tile = 1;
//		else if (tile == Floor || tile == Corridor)
//			tile = 2;
//	}
}

int DungeonBuilder::getTile(int x, int y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return Unused;

	return tiles[x + y * width];
}

void DungeonBuilder::setTile(int x, int y, int tile)
{
	tiles[x + y * width] = tile;
}

bool DungeonBuilder::createFeature()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (exits.empty())
			break;

		//从当前所有的可能出口矩形中随机选一个，再在这个矩形中选一个随机的xy坐标
		int r = randomInt(exits.size());
		int x = randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
		int y = randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

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

bool DungeonBuilder::createFeature(int x, int y, Direction dir)
{
	static const int roomChance = 50; // corridorChance = 100 - roomChance

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

	if (getTile(x + dx, y + dy) != Floor && getTile(x + dx, y + dy) != Corridor)
		return false;

	if (randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			setTile(x, y, ClosedDoor);

			return true;
		}
	}
	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (getTile(x + dx, y + dy) == Floor)
				setTile(x, y, ClosedDoor);
			else // don't place a door between corridors
				setTile(x, y, Corridor);

			return true;
		}
	}

	return false;
}

bool DungeonBuilder::makeRoom(int x, int y, Direction dir, bool firstRoom /*= false*/)
{
	static const int minRoomSize = 6;
	static const int maxRoomSize = 15;

	Rect room;
	room.width = randomInt(minRoomSize, maxRoomSize);
	room.height = randomInt(minRoomSize, maxRoomSize);

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

bool DungeonBuilder::makeCorridor(int x, int y, Direction dir)
{
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (randomBool()) // horizontal corridor
	{
		corridor.width = randomInt(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North)
		{
			corridor.y = y - 1;

			if (randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == South)
		{
			corridor.y = y + 1;

			if (randomBool()) // west
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
		corridor.height = randomInt(minCorridorLength, maxCorridorLength);

		if (dir == North)
			corridor.y = y - corridor.height;

		else if (dir == South)
			corridor.y = y + 1;

		else if (dir == West)
		{
			corridor.x = x - 1;

			if (randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}

		else if (dir == East)
		{
			corridor.x = x + 1;

			if (randomBool()) // north
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

bool DungeonBuilder::placeRect(const Rect& rect, int tile)
{
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > width - 1 || rect.y + rect.height > height - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (getTile(x, y) != Unused)
				return false; // the area already used
		}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				setTile(x, y, Wall);
			else
				setTile(x, y, tile);
		}

	return true;
}

bool DungeonBuilder::placeObject(int tile)
{
	if (rooms.empty())
		return false;

	int r = randomInt(rooms.size()); // choose a random room
	int x = randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

	if (getTile(x, y) == Floor)
	{
		setTile(x, y, tile);

		// place one object in one room (optional)
		rooms.erase(rooms.begin() + r);

		return true;
	}

	return false;
}

void DungeonBuilder::writeToFile()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + "tile.tmx";
	std::string picturePath = FileUtils::getInstance()->fullPathForFilename("tile.png");

	tinyxml2::XMLDocument *pDoc=new tinyxml2::XMLDocument();
	//xml 声明（参数可选）
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);

	//添加map节点
	tinyxml2::XMLElement *mapElement = pDoc->NewElement("map");
	mapElement->SetAttribute("version", "1.0");
	mapElement->SetAttribute("orientation", "orthogonal");
	mapElement->SetAttribute("renderorder", "right-down");
	mapElement->SetAttribute("width", width);
	mapElement->SetAttribute("height", height);
	mapElement->SetAttribute("tilewidth", "32");
	mapElement->SetAttribute("tileheight", 32);
	mapElement->SetAttribute("nextobjectid", "1");
	pDoc->LinkEndChild(mapElement);

	//添加tileset节点
	tinyxml2::XMLElement *tilesetElement = pDoc->NewElement("tileset");
	tilesetElement->SetAttribute("firstgid", "1");
	tilesetElement->SetAttribute("name", "tiled");
	tilesetElement->SetAttribute("tilewidth", "32");
	tilesetElement->SetAttribute("tileheight", "32");
	tilesetElement->SetAttribute("tilecount", "128");
	tilesetElement->SetAttribute("clumns", 64);
	mapElement->LinkEndChild(tilesetElement);

	//在tileset节点中添加image节点
	tinyxml2::XMLElement *imageElement = pDoc->NewElement("image");
	imageElement->SetAttribute("source", picturePath.c_str());
	imageElement->SetAttribute("width", "256");
	imageElement->SetAttribute("height", "512");
	tilesetElement->LinkEndChild(imageElement);

	//添加layer节点
	tinyxml2::XMLElement *layerElement = pDoc->NewElement("layer");
	layerElement->SetAttribute("name", "bk");
	layerElement->SetAttribute("width" , width);
	layerElement->SetAttribute("height", height);
	mapElement->LinkEndChild(layerElement);

	//添加layer中的bk data节点
	tinyxml2::XMLElement *bkdataElement = pDoc->NewElement("data");
	layerElement->LinkEndChild(bkdataElement);

	//bk data 数据
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", "1");
			bkdataElement->LinkEndChild(tempElement);
		}
	}


	//添加terrain layer节点
	tinyxml2::XMLElement *terrainlayerElement = pDoc->NewElement("layer");
	terrainlayerElement->SetAttribute("name", "terrain");
	terrainlayerElement->SetAttribute("width", width);
	terrainlayerElement->SetAttribute("height", height);
	mapElement->LinkEndChild(terrainlayerElement);

	//添加terrain layer中data
	tinyxml2::XMLElement *terraindataElement = pDoc->NewElement("data");
	terrainlayerElement->LinkEndChild(terraindataElement);

	//添加data数据
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tinyxml2::XMLElement *tempElement = pDoc->NewElement("tile");
			tempElement->SetAttribute("gid", getTile(i,j));
			terraindataElement->LinkEndChild(tempElement);
		}
	}

	pDoc->SaveFile(filePath.c_str());
	pDoc->Print();
	delete pDoc;
}
