#pragma once

#include<cocos2d.h>
#include"Singleton.h"
#include<random>
#include<vector>
#include<iostream>
#include<fstream>

USING_NS_CC;

class DungeonBuilder :public Singleton<DungeonBuilder>
{
public:
	enum Tile
	{
		Unused = 1,
		Floor = 21,
		Corridor = 21,
		Wall = 110,
		ClosedDoor = 21,
		OpenDoor = 21,
		UpStairs = 7,
		DownStairs = 8
	};
	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

	struct Rect
	{
		int x, y;
		int width, height;
	};

	int randomInt(int exclusiveMax);
	int randomInt(int min, int max);
	bool randomBool(double probability = 0.5);


	DungeonBuilder();
	void init(unsigned seed);
	void generate();
	int getTile(int x, int y) const ;
	void setTile(int x, int y, int tile);

	bool createFeature();
	bool createFeature(int x, int y, Direction dir);

	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
	bool makeCorridor(int x, int y, Direction dir);

	bool placeRect(const Rect& rect, int tile);
	bool placeObject(int tile);

	void writeToFile();
private:
	int width;
	int height;
	std::vector<int> tiles;
	std::vector<Rect> rooms;
	std::vector<Rect> exits;
	//std::random_device rd;
	std::mt19937 mt;//(rd());
};

