#include "BuffMaxHPVal.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "CharacterAttr.h"



Buff::BuffMaxHPVal::BuffMaxHPVal()
{
	hpOffset = 0;
	this->setTrigType(BuffBase::OnLoad);
	this->setPriority(1);
}


Buff::BuffMaxHPVal::~BuffMaxHPVal()
{
}

void Buff::BuffMaxHPVal::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	int maxHP = attrHandler->getMaxHP();
	attrHandler->setMaxHPByBuff(maxHP + hpOffset);
}

void Buff::BuffMaxHPVal::setHPOffset(int offset)
{
	hpOffset = offset;
}
