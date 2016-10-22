#include "BuffAgiVal.h"
#include "CharacterAttrHandler.h"
#include "Character.h"



Buff::BuffAgiVal::BuffAgiVal()
{
	agiOffset = 0;
	this->setTrigType(BuffBase::ATTR);
	this->setPriority(3);
}


Buff::BuffAgiVal::~BuffAgiVal()
{

}

void Buff::BuffAgiVal::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	int agility=attrHandler->getAgility();
	attrHandler->setAgilityByBuff(agility + agiOffset);
}

void Buff::BuffAgiVal::setOffset(int offset)
{
	agiOffset = offset;
}

