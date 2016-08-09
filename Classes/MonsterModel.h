#pragma once

#include"cocos2d.h"
#include"Character.h"

class MonsterModel
{
public:
	MonsterModel();
	~MonsterModel();
	Character* makeMonster();
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::string, characterName, CharacterName);
	CC_SYNTHESIZE(int, strength, Strength);
	CC_SYNTHESIZE(int, intellect, Intellect);
	CC_SYNTHESIZE(int, agility, Agility);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, MP, MP);
};

