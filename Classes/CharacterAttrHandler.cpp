#include "CharacterAttrHandler.h"
#include "Character.h"

CharacterAttrHandler::CharacterAttrHandler(Character* c)
{
	characterPtr = c;
}

CharacterAttrHandler::~CharacterAttrHandler()
{
}

bool CharacterAttrHandler::isPhysicalImmune()
{
	return attr.physicalImmune;
}

bool CharacterAttrHandler::isMagicImmune()
{
	return attr.magicImmune;
}

bool CharacterAttrHandler::isMoveAble()
{
	return attr.moveAble;
}

bool CharacterAttrHandler::isAttackAble()
{
	return attr.attackAble;
}

bool CharacterAttrHandler::isSkillAble()
{
	return attr.skillAble;
}

bool CharacterAttrHandler::isChantAble()
{
	return attr.chantAble;
}

bool CharacterAttrHandler::isActionAble()
{
	return attr.actionAble;
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

int CharacterAttrHandler::getLuck()
{
	return attr.luck;
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

int CharacterAttrHandler::getWeight()
{
	return attr.weight;
}

void CharacterAttrHandler::setPhysicalImmune(bool b)
{
	attr.physicalImmune = b;
	oriAttr.physicalImmune = b;

}

void CharacterAttrHandler::setMagicImmnue(bool b)
{
	attr.magicImmune = b;
	oriAttr.magicImmune = b;
}

void CharacterAttrHandler::setMoveAble(bool b)
{
	attr.moveAble = b;
	oriAttr.moveAble = b;
}

void CharacterAttrHandler::setAttackAble(bool b)
{
	attr.attackAble = b;
	oriAttr.attackAble = b;

}

void CharacterAttrHandler::setSkillAble(bool b)
{
	attr.skillAble = b;
	oriAttr.skillAble = b;
}

void CharacterAttrHandler::setChantAble(bool b)
{
	attr.chantAble = b;
	oriAttr.chantAble = b;
}

void CharacterAttrHandler::setActionAble(bool b)
{
	attr.actionAble = b;
	oriAttr.actionAble = b;
}

void CharacterAttrHandler::setMaxHP(int h)
{
	oriAttr.maxHP = h;
	attr.maxHP = h;
	if (characterPtr->getHP()>h)
	{
		characterPtr->setHP(h);
	}
}

void CharacterAttrHandler::setMaxMP(int m)
{
	oriAttr.maxMP = m;
	attr.maxMP = m;
	if (characterPtr->getMP() > m)
	{
		characterPtr->setMP(m);
	}
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

void CharacterAttrHandler::setLuck(int luck)
{
	oriAttr.luck = luck;
	attr.luck = luck;
}

void CharacterAttrHandler::setPhysicalImmnueByBuff(bool b)
{
	attr.physicalImmune = b;
}

void CharacterAttrHandler::setMagicImmuneByBuff(bool b)
{
	attr.magicImmune = b;
}

void CharacterAttrHandler::setMoveAbleByBuff(bool b)
{
	attr.moveAble = b;
}

void CharacterAttrHandler::setAttackAbleByBuff(bool b)
{
	attr.attackAble = b;
}

void CharacterAttrHandler::setSkillAbleByBuff(bool b)
{
	attr.skillAble = b;
}

void CharacterAttrHandler::setChantAbleByBuff(bool b)
{
	attr.chantAble = b;
}

void CharacterAttrHandler::setActionAbleByBuff(bool b)
{
	attr.actionAble = b;
}

void CharacterAttrHandler::setViewSize(int viewSize)
{
	oriAttr.viewSize = viewSize;
	attr.viewSize = viewSize;
}

void CharacterAttrHandler::setMaxHPByBuff(int h)
{
	attr.maxHP = h;
	if (characterPtr->getHP() > h)
	{
		characterPtr->setHP(h);
	}
}

void CharacterAttrHandler::setMaxMPByBuff(int m)
{
	attr.maxMP = m;
	if (characterPtr->getMP() > m)
	{
		characterPtr->setMP(m);
	}
}

void CharacterAttrHandler::setStrengthByBuff(int strength)
{
	strength = strength < 0 ? 0 : strength;
	attr.strength = strength;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setIntellectByBuff(int intellect)
{
	intellect = intellect < 0 ? 0 : intellect;
	attr.intellect = intellect;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setAgilityByBuff(int agility)
{
	agility = agility < 0 ? 0 : agility;
	attr.agility = agility;
	recalculateBattleAttr();
}

void CharacterAttrHandler::setLuckByBuff(int luck)
{
	attr.luck = luck;
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

void CharacterAttrHandler::setWeightByBuff(int w)
{
	attr.weight = w;
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