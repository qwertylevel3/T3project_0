#include "MonsterManager.h"
#include"Character.h"
#include"MonsterModel.h"
#include<sstream>
#include"ToolFunction.h"

MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
}

void MonsterManager::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("monster.xml");
	tinyxml2::XMLElement* monsterBoxElement = doc.RootElement();
	tinyxml2::XMLElement* monsterElement = monsterBoxElement->FirstChildElement();
	while (monsterElement)
	{
		initModel(monsterElement);

		monsterElement = monsterElement->NextSiblingElement();
	}
}

Character * MonsterManager::getMonster(const std::string& name)
{
	return monsterMap[name]->makeMonster();
}

void MonsterManager::initModel(tinyxml2::XMLElement* monsterElement)
{
	MonsterModel* model = new MonsterModel();

	model->setName(getChildElementStrAttr(monsterElement,"name"));
	model->setCharacterName(getChildElementStrAttr(monsterElement,"characterName"));
	model->setStrength(getChildElementIntAttr(monsterElement,"strength"));
	model->setIntellect(getChildElementIntAttr(monsterElement,"intellect"));
	model->setAgility(getChildElementIntAttr(monsterElement,"agility"));
	model->setHP(getChildElementIntAttr(monsterElement,"HP"));
	model->setMP(getChildElementIntAttr(monsterElement,"MP"));
	model->setViewSize(getChildElementIntAttr(monsterElement,"viewSize"));

	monsterMap[model->getName()] = model;
}
