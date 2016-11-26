#include "MonsterModel.h"
#include"CharacterFactory.h"
#include "AICommonEnemy.h"
#include "InventoryFactory.h"
#include "CharacterAttr.h"

MonsterModel::MonsterModel()
{
}

MonsterModel::~MonsterModel()
{
}

Character * MonsterModel::makeMonster()
{
	Character* monster = CharacterFactory::getInstance()->getCharacter(characterName);

	monster->setName(name);

	monster->setPhysicalImmune(attr.physicalImmune);
	monster->setMagicImmnue(attr.magicImmune);

	monster->setMoveAble(attr.moveAble);
	monster->setAttackAble(attr.attackAble);
	monster->setChantAble(attr.chantAble);
	monster->setSkillAble(attr.skillAble);
	monster->setActionAble(attr.actionAble);

	monster->setStrength(attr.strength);
	monster->setIntellect(attr.intellect);
	monster->setAgility(attr.agility);
	monster->setHP(attr.maxHP);
	monster->setMP(attr.maxMP);
	monster->setMaxHP(attr.maxHP);
	monster->setMaxMP(attr.maxMP);
	monster->setLuck(attr.luck);
	monster->setViewSize(attr.viewSize);
	monster->setCharacterType(Character::Bad);

	AICommonEnemy* ai = new AICommonEnemy();
	monster->setAI(ai);

	if (leftHandName!="NULL")
	{
		Inventory* left = InventoryFactory::getInstance()->getInventory(leftHandName);
		monster->equipLeftHand(left);
	}
	if (rightHandName!="NULL")
	{
		Inventory* right = InventoryFactory::getInstance()->getInventory(rightHandName);
		monster->equipRightHand(right);
	}
	if (armorName!="NULL")
	{
		Inventory* armor = InventoryFactory::getInstance()->getInventory(armorName);
		monster->equipArmor(armor);
	}

	if (accessoryName!="NULL")
	{
		Inventory* accessory = InventoryFactory::getInstance()->getInventory(accessoryName);
		monster->equipAccessory(accessory);
	}

	return monster;
}