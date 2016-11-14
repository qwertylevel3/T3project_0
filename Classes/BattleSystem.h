#pragma once

#include"singleton.h"
#include <vector>
#include "base/ccTypes.h"

class Character;
class Weapon;

namespace cocos2d
{
	class Animation;
}

class BattleSystem :public Singleton<BattleSystem>
{
public:
	enum AttackHand
	{
		LeftHand, RightHand, DoubleHand, Bow
	};
	BattleSystem();
	~BattleSystem();
	void init();
	void attack(Character* a, Character* b);
	void attack(Character* caster, std::vector<cocos2d::Point>& coords);


	int getAttackCount(Character* a, AttackHand hand);
	int getCriticalAttackCount(Character* c, AttackHand hand);
	int getCriticalPoint(Character* c);
	int getBlockCount(Character* c);
	int getEvadeCount(Character* c);
	int getAccuracyCount(Character* c);
	int getCriticalProCount(Character* c);
	int getBlockProCount(Character* c);
	int getComboProCount(Character* c);
protected:
	void showAttackEffect(Character* caster,AttackHand hand);
	void showOneHandEffect(Character* caster);
	void showTwoHandEffect(Character* caster);
	void showBowEffect(Character* caster);

	Weapon* getWeapon(Character* c, AttackHand hand);
	void attack(Character* a, Character* b, AttackHand hand);
	//************************************
	// Method:    sufferAttack
	// FullName:  BattleSystem::sufferAttack
	// Access:    protected
	// Returns:   int
	// Qualifier: 返回真实收到的伤害值
	// Parameter: Character * c
	// Parameter: int attackCount
	//************************************
	int sufferAttack(Character* c, int attackCount);

	bool isInAtkArea(Character* a, Character* b, AttackHand hand);
	bool isEvade(Character* a, Character* b, AttackHand hand);
	bool isCritical(Character* c);
	bool isBlock(Character* c);
	bool isCombo(Character* c);

	double getRandom(double start, double end);

	//0-100,m为下界，当roll值小于m返回true
	bool roll(double m);

	int combo;
	cocos2d::Animation* animation;
};
