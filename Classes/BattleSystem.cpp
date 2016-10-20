#include "BattleSystem.h"
#include <iostream>
#include<cstdlib>
#include<ctime>
#include"armor.h"
#include"accessory.h"
#include"Character.h"
#include "Weapon.h"
#include "Marco.h"

using namespace std;


BattleSystem::BattleSystem()
{
}


BattleSystem::~BattleSystem()
{
}

void BattleSystem::init()
{
	combo = 0;
	srand(unsigned(time(0)));
}

Weapon* BattleSystem::getWeapon(Character* c, AttackHand hand)
{
	Weapon* weapon;
	Inventory::Type type;
	switch (hand)
	{
	case LeftHand:
	case DoubleHand:
	case Bow:
		type = c->getLeftHand() ? c->getLeftHand()->getInventoryType() : Inventory::Type::Empty;
		if (type == Inventory::OneHandWeapon || 
			type == Inventory::TwoHandWeapon ||
			type==Inventory::Bow)
		{
			weapon = static_cast<Weapon*>(c->getLeftHand());
		}
		else
		{
			weapon = nullptr;
		}

		break;
	case RightHand:
		type = c->getRightHand() ? c->getRightHand()->getInventoryType() : Inventory::Empty;
		if (type == Inventory::OneHandWeapon 
			|| type == Inventory::TwoHandWeapon
			|| type==Inventory::Bow)
		{
			weapon = static_cast<Weapon*>(c->getRightHand());
		}
		else
		{
			weapon = nullptr;
		}
		break;
	}
	return weapon;
}

void BattleSystem::attack(Character * a, Character * b)
{
#ifdef SHOWMESSAGE
	cout << "-----attack start------" << endl;
	cout << a->getName() << "(HP:" << a->getHP() << ")" << " -> "
		<< b->getName() << "(HP:" << b->getHP() << ")" << endl;
#endif
	combo = 0;
	do
	{
		if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~leftHand:" << endl;
#endif
			attack(a, b, LeftHand);
			if (a->getRightHand() && a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
			{
#ifdef SHOWMESSAGE
			cout << "~rightHand:" << endl;
#endif
				attack(a, b, RightHand);
			}
		}
		else if (a->getRightHand() && a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~rightHand:" << endl;
#endif
			attack(a, b, RightHand);
		}
		else if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::TwoHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~doubleHand:" << endl;
#endif
			attack(a, b, DoubleHand);
		}
		else if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::Bow)
		{
#ifdef SHOWMESSAGE
			cout << "~doubleHand:" << endl;
#endif
			attack(a, b, Bow);
		}



		if (!isCombo(a))
		{
			break;
		}
		else
		{
#ifdef SHOWMESSAGE
			cout << "combo!" << endl;
#endif
			combo++;
		}
	} while (true);
#ifdef SHOWMESSAGE
	cout << "-----attack end------" << endl;
	cout << a->getName() << "(HP:" << a->getHP() << ")" << " -> "
		<< b->getName() << "(HP:" << b->getHP() << ")" << endl;
	cout << "---------------------" << endl;
#endif
}

void BattleSystem::attack(Character* a, Character* b, AttackHand hand)
{
	if (!isInAtkArea(a, b, hand))
	{
#ifdef SHOWMESSAGE
		cout << "is not in atk area" << endl;
#endif
		return;
	}
	if (isEvade(a, b, hand))
	{
#ifdef SHOWMESSAGE
		cout << "evade!" << endl;
#endif
		return;
	}

	int attackCount = 0;
	if (isCritical(a, hand))
	{
		attackCount = getCriticalAttackCount(a, hand);
#ifdef SHOWMESSAGE
		cout << "critical atk!" << endl;
		cout << "atk count:" << attackCount << endl;
#endif
	}
	else
	{
		attackCount = getAttackCount(a, hand);
#ifdef SHOWMESSAGE
		cout << "atk count:" << attackCount << endl;
#endif
	}
	sufferAttack(b, attackCount);
}

