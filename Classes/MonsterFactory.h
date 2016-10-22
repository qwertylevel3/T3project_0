#pragma once

#include"Singleton.h"
#include<string>
#include<map>
#include "XMLConfigure.h"
#include "tinyxml2/tinyxml2.h"

class Character;
class MonsterModel;

class MonsterFactory:public XMLConfigure,public Singleton<MonsterFactory>
{
public:
	MonsterFactory();
	~MonsterFactory();
	void init();
	Character* getMonster(const std::string& name);
protected:
	void initModel(tinyxml2::XMLElement* monsterElement);

	std::map<std::string, MonsterModel*> monsterMap;
};

