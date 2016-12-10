#include "GameActorFactory.h"
#include"Character.h"
#include"GameActorModel.h"
#include<sstream>
#include"ToolFunction.h"

GameActorFactory::GameActorFactory()
{
}


GameActorFactory::~GameActorFactory()
{
}

void GameActorFactory::init()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("gameActor.xml");
	tinyxml2::XMLElement* actorBoxElement = doc.RootElement();
	tinyxml2::XMLElement* actorElement = actorBoxElement->FirstChildElement();
	while (actorElement)
	{
		initModel(actorElement);

		actorElement = actorElement->NextSiblingElement();
	}
}

Character * GameActorFactory::getActor(const std::string& name)
{
	return actorMap[name]->makeActor();
}

void GameActorFactory::initModel(tinyxml2::XMLElement* actorElement)
{
	GameActorModel* model = new GameActorModel();

	model->setName(getChildElementStrAttr(actorElement,"name"));
	model->setCharacterName(getChildElementStrAttr(actorElement,"characterName"));
	model->setAIName(getChildElementStrAttr(actorElement, "ai"));
	model->setPlayType(getChildElementStrAttr(actorElement, "playType"));
	model->setCharacterType(getChildElementStrAttr(actorElement, "characterType"));

	model->attr.physicalImmune = getChildElementIntAttr(actorElement, "physicalImmune");
	model->attr.magicImmune = getChildElementIntAttr(actorElement, "magicImmune");

	model->attr.moveAble = getChildElementIntAttr(actorElement, "moveAble");
	model->attr.attackAble = getChildElementIntAttr(actorElement, "attackAble");
	model->attr.chantAble = getChildElementIntAttr(actorElement, "chantAble");
	model->attr.skillAble = getChildElementIntAttr(actorElement, "skillAble");
	model->attr.actionAble = getChildElementIntAttr(actorElement, "chantAble");

	model->attr.strength = getChildElementIntAttr(actorElement, "strength");
	model->attr.intellect=getChildElementIntAttr(actorElement,"intellect");
	model->attr.agility=getChildElementIntAttr(actorElement,"agility");
	model->attr.luck = getChildElementIntAttr(actorElement, "luck");
	model->attr.viewSize = getChildElementIntAttr(actorElement, "viewSize");
	model->attr.maxHP = getChildElementIntAttr(actorElement, "maxHP");
	model->attr.maxMP = getChildElementIntAttr(actorElement, "maxMP");

	model->setLeftHandName(getChildElementStrAttr(actorElement, "leftHand"));
	model->setRightHandName(getChildElementStrAttr(actorElement, "rightHand"));
	model->setArmorName(getChildElementStrAttr(actorElement, "armor"));
	model->setAccessoryName(getChildElementStrAttr(actorElement, "accessory"));

	actorMap[model->getName()] = model;
}