void BattleSystem::sufferAttack(Character * c, int attackCount)
{
	Armor* armor = c->getArmor();
	int armorCount = 0;
	int blockCount = 0;
	if (armor)
	{
		armorCount = armor->getArmorCount();
	}
	if (isBlock(c))
	{
		blockCount = getBlockCount(c);
#ifdef SHOWMESSAGE
		cout << "block!" << endl;
		cout << "blockCount:" << blockCount << endl;
#endif
	}

	attackCount = attackCount - armorCount - blockCount;
	attackCount = attackCount >= 1 ? attackCount : 1;
#ifdef SHOWMESSAGE
	cout << "suffer damage:" << attackCount << endl;
#endif
	c->sufferDamage(attackCount);
}

int BattleSystem::getAttackCount(Character* a, AttackHand hand)
{
	double agility = a->getAgility();
	double strength = a->getStrength();

	Weapon* weapon = getWeapon(a, hand);
	double agiReq = 0;
	double strReq = 0;
	double attackCount = 0;

	if (!weapon)
	{
		return 0;
	}

	agiReq = weapon->getAgiRequire();
	strReq = weapon->getStrRequire();

	attackCount = weapon->getWeaponDamage();

	if (agiReq != 0 && agiReq >= agility)
	{
		attackCount = attackCount*agility / agiReq;
	}
	if (strReq != 0 && strReq >= strength)
	{
		attackCount = attackCount*strength / strReq;
	}

	return int(attackCount < 1 ? 1 : attackCount);
}

int BattleSystem::getCriticalAttackCount(Character* c, AttackHand hand)
{
	double k1 = 0.01;
	int attackCount = getAttackCount(c, hand);
	double criticalAttack = double(attackCount)*(1 + k1*double(c->getStrength())) + getCriticalPoint(c);
	return int(criticalAttack < 1 ? 1 : attackCount);
}

int BattleSystem::getCriticalPoint(Character* c)
{
	return c->getCriticalPoint();
}

int BattleSystem::getBlockCount(Character* c)
{
	return c->getBlockPoint();
}

bool BattleSystem::isInAtkArea(Character* a, Character* b, AttackHand hand)
{
	std::vector<cocos2d::Point> atkArea;
	atkArea = a->getAtkArea();
	for each (cocos2d::Point point in atkArea)
	{
		if (point == b->getMapCoord())
		{
			return true;
		}
	}
	return false;
}

bool BattleSystem::isEvade(Character* a, Character* b, AttackHand hand)
{
	double temp = getEvadeCount(b) - getAccuracyCount(a,hand);
	temp = temp > 0 ? temp : 0;
	temp = temp < 5 ? 5 : temp;
	temp = temp > 95 ? 95 : temp;
#ifdef SHOWMESSAGE
	cout << "evade chance:" << temp << endl;
#endif
	return roll(temp);
}

bool BattleSystem::isCritical(Character* c, AttackHand hand)
{
	int criPro = getCriticalProCount(c, hand);
#ifdef SHOWMESSAGE
	cout << "cirtical chance:" << criPro << endl;
#endif
	return roll(criPro);
}

bool BattleSystem::isBlock(Character* c)
{
	int blockPro = getBlockProCount(c);
#ifdef SHOWMESSAGE
	cout << "block chance:" << blockPro << endl;
#endif

	return roll(blockPro);
}

bool BattleSystem::isCombo(Character* c)
{
	int comboPro = getComboProCount(c);
#ifdef SHOWMESSAGE
	cout << "combo chance:" << comboPro << endl;
#endif
	return roll(comboPro);
}

double BattleSystem::getRandom(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

bool BattleSystem::roll(double m)
{
	double rand = getRandom(0, 100);
#ifdef SHOWMESSAGE
	cout << "	(roll:" << rand <<")"<< endl;
#endif
	if (rand < m)
	{
		return true;
	}
	return false;
}

int BattleSystem::getEvadeCount(Character* c)
{
	return c->getEvadePro();
}

int BattleSystem::getAccuracyCount(Character* c, AttackHand hand)
{
	return c->getAccuracuPro();
}

int BattleSystem::getCriticalProCount(Character* c, AttackHand hand)
{
	return c->getCriticalPro();
}

int BattleSystem::getBlockProCount(Character* c)
{
	return c->getBlockPro();
}

int BattleSystem::getComboProCount(Character* c)
{
	return c->getComboPro();
}
