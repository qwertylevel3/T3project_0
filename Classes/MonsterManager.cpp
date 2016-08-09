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
		MonsterModel* model = new MonsterModel();

		tinyxml2::XMLElement* nameElement = monsterElement->FirstChildElement("name");
		std::string name = nameElement->GetText();
		model->setName(name);

		tinyxml2::XMLElement* characterNameElement = monsterElement->FirstChildElement("characterName");
		std::string characterName = characterNameElement->GetText();
		model->setCharacterName(characterName);

		tinyxml2::XMLElement* strengthElement = monsterElement->FirstChildElement("strength");
		std::string strengthStr = strengthElement->GetText();
		model->setStrength(ToolFunction::string2int(strengthStr));

		tinyxml2::XMLElement* intellectElement = monsterElement->FirstChildElement("intellect");
		std::string intellectStr = intellectElement->GetText();
		model->setIntellect(ToolFunction::string2int(intellectStr));

		tinyxml2::XMLElement* agilityElement = monsterElement->FirstChildElement("agility");
		std::string agilityStr = agilityElement->GetText();
		model->setAgility(ToolFunction::string2int(agilityStr));

		tinyxml2::XMLElement* HPElement = monsterElement->FirstChildElement("HP");
		std::string HPStr = HPElement->GetText();
		model->setHP(ToolFunction::string2int(HPStr));

		tinyxml2::XMLElement* MPElement = monsterElement->FirstChildElement("MP");
		std::string MPStr = MPElement->GetText();
		model->setMP(ToolFunction::string2int(MPStr));

		monsterMap[model->getName()] = model;

		monsterElement = monsterElement->NextSiblingElement();
	}
}

Character * MonsterManager::getMonster(std::string name)
{
	return monsterMap[name]->makeMonster();
}
