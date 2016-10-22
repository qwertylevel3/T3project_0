#include "BuffMaxHPPer.h"
#include "CharacterAttrHandler.h"
#include "CharacterAttr.h"
#include "Character.h"



Buff::BuffMaxHPPer::BuffMaxHPPer()
{
	percent = 0;
	this->setTrigType(BuffBase::ATTR);
	this->setPriority(2);
}


Buff::BuffMaxHPPer::~BuffMaxHPPer()
{
}

void Buff::BuffMaxHPPer::setPercent(int per)
{
	percent = per;
}

void Buff::BuffMaxHPPer::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	int maxHP = attrHandler->getMaxHP();
	attrHandler->setMaxHPByBuff(double(maxHP)*(1.0+double(percent)/100.0));
}
