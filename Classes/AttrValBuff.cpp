#include "AttrValBuff.h"



AttrValBuff::AttrValBuff()
{
}


AttrValBuff::~AttrValBuff()
{
}

void AttrValBuff::apply(Character* target)
{

}

void AttrValBuff::setStrengthOffset(int offset)
{
	attrOffset.strength = offset;
}

void AttrValBuff::setIntellectOffset(int offset)
{
	attrOffset.intellect = offset;
}

void AttrValBuff::setAgilityOffset(int offset)
{
	attrOffset.agility = offset;
}

void AttrValBuff::setLuckOffset(int offset)
{
	attrOffset.luck = offset;
}

void AttrValBuff::setViewSizeOffset(int offset)
{
	attrOffset.viewSize = offset;
}

void AttrValBuff::setMaxHPOffset(int offset)
{
	attrOffset.maxHP = offset;
}

void AttrValBuff::setMaxMPOffset(int offset)
{
	attrOffset.maxMP = offset;
}

void AttrValBuff::setEvadeProOffset(int offset)
{
	attrOffset.evadePro = offset;
}

void AttrValBuff::setAccuracyProOffset(int offset)
{
	attrOffset.accuracyPro = offset;
}

void AttrValBuff::setCriticalProOffset(int offset)
{
	attrOffset.criticalPro = offset;
}

void AttrValBuff::setCriticalPointOffset(int offset)
{

}

void AttrValBuff::setBlockProOffset(int offset)
{
	attrOffset.blockPro = offset;
}

void AttrValBuff::setBlockPointOffset(int offset)
{
	attrOffset.blockPoint = offset;
}

void AttrValBuff::setComboProOffset(int offset)
{
	attrOffset.comboPro = offset;
}
