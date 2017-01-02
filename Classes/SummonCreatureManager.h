#pragma once

#include "Singleton.h"
#include <vector>


class Character;


//处理召唤生物的资源保存和析构
class SummonCreatureManager:public Singleton<SummonCreatureManager>
{
public:
	SummonCreatureManager();
	~SummonCreatureManager();
	void init();
	void initMission();
	void addCharacter(Character* creature);
protected:
	std::vector<Character*> creatureList;
};

