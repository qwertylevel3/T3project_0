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

Character * MonsterManager::getMonster(std::string name)
{
	return monsterMap[name]->makeMonster();
}

void MonsterManager::initModel(tinyxml2::XMLElement* monsterElement)
{
	MonsterModel* model = new MonsterModel();

	model->setName(getStrAttr(monsterElement,"name"));
	model->setCharacterName(getStrAttr(monsterElement,"characterName"));
	model->setStrength(getIntAttr(monsterElement,"strength"));
	model->setIntellect(getIntAttr(monsterElement,"intellect"));
	model->setAgility(getIntAttr(monsterElement,"agility"));
	model->setHP(getIntAttr(monsterElement,"HP"));
	model->setMP(getIntAttr(monsterElement,"MP"));

	monsterMap[model->getName()] = model;
}

int MonsterManager::getIntAttr(tinyxml2::XMLElement* element, const std::string& attrName)
{
	tinyxml2::XMLElement* attrElement = element->FirstChildElement(attrName.c_str());
	return ToolFunction::string2int(attrElement->GetText());
}

std::string MonsterManager::getStrAttr(tinyxml2::XMLElement* element, const std::string& attrName)
{
	tinyxml2::XMLElement* attrElement = element->FirstChildElement(attrName.c_str());
	return attrElement->GetText();
}
