#include "BuffAutoHeal.h"
#include "Character.h"
#include "ToolFunction.h"



Buff::BuffAutoHeal::BuffAutoHeal()
{
	this->setName("autoHeal");
	this->setCname(ToolFunction::WStr2UTF8(L"×Ô¶¯»Ø¸´"));
	this->setBuffType(BuffBase::Good);
	this->setTrigType(BuffBase::OnRoundStart);
	this->setPriority(99);
	this->setDuration(-1);
}


Buff::BuffAutoHeal::~BuffAutoHeal()
{
}

void Buff::BuffAutoHeal::apply(Character* target)
{
	target->sufferHPEffect(2);
	target->sufferMPEffect(2);
}
