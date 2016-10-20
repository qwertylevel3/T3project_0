#pragma once

#include"singleton.h"
class Character;
class Weapon;

class BattleSystem:public Singleton<BattleSystem>
{
public:
	enum AttackHand
	{
		LeftHand, RightHand, DoubleHand,Bow
	};
	BattleSystem();
	~BattleSystem();
	void init();
	void attack(Character* a, Character* b);

	int getAttackCount(Character* a,AttackHand hand);
	int getCriticalAttackCount(Character* c,AttackHand hand);
	int getCriticalPoint(Character* c);
	int getBlockCount(Character* c);
	int getEvadeCount(Character* c);
	int getAccuracyCount(Character* c, AttackHand hand);
	int getCriticalProCount(Character* c,AttackHand hand);
	int getBlockProCount(Character* c);
	int getComboProCount(Character* c);
protected:
	Weapon* getWeapon(Character* c,AttackHand hand);
	void attack(Character* a, Character* b, AttackHand hand);
	void sufferAttack(Character* c, int attackCount);

	bool isInAtkArea(Character* a,Character* b,AttackHand hand);
	bool isEvade(Character* a, Character* b,AttackHand hand);
	bool isCritical(Character* c,AttackHand hand);
	bool isBlock(Character* c);
	bool isCombo(Character* c);

	double getRandom(double start, double end);

	//0-100,m为下界，当roll值小于m返回true
	bool roll(double m);

	int combo;
};

