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
	int getViewSize();

	int getStrength();
	int getIntellect();
	int getAgility();

	int getEvadePoint();
	int getAccuracyPoint();
	int getCriticalPro();
	int getCriticalPer();
	int getCriticalPoint();
	int getBlockPro();
	int getBlockPoint();
	int getComboPro();

	//////////////////////////////////////////////////////////////////////////

	void setMaxHP(int h);
	void setMaxMP(int m);
	void setViewSize(int viewSize);

	void setStrength(int strength);
	void setIntellect(int intellect);
	void setAgility(int agility);

	//////////////////////////////////////////////////////////////////////////

	void setMaxHPByBuff(int h);
	void setMaxMPByBuff(int m);
	void setViewSizeByBuff(int viewSize);

	void setStrengthByBuff(int strength);
	void setIntellectByBuff(int intellect);
	void setAgilityByBuff(int agility);

	void setEvadePointByBuff(int e);
	void setAccuracyPointByBuff(int a);
	void setCriticalProByBuff(int p);
	void setCriticalPerByBuff(int p);
	void setCriticalPointByBuff(int c);
	void setBlockProByBuff(int p);
	void setBlockPointByBuff(int b);
	void setComboProByBuff(int p);


	//////////////////////////////////////////////////////////////////////////

	void reset();
	void recalculateBattleAttr();
protected:
	CharacterAttr attr;
	CharacterAttr oriAttr;
	Character* characterPtr;
};

