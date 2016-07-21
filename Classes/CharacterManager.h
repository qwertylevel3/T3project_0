#pragma once

#include"Singleton.h"
#include"cocos2d.h"
#include"Character.h"

#include"CharacterModel.h"
#include<map>

class CharacterManager:public Singleton<CharacterManager>
{
public:
	CharacterManager();
	~CharacterManager();
	void init();
	Character* getCharacter(std::string characterName);
protected:
	void initCharacterModel(const std::string fileName);

	cocos2d::CCSpriteFrameCache * cache;
	std::map<std::string, CharacterModel*> modelMap;
};

