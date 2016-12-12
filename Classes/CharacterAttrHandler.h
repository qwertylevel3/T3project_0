#pragma once

#include "CharacterAttr.h"

class Character;

class CharacterAttrHandler
{
public:
	CharacterAttrHandler(Character* c);
	~CharacterAttrHandler();

	bool isPhysicalImmune();
	bool isMagicImmune();

	bool isMoveAble();
	bool isAttackAble();
	bool isSkillAble();
	bool isChantAble();
	bool isActionAble();
	
	int getMaxHP();
	int getMaxMP();
	int getViewSize();

	int getOriStrength();
	int getOriIntellect();
	int getOriAgility();

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

	void setPhysicalImmune(bool b);
	void setMagicImmnue(bool b);

	void setMoveAble(bool b);
	void setAttackAble(bool b);
	void setSkillAble(bool b);
	void setChantAble(bool b);
	void setActionAble(bool b);

	void setMaxHP(int h);
	void setMaxMP(int m);
	void setViewSize(int viewSize);

	void setStrength(int strength);
	void setIntellect(int intellect);
	void setAgility(int agility);
	void setLuck(int luck);

	//////////////////////////////////////////////////////////////////////////
	void setPhysicalImmnueByBuff(bool b);
	void setMagicImmuneByBuff(bool b);

	void setMoveAbleByBuff(bool b);
	void setAttackAbleByBuff(bool b);
	void setSkillAbleByBuff(bool b);
	void setChantAbleByBuff(bool b);
	void setActionAbleByBuff(bool b);

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

