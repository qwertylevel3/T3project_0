#pragma once

#include"Singleton.h"
#include<string>
#include<map>
#include "tinyxml2/tinyxml2.h"

class Character;
class MonsterModel;

class MonsterManager:public Singleton<MonsterManager>
{
public:
	MonsterManager();
	~MonsterManager();
	void init();
	Character* getMonster(const std::string& name);
protected:
	void initModel(tinyxml2::XMLElement* monsterElement);
	int getIntAttr(tinyxml2::XMLElement* element,const std::string& attrName);
	std::string getStrAttr(tinyxml2::XMLElement* element,const std::string& attrName);
	std::map<std::string, MonsterModel*> monsterMap;
};

