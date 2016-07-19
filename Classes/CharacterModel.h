#pragma once

#include<string>
#include"cocos2d.h"
#include"Character.h"

class CharacterModel
{
public:
	CharacterModel();
	~CharacterModel();

	Character* makeCharacter();
protected:
	CC_SYNTHESIZE(std::string, name, Name);

	cocos2d::CCAnimation* moveUpAnimation;
	cocos2d::CCAnimation* moveDownAnimation;
	cocos2d::CCAnimation* moveLeftAnimation;
	cocos2d::CCAnimation* moveRightAnimation;
};

