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
	int getLuck();

	int getEvadePoint();
	int getAccuracyPoint();
	int getCriticalPro();
	int getCriticalPer();
	int getCriticalPoint();
	int getBlockPro();
	int getBlockPoint();
	int getComboPro();
	int getWeight();

	//////////////////////////////////////////////////////////////////////////

	void setMaxHP(int h);
	void setMaxMP(int m);
	void setViewSize(int viewSize);

	void setStrength(int strength);
	void setIntellect(int intellect);
	void setAgility(int agility);
	void setLuck(int luck);

	//////////////////////////////////////////////////////////////////////////

	void setMaxHPByBuff(int h);
	void setMaxMPByBuff(int m);
	void setViewSizeByBuff(int viewSize);
	void setWeightByBuff(int w);

	void setStrengthByBuff(int strength);
	void setIntellectByBuff(int intellect);
	void setAgilityByBuff(int agility);
	void setLuckByBuff(int luck);

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

