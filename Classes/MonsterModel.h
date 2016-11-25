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
	CC_SYNTHESIZE(std::string, leftHandName, LeftHandName);
	CC_SYNTHESIZE(std::string, rightHandName, RightHandName);
	CC_SYNTHESIZE(std::string, armorName, ArmorName);
	CC_SYNTHESIZE(std::string, accessoryName, AccessoryName);
};

