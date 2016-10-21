#pragma once

#include "CharacterAttr.h"

class Character;

class CharacterAttrHandler
{
public:
	CharacterAttrHandler(Character* c);
	~CharacterAttrHandler();

	int getMaxHP();
	int getMaxMP();
	int getStrength();
	int getIntellect();
	int getAgility();
	int getViewSize();

	int getEvadePro();
	int getAccuracuPro();
	int getCriticalPro();
	int getCriticalPoint();
	int getBlockPro();
	int getBlockPoint();
	int getComboPro();

	//////////////////////////////////////////////////////////////////////////

	void setMaxHP(int h);
	void setMaxMP(int m);
	void setStrength(int strength);
	void setIntellect(int intellect);
	void setAgility(int agility);
	void setViewSize(int viewSize);
	
	void recalculateAttr();
protected:
	CharacterAttr attr;
	CharacterAttr oriAttr;
	Character* characterPtr;
};

