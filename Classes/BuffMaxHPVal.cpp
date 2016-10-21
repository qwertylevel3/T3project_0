#include "BuffMaxHPVal.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "CharacterAttr.h"



Buff::BuffMaxHPVal::BuffMaxHPVal()
{
	hpOffset = 0;
	this->setType(BuffBase::OnLoad);
	this->setPriority(0);
}


Buff::BuffMaxHPVal::~BuffMaxHPVal()
{
}

void Buff::BuffMaxHPVal::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	int maxHP = attrHandler->getMaxHP();
	attrHandler->setMaxHP(maxHP + hpOffset);
}

void Buff::BuffMaxHPVal::setHPOffset(int offset)
{
	hpOffset = offset;
}
