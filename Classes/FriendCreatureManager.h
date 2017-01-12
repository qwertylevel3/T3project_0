#pragma once

#include "Singleton.h"
#include <vector>


class Character;


class FriendCreatureManager:public Singleton<FriendCreatureManager>
{
public:
	FriendCreatureManager();
	~FriendCreatureManager();
	void init();
	void initMission();
	void addCharacter(Character* creature);
	void restart();
protected:
	void clear();
	std::vector<Character*> creatureList;
};

