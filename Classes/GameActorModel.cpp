#include "GameActorModel.h"
#include"CharacterFactory.h"
#include "AICommonEnemy.h"
#include "InventoryFactory.h"
#include "CharacterAttr.h"

GameActorModel::GameActorModel()
{
}

GameActorModel::~GameActorModel()
{
}

Character * GameActorModel::makeActor()
{
	Character* monster = CharacterFactory::getInstance()->getCharacter(characterName);

	monster->setName(name);
	monster->setPlayType(str2playType(playType));
	monster->setCharacterType(str2CharacterType(characterType));


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

	monster->setAI(aiName);

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

Character::PlayType GameActorModel::str2playType(std::string playType)
{
	if (playType=="enemy")
	{
		return Character::Enemy;
	}
	else if (playType=="object")
	{
		return Character::Object;
	}
	else
	{
		CCAssert(false, "error play type in game actor");
	}
}

Character::Type GameActorModel::str2CharacterType(std::string type)
{
	if (type=="good")
	{
		return Character::Good;
	}
	else if (type=="bad")
	{
		return Character::Bad;
	}
	else
	{
		return Character::Neutral;
	}
}
