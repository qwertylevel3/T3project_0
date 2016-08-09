#include "MonsterModel.h"
#include"CharacterManager.h"



MonsterModel::MonsterModel()
{
}


MonsterModel::~MonsterModel()
{
}

Character * MonsterModel::makeMonster()
{
	Character* monster = CharacterManager::getInstance()->getCharacter(characterName);

	monster->setStrength(strength);
	monster->setIntellect(intellect);
	monster->setAgility(agility);
	monster->setHP(HP);
	monster->setMP(MP);
	monster->setCurHP(HP);
	monster->setCurMP(MP);
	monster->setCharacterType(Character::Bad);

	return monster;
}
