#include "BattleSystem.h"
#include<cstdlib>
#include<ctime>
#include"weapon.h"
#include"armor.h"
#include"accessory.h"
#include"Character.h"



BattleSystem::BattleSystem()
{
}


BattleSystem::~BattleSystem()
{
}

void BattleSystem::init()
{
	srand(unsigned(time(0)));
}

void BattleSystem::attack(Character * a, Character * b)
{
	combo = 0;
	do
	{
		if (isEvade(a, b))
		{
			break;
		}
		int attackCount = 0;
		if (isCritical(a))
		{
			attackCount = getCriticalAttackCount(a);
		}
		else
		{
			attackCount = getAttackCount(a);
		}
		sufferAttack(b, attackCount);

		if (!isCombo(a))
		{
			break;
		}
		else
		{
			combo++;
		}
	} while (true);
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
	}

	attackCount = attackCount - armorCount - blockCount;
	attackCount = attackCount >= 1 ? attackCount : 1;
	c->sufferDamage(attackCount);
}

int BattleSystem::getAttackCount(Character* a)
{
	int agility = a->getAgility();
	int strength = a->getStrength();

	Weapon* leftHand = a->getLeftHand();
	int leftHandAgiReq = 0;
	int leftHandStrReq = 0;
	double leftHandAttack = 0;
	Weapon* rightHand = a->getRightHand();
	int rightHandAgiReq = 0;
	int rightHandStrReq = 0;
	double rightHandAttack = 0;

	if (leftHand)
	{
		leftHandAgiReq = leftHand->getAgiRequire();
		leftHandStrReq = leftHand->getStrRequire();

		leftHandAttack = leftHand->getWeaponDamage();

		if (leftHandAgiReq != 0 && leftHandAgiReq >= agility)
		{
			leftHandAttack = leftHandAttack*double(agility) / double(leftHandAgiReq);
		}
		if (leftHandStrReq != 0 && leftHandStrReq >= strength)
		{
			leftHandAttack = leftHandAttack*double(strength) / double(leftHandStrReq);
		}


	}
	if (rightHand)
	{
		rightHandAgiReq = rightHand->getAgiRequire();
		rightHandStrReq = rightHand->getStrRequire();

		rightHandAttack = rightHand->getWeaponDamage();

		if (rightHandAgiReq != 0 && rightHandAgiReq >= agility)
		{
			rightHandAttack = rightHandAttack*double(strength) / double(rightHandStrReq);
		}
		if (rightHandStrReq != 0 && rightHandStrReq >= strength)
		{
			rightHandAttack = rightHandAttack*double(agility) / double(rightHandAgiReq);
		}
	}
	return int(leftHandAttack + rightHandAttack);
}

int BattleSystem::getCriticalAttackCount(Character* c)
{
	double k1 = 0.01;
	int attackCount = getAttackCount(c);
	double criticalAttack = double(attackCount)*(1 + k1*double(c->getStrength())) + getCriticalAdd(c);
	return int(criticalAttack);
}

int BattleSystem::getBlockCount(Character* c)
{
	double k1 = 0.5;
	double str = c->getStrength();
	double count = k1*str + getBlockAdd(c) + 5;
	return int(count);
}

bool BattleSystem::isEvade(Character* a, Character* b)
{
	double B_agi = b->getAgility();
	double B_evadeAdd = getEvadeProAdd(b);
	double A_agi = a->getAgility();
	double A_accuracyAdd = getAccuracyProAdd(a);

	double k1 = 1;
	double k2 = 1;
	double k3 = 1;
	double temp = ((B_agi*k1 + B_evadeAdd) - (A_agi*k2 + A_accuracyAdd));
	temp = temp > 0 ? temp : 0;
	temp = temp*k3 + 5;
	temp = temp > 95 ? 95 : temp;

	return roll(temp);
}

bool BattleSystem::isCritical(Character* c)
{
	double k1 = 1;
	double agi = c->getAgility();

	double criProAdd = getCriticalProAdd(c);

	double criPro = agi*k1 + criProAdd + 5;

	return roll(criPro);
}

bool BattleSystem::isBlock(Character* c)
{
	double k1 = 1;
	double agi = c->getAgility();
	double blockProAdd = getBlockProAdd(c);

	double blockPro = agi*k1 + blockProAdd + 5;

	return roll(blockPro);
}

