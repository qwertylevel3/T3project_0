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

int CharacterAttrHandler::getEvadePoint()
{
	return attr.evadePoint;
}

int CharacterAttrHandler::getAccuracyPoint()
{
	return attr.accuracyPoint;
}

int CharacterAttrHandler::getCriticalPro()
{
	return attr.criticalPro;
}

int CharacterAttrHandler::getCriticalPer()
{
	return attr.criticalPer;
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
	attr.maxHP = h;
}

void CharacterAttrHandler::setMaxMP(int m)
{
	oriAttr.maxMP = m;
	attr.maxMP = m;
}

void CharacterAttrHandler::setStrength(int strength)
{
	oriAttr.strength = strength;
	attr.strength = strength;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setIntellect(int intellect)
{
	oriAttr.intellect = intellect;
	attr.intellect = intellect;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setAgility(int agility)
{
	oriAttr.agility = agility;
	attr.agility = agility;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setViewSize(int viewSize)
{
	oriAttr.viewSize = viewSize;
	attr.viewSize = viewSize;
}

void CharacterAttrHandler::setMaxHPByBuff(int h)
{
	attr.maxHP = h;
}

void CharacterAttrHandler::setMaxMPByBuff(int m)
{
	attr.maxMP = m;
}

void CharacterAttrHandler::setStrengthByBuff(int strength)
{
	attr.strength = strength;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setIntellectByBuff(int intellect)
{
	attr.intellect = intellect;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setAgilityByBuff(int agility)
{
	attr.agility = agility;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setEvadePointByBuff(int e)
{
	attr.evadePoint = e;
}

void CharacterAttrHandler::setAccuracyPointByBuff(int a)
{
	attr.accuracyPoint = a;
}

void CharacterAttrHandler::setCriticalProByBuff(int p)
{
	attr.criticalPro = p;
}

void CharacterAttrHandler::setCriticalPerByBuff(int p)
{
	attr.criticalPer = p;
}

void CharacterAttrHandler::setCriticalPointByBuff(int c)
{
	attr.criticalPoint = c;
}

void CharacterAttrHandler::setBlockProByBuff(int p)
{
	attr.blockPro = p;
}

void CharacterAttrHandler::setBlockPointByBuff(int b)
{
	attr.blockPoint = b;
}

void CharacterAttrHandler::setComboProByBuff(int p)
{
	attr.comboPro = p;
}

void CharacterAttrHandler::setViewSizeByBuff(int viewSize)
{
	attr.viewSize = viewSize;
}


void CharacterAttrHandler::reset()
{
	attr = oriAttr;
}

void CharacterAttrHandler::recalculateBattleAttr()
{
	oriAttr.calculateBattleAttr();
	attr.calculateBattleAttr();
}
