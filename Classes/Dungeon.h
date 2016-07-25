#pragma once

#include"Storey.h"
#include"platform\CCPlatformMacros.h"


namespace Field {

	class Dungeon
	{
	public:
		Dungeon();
		~Dungeon();

		int getFloorNum();
		void addStorey(Storey* storey);
		Storey* getStorey();
		void writeToFile();
		void changeFloor(int floor);
		void nextFloor();
		void addCharacter(Character* character);
	protected:
		std::vector<Storey*> storeyVec;
		CC_SYNTHESIZE(int, curFloor, CurFloor);
	};

}