bool BattleSystem::isCombo(Character* c)
{
	double k1 = 0.1;
	double k2 = 5;
	double agility = c->getAgility();
	double comboProAdd = getComboProAdd(c);

	double comboPro = agility*k1 + comboProAdd + 5;
	comboPro = comboPro - k2*combo;
	comboPro = comboPro < 0 ? 0 : comboPro;

	return roll(comboPro);
}

double BattleSystem::getRandom(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

bool BattleSystem::roll(double m)
{
	double rand = getRandom(0, 100);

	if (rand < m)
	{
		return true;
	}
	return false;
}

int BattleSystem::getEvadeProAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandEvadeProAdd = leftHand ? leftHand->getEvadeProAdd() : 0;
	int rightHandEvadeProAdd = rightHand ? rightHand->getEvadeProAdd() : 0;
	int armorEvadeProAdd = armor ? armor->getEvadeProAdd() : 0;
	int accessoryEvadeProAdd = accessory ? accessory->getEvadeProAdd() : 0;

	return leftHandEvadeProAdd
		+ rightHandEvadeProAdd
		+ armorEvadeProAdd
		+ accessoryEvadeProAdd;
}

int BattleSystem::getAccuracyProAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandAccProAdd = leftHand ? leftHand->getAccuracyProAdd() : 0;
	int rightHandAccProAdd = rightHand ? rightHand->getAccuracyProAdd() : 0;
	int armorAccProAdd = armor ? armor->getAccuracyProAdd() : 0;
	int accessoryAccProAdd = accessory ? accessory->getAccuracyProAdd() : 0;

	return leftHandAccProAdd
		+ rightHandAccProAdd
		+ armorAccProAdd
		+ accessoryAccProAdd;
}

int BattleSystem::getCriticalProAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandCriProAdd = leftHand ? leftHand->getCriticalProAdd() : 0;
	int rightHandCriProAdd = rightHand ? rightHand->getCriticalProAdd() : 0;
	int armorCriProAdd = armor ? armor->getCriticalProAdd() : 0;
	int accessoryCriProAdd = accessory ? accessory->getCriticalProAdd() : 0;

	return leftHandCriProAdd
		+ rightHandCriProAdd
		+ armorCriProAdd
		+ accessoryCriProAdd;
}

int BattleSystem::getCriticalAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandCriAdd = leftHand ? leftHand->getCriticalAdd() : 0;
	int rightHandCriAdd = rightHand ? rightHand->getCriticalAdd() : 0;
	int armorCriAdd = armor ? armor->getCriticalAdd() : 0;
	int accessoryCriAdd = accessory ? accessory->getCriticalAdd() : 0;

	return leftHandCriAdd
		+ rightHandCriAdd
		+ armorCriAdd
		+ accessoryCriAdd;
}

int BattleSystem::getBlockProAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandBloProAdd = leftHand ? leftHand->getBlockProAdd() : 0;
	int rightHandBloProAdd = rightHand ? rightHand->getBlockProAdd() : 0;
	int armorBloProAdd = armor ? armor->getBlockProAdd() : 0;
	int accessoryBloProAdd = accessory ? accessory->getBlockProAdd() : 0;

	return leftHandBloProAdd
		+ rightHandBloProAdd
		+ armorBloProAdd
		+ accessoryBloProAdd;
}

int BattleSystem::getBlockAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandBloAdd = leftHand ? leftHand->getBlockAdd() : 0;
	int rightHandBloAdd = rightHand ? rightHand->getBlockAdd() : 0;
	int armorBloAdd = armor ? armor->getBlockAdd() : 0;
	int accessoryBloAdd = accessory ? accessory->getBlockAdd() : 0;

	return leftHandBloAdd
		+ rightHandBloAdd
		+ armorBloAdd
		+ accessoryBloAdd;
}

int BattleSystem::getComboProAdd(Character* c)
{
	Inventory* leftHand = c->getLeftHand();
	Inventory* rightHand = c->getRightHand();
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int leftHandComProAdd = leftHand ? leftHand->getComboProAdd() : 0;
	int rightHandComProAdd = rightHand ? rightHand->getComboProAdd() : 0;
	int armorComProAdd = armor ? armor->getComboProAdd() : 0;
	int accessoryComProAdd = accessory ? accessory->getComboProAdd() : 0;

	return leftHandComProAdd
		+ rightHandComProAdd
		+ armorComProAdd
		+ accessoryComProAdd;
}
