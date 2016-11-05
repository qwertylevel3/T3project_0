#pragma once

#include"cocos2d.h"
#include"Character.h"
#include "CharacterAttr.h"

class MonsterModel
{
public:
	MonsterModel();
	~MonsterModel();
	Character* makeMonster();
	CharacterAttr attr;
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::string, characterName, CharacterName);
};

