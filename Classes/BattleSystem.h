#pragma once

#include"singleton.h"
class Character;

class BattleSystem:public Singleton<BattleSystem>
{
public:
	BattleSystem();
	~BattleSystem();
	void init();
	void attack(Character* a, Character* b);
protected:
	bool showMessage;
	void sufferAttack(Character* c, int attackCount);

	int getAttackCount(Character* a);
	int getCriticalAttackCount(Character* c);
	int getBlockCount(Character* c);

	bool isEvade(Character* a, Character* b);
	bool isCritical(Character* c);
	bool isBlock(Character* c);
	bool isCombo(Character* c);

	double getRandom(double start, double end);
	bool roll(double m);//0-100,m为下界，当roll值小于m返回true

	int getEvadeProAdd(Character* c);
	int getAccuracyProAdd(Character* c);
	int getCriticalProAdd(Character* c);
	int getCriticalAdd(Character* c);
	int getBlockProAdd(Character* c);
	int getBlockAdd(Character* c);
	int getComboProAdd(Character* c);

	int combo;
};

