#include "MonsterFactory.h"
#include"Character.h"
#include"MonsterModel.h"
#include<sstream>
#include"ToolFunction.h"

MonsterFactory::MonsterFactory()
{
}


MonsterFactory::~MonsterFactory()
{
}

void MonsterFactory::init()
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

Character * MonsterFactory::getMonster(const std::string& name)
{
	return monsterMap[name]->makeMonster();
}

void MonsterFactory::initModel(tinyxml2::XMLElement* monsterElement)
{
	MonsterModel* model = new MonsterModel();

	model->setName(getChildElementStrAttr(monsterElement,"name"));
	model->setCharacterName(getChildElementStrAttr(monsterElement,"characterName"));

	model->attr.physicalImmune = getChildElementIntAttr(monsterElement, "physicalImmune");
	model->attr.magicImmune = getChildElementIntAttr(monsterElement, "magicImmune");

	model->attr.moveAble = getChildElementIntAttr(monsterElement, "moveAble");
	model->attr.attackAble = getChildElementIntAttr(monsterElement, "attackAble");
	model->attr.chantAble = getChildElementIntAttr(monsterElement, "chantAble");
	model->attr.skillAble = getChildElementIntAttr(monsterElement, "skillAble");
	model->attr.actionAble = getChildElementIntAttr(monsterElement, "chantAble");

	model->attr.strength = getChildElementIntAttr(monsterElement, "strength");
	model->attr.intellect=getChildElementIntAttr(monsterElement,"intellect");
	model->attr.agility=getChildElementIntAttr(monsterElement,"agility");
	model->attr.luck = getChildElementIntAttr(monsterElement, "luck");
	model->attr.viewSize = getChildElementIntAttr(monsterElement, "viewSize");
	model->attr.maxHP = getChildElementIntAttr(monsterElement, "maxHP");
	model->attr.maxMP = getChildElementIntAttr(monsterElement, "maxMP");

	model->setLeftHandName(getChildElementStrAttr(monsterElement, "leftHand"));
	model->setRightHandName(getChildElementStrAttr(monsterElement, "rightHand"));
	model->setArmorName(getChildElementStrAttr(monsterElement, "armor"));
	model->setAccessoryName(getChildElementStrAttr(monsterElement, "accessory"));

	monsterMap[model->getName()] = model;
}
