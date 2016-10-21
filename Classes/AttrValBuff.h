#pragma once

#include "BuffBase.h"
#include "CharacterAttr.h"

class AttrValBuff:public BuffBase
{
public:
	AttrValBuff();
	~AttrValBuff();
	void apply(Character* target);

	void setStrengthOffset(int offset);
	void setIntellectOffset(int offse);
	void setAgilityOffset(int offset);

	void setLuckOffset(int offset);
	void setViewSizeOffset(int offset);
	void setMaxHPOffset(int offset);
	void setMaxMPOffset(int offset);

	void setEvadeProOffset(int offset);
	void setAccuracyProOffset(int offset);
	void setCriticalProOffset(int offset);
	void setCriticalPointOffset(int offset);
	void setBlockProOffset(int offset);
	void setBlockPointOffset(int offset);
	void setComboProOffset(int offset);
protected:
	CharacterAttr attrOffset;
};

