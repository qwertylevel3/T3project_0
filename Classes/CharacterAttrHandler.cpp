#include "CharacterAttrHandler.h"



CharacterAttrHandler::CharacterAttrHandler(Character* c)
{
	characterPtr = c;
}


CharacterAttrHandler::~CharacterAttrHandler()
{
}

int CharacterAttrHandler::getMaxHP()
{
	return attr.maxHP;
}

int CharacterAttrHandler::getMaxMP()
{
	return attr.maxMP;
}

int CharacterAttrHandler::getStrength()
{
	return attr.strength;
}

int CharacterAttrHandler::getIntellect()
{
	return attr.intellect;
}

int CharacterAttrHandler::getAgility()
{
	return attr.agility;
}

int CharacterAttrHandler::getViewSize()
{
	return attr.viewSize;
}

CharacterAttr::CharacterType CharacterAttrHandler::getCharacterType()
{
	return attr.characterType;
}

void CharacterAttrHandler::setMaxHP(int h)
{
	oriAttr.maxHP = h;
	recalculateAttr();
}

void CharacterAttrHandler::setMaxMP(int m)
{
	oriAttr.maxMP = m;
	recalculateAttr();
}

void CharacterAttrHandler::setStrength(int strength)
{
	oriAttr.strength = strength;
	recalculateAttr();
}

void CharacterAttrHandler::setIntellect(int intellect)
{
	oriAttr.intellect = intellect;
	recalculateAttr();
}

void CharacterAttrHandler::setAgility(int agility)
{
	oriAttr.agility = agility;
	recalculateAttr();
}

void CharacterAttrHandler::setViewSize(int viewSize)
{
	oriAttr.viewSize = viewSize;
	recalculateAttr();
}

void CharacterAttrHandler::setCharacterType(CharacterAttr::CharacterType type)
{
	oriAttr.characterType = type;
	recalculateAttr();
}

void CharacterAttrHandler::recalculateAttr()
{
	attr = oriAttr;
}

