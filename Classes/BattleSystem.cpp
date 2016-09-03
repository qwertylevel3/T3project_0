#include "BattleSystem.h"
#include<cstdlib>
#include<ctime>
#include"armor.h"
#include"accessory.h"
#include"Character.h"
#include "platform/CCPlatformMacros.h"
#include "Weapon.h"



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
		type = c->getLeftHand()->getInventoryType();
		CCAssert(type == Inventory::OneHandWeapon || type == Inventory::TwoHandWeapon,
			"inventory in left hand is not weapon");
		weapon = static_cast<Weapon*>(c->getLeftHand());
		break;
	case RightHand:
		type = c->getRightHand()->getInventoryType();
		CCAssert(type == Inventory::OneHandWeapon || type == Inventory::TwoHandWeapon,
			"inventory in right hand is not weapon");
		weapon = static_cast<Weapon*>(c->getRightHand());
		break;
	}
	return weapon;
}

void BattleSystem::attack(Character * a, Character * b)
{
	combo = 0;
	do
	{
		if (a->getLeftHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
			attack(a, b, LeftHand);
			if (a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
			{
				attack(a, b, RightHand);
			}
		}
		else if (a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
			attack(a, b, RightHand);
		}
		else if (a->getLeftHand()->getInventoryType() == Inventory::TwoHandWeapon)
		{
			attack(a, b, DoubleHand);
		}

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

void BattleSystem::attack(Character* a, Character* b, AttackHand hand)
{
	if (!isInAtkArea(a, b, hand))
	{
		return;
	}
	if (isEvade(a, b, hand))
	{
		return;
	}

	int attackCount = 0;
	if (isCritical(a, hand))
	{
		attackCount = getCriticalAttackCount(a, hand);
	}
	else
	{
		attackCount = getAttackCount(a, hand);
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
	}

	attackCount = attackCount - armorCount - blockCount;
	attackCount = attackCount >= 1 ? attackCount : 1;
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
	double criticalAttack = double(attackCount)*(1 + k1*double(c->getStrength())) + getCriticalAdd(c, hand);
	return int(criticalAttack < 1 ? 1 : attackCount);
}

int BattleSystem::getBlockCount(Character* c)
{
	double k1 = 0.5;
	double str = c->getStrength();
	double count = k1*str + getBlockAdd(c) + 5;
	return int(count);
}

bool BattleSystem::isInAtkArea(Character* a, Character* b, AttackHand hand)
{

	std::vector<cocos2d::Point> atkArea;
	if (hand == LeftHand)
	{
		atkArea = a->getLeftHandAtkArea();
	}
	else if (hand == RightHand)
	{
		atkArea = a->getRightHandAtkArea();
	}
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

	return roll(temp);
}

bool BattleSystem::isCritical(Character* c, AttackHand hand)
{
	int criPro = getCriticalProCount(c, hand);

	return roll(criPro);
}

bool BattleSystem::isBlock(Character* c)
{
	int blockPro = getBlockProCount(c);

	return roll(blockPro);
}

bool BattleSystem::isCombo(Character* c)
{
	int comboPro = getComboProCount(c);

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

int BattleSystem::getEvadeCount(Character* c)
{
	double k1 = 1;
	double agility = c->getAgility();
	double evadeCount = agility* k1 + getEvadeProAdd(c);
	return int(evadeCount);
}

int BattleSystem::getAccuracyCount(Character* c, AttackHand hand)
{
	double k1=1;
	double agility = c->getAgility();
	double accuracyAdd = getAccuracyProAdd(c, hand);
	double accuracyCount = agility*k1 + accuracyAdd;
	return int(accuracyCount);
}

int BattleSystem::getCriticalProCount(Character* c, AttackHand hand)
{
	double k1 = 1;
	double agility = c->getAgility();

	double criProAdd = getCriticalProAdd(c, hand);

	double criPro = agility*k1 + criProAdd + 5;
	return int(criPro);
}

int BattleSystem::getBlockProCount(Character* c)
{
	double k1 = 1;
	double agility = c->getAgility();
	double blockProAdd = getBlockProAdd(c);

	double blockPro = agility*k1 + blockProAdd + 5;
	return int(blockPro);
}

int BattleSystem::getComboProCount(Character* c)
{
	double k1 = 0.1;
	double k2 = 5;
	double agility = c->getAgility();
	double comboProAdd = getComboProAdd(c);

	double comboPro = agility*k1 + comboProAdd + 5;
	comboPro = comboPro - k2*combo;
	comboPro = comboPro < 0 ? 0 : comboPro;
	return int(comboPro);
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

int BattleSystem::getAccuracyProAdd(Character* c, AttackHand hand)
{
	Weapon* weapon = getWeapon(c, hand);
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int weaponAccProAdd = weapon ? weapon->getAccuracyProAdd() : 0;
	int armorAccProAdd = armor ? armor->getAccuracyProAdd() : 0;
	int accessoryAccProAdd = accessory ? accessory->getAccuracyProAdd() : 0;

	return weaponAccProAdd
		+ armorAccProAdd
		+ accessoryAccProAdd;
}

int BattleSystem::getCriticalProAdd(Character* c, AttackHand hand)
{
	Weapon* weapon = getWeapon(c, hand);
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int weaponCriProAdd = weapon ? weapon->getCriticalProAdd() : 0;
	int armorCriProAdd = armor ? armor->getCriticalProAdd() : 0;
	int accessoryCriProAdd = accessory ? accessory->getCriticalProAdd() : 0;

	return weaponCriProAdd
		+ armorCriProAdd
		+ accessoryCriProAdd;
}

int BattleSystem::getCriticalAdd(Character* c, AttackHand hand)
{
	Weapon* weapon = getWeapon(c, hand);
	Inventory* armor = c->getArmor();
	Inventory* accessory = c->getAccessory();

	int weaponCriAdd = weapon ? weapon->getCriticalAdd() : 0;
	int armorCriAdd = armor ? armor->getCriticalAdd() : 0;
	int accessoryCriAdd = accessory ? accessory->getCriticalAdd() : 0;

	return weaponCriAdd
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
