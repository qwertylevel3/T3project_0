#pragma once

#include"Singleton.h"
#include"cocos2d.h"
#include"Character.h"
#include"tinyxml2\tinyxml2.h"

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
	void createNextAnimationVector(tinyxml2::XMLElement* root,
		std::string animationName,
		std::vector<std::string>& frameVec);

	std::map<std::string, CharacterModel*> modelMap;
};

