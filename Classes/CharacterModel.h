#pragma once

#include<string>
#include"cocos2d.h"
#include"Character.h"
#include<vector>

class CharacterModel
{
public:
	CharacterModel();
	~CharacterModel();

	Character* makeCharacter();

	cocos2d::CCAnimation* createAnimation(const std::vector<std::string>& frameList);
	void createMoveUpAnimation(const std::vector<std::string>& frameList);
	void createMoveDownAnimation(const std::vector<std::string>& frameList);
	void createMoveLeftAnimation(const std::vector<std::string>& frameList);
	void createMoveRightAnimation(const std::vector<std::string>& frameList);
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::string, firstFrameName, FirstFrameName);

	cocos2d::CCAnimation* moveUpAnimation;
	cocos2d::CCAnimation* moveDownAnimation;
	cocos2d::CCAnimation* moveLeftAnimation;
	cocos2d::CCAnimation* moveRightAnimation;
};

