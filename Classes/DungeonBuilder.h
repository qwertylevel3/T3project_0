#pragma once

#include<cocos2d.h>
#include"Singleton.h"
#include<vector>
#include"Dungeon.h"

USING_NS_CC;

namespace Field {

	class DungeonBuilder :public Singleton<DungeonBuilder>
	{
	public:
		DungeonBuilder();
		void init();
		Dungeon* generate(int floorNum);
		void writeToFile();
	private:
		Dungeon* dungeon;
	};
}
