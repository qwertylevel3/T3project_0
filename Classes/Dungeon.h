#pragma once

#include"Storey.h"
#include"platform\CCPlatformMacros.h"
#include"Singleton.h"


namespace Field {

	class Dungeon:public Singleton<Dungeon>
	{
	public:
		Dungeon();
		~Dungeon();

		void generate(int floorNum);
		int getFloorNum();
		void addStorey(Storey* storey);
		Storey* getStorey();
		void writeToFile();
		void changeFloor(int floor);
		void nextFloor();
		void addCharacter(Character* character);
		void clear();

		//返回当前坐标的character，如果没有，返回nullPtr
		Character* getCharacter(int x,int y);
		Character* getCharacter(cocos2d::Point mapCoord);
	protected:
		std::vector<Storey*> storeyVec;
		CC_SYNTHESIZE(int, curFloor, CurFloor);
	};

}

