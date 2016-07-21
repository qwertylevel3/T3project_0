#include "CharacterManager.h"
#include"tinyxml2\tinyxml2.h"
#include<vector>

USING_NS_CC;


CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::init()
{
	cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("test_character.plist");

	initCharacterModel("character.xml");
}

Character * CharacterManager::getCharacter(std::string characterName)
{
	return modelMap[characterName]->makeCharacter();
}

void CharacterManager::initCharacterModel(const std::string fileName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName.c_str());
	tinyxml2::XMLElement *characterBox = doc.RootElement();
	tinyxml2::XMLElement *character = characterBox->FirstChildElement("character");
	while (character)
	{
		CharacterModel* model = new CharacterModel();

		tinyxml2::XMLElement *nameElement = character->FirstChildElement();
		std::string modelName = nameElement->GetText();
		model->setName(modelName);

		tinyxml2::XMLElement* firstFrameElement = character->FirstChildElement("firstFrame");
		std::string firstFrame = firstFrameElement->GetText();
		model->setFirstFrameName(firstFrame);

		std::vector<std::string> frameVector;

		tinyxml2::XMLElement* moveUpElement = character->FirstChildElement("moveUpAnimation");
		tinyxml2::XMLElement* moveUpFrameElement = moveUpElement->FirstChildElement();
		while (moveUpFrameElement)
		{
			std::string frameName = moveUpFrameElement->GetText();
			frameVector.push_back(frameName);
			moveUpFrameElement = moveUpFrameElement->NextSiblingElement();
		}
		model->createMoveUpAnimation(frameVector);
		frameVector.clear();

		tinyxml2::XMLElement* moveDownElement = character->FirstChildElement("moveDownAnimation");
		tinyxml2::XMLElement* moveDownFrameElement = moveDownElement->FirstChildElement();
		while (moveDownFrameElement)
		{
			std::string frameName = moveDownFrameElement->GetText();
			frameVector.push_back(frameName);
			moveDownFrameElement = moveDownFrameElement->NextSiblingElement();
		}
		model->createMoveDownAnimation(frameVector);
		frameVector.clear();

		tinyxml2::XMLElement* moveLeftElement = character->FirstChildElement("moveLeftAnimation");
		tinyxml2::XMLElement* moveLeftFrameElement = moveLeftElement->FirstChildElement();
		while (moveLeftFrameElement)
		{
			std::string frameName = moveLeftFrameElement->GetText();
			frameVector.push_back(frameName);
			moveLeftFrameElement = moveLeftFrameElement->NextSiblingElement();
		}
		model->createMoveLeftAnimation(frameVector);
		frameVector.clear();

		tinyxml2::XMLElement* moveRightElement = character->FirstChildElement("moveRightAnimation");
		tinyxml2::XMLElement* moveRightFrameElement = moveRightElement->FirstChildElement();
		while (moveRightFrameElement)
		{
			std::string frameName = moveRightFrameElement->GetText();
			frameVector.push_back(frameName);
			moveRightFrameElement = moveRightFrameElement->NextSiblingElement();
		}
		model->createMoveRightAnimation(frameVector);
		frameVector.clear();

		modelMap[model->getName()] = model;

		character = character->NextSiblingElement();
	}
}

