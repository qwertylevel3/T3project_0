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

int CharacterAttrHandler::getEvadePro()
{
	return attr.evadePro;
}

int CharacterAttrHandler::getAccuracuPro()
{
	return attr.accuracyPro;
}

int CharacterAttrHandler::getCriticalPro()
{
	return attr.criticalPro;
}

int CharacterAttrHandler::getCriticalPoint()
{
	return attr.criticalPoint;
}

int CharacterAttrHandler::getBlockPro()
{
	return attr.blockPro;
}

int CharacterAttrHandler::getBlockPoint()
{
	return attr.blockPoint;
}

int CharacterAttrHandler::getComboPro()
{
	return attr.comboPro;
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

void CharacterAttrHandler::recalculateAttr()
{
	attr = oriAttr;
}

