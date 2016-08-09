#pragma once

#include"Singleton.h"
#include<string>
#include<map>

class Character;
class MonsterModel;

class MonsterManager:public Singleton<MonsterManager>
{
public:
	MonsterManager();
	~MonsterManager();
	void init();
	Character* getMonster(std::string name);
protected:
	std::map<std::string, MonsterModel*> monsterMap;
};

