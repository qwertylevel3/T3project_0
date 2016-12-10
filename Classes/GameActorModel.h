#pragma once

#include"cocos2d.h"
#include"Character.h"
#include "CharacterAttr.h"

class GameActorModel
{
public:
	GameActorModel();
	~GameActorModel();
	Character* makeActor();
	CharacterAttr attr;
protected:
	Character::PlayType str2playType(std::string playType);
	Character::Type str2CharacterType(std::string type);

	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::string, characterName, CharacterName);
	CC_SYNTHESIZE(std::string, leftHandName, LeftHandName);
	CC_SYNTHESIZE(std::string, rightHandName, RightHandName);
	CC_SYNTHESIZE(std::string, armorName, ArmorName);
	CC_SYNTHESIZE(std::string, accessoryName, AccessoryName);
	CC_SYNTHESIZE(std::string, aiName, AIName);
	CC_SYNTHESIZE(std::string, playType, PlayType);
	CC_SYNTHESIZE(std::string, characterType, CharacterType);
};

