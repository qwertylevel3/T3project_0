#include "CharacterManager.h"

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
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("test_character.plist");

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

		tinyxml2::XMLElement *nameElement = character->FirstChildElement("name");
		std::string modelName = nameElement->GetText();
		model->setName(modelName);

		tinyxml2::XMLElement* firstFrameElement = character->FirstChildElement("firstFrame");
		std::string firstFrame = firstFrameElement->GetText();
		model->setFirstFrameName(firstFrame);

		std::vector<std::string> frameVector;

		createNextAnimationVector(character, "moveUpAnimation", frameVector);
		model->createMoveUpAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "moveDownAnimation", frameVector);
		model->createMoveDownAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "moveLeftAnimation", frameVector);
		model->createMoveLeftAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "moveRightAnimation", frameVector);
		model->createMoveRightAnimation(frameVector);
		frameVector.clear();

		createNextAnimationVector(character, "standUpAnimation", frameVector);
		model->createStandUpAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "standDownAnimation", frameVector);
		model->createStandDownAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "standLeftAnimation", frameVector);
		model->createStandLeftAnimation(frameVector);
		frameVector.clear();
		createNextAnimationVector(character, "standRightAnimation", frameVector);
		model->createStandRightAnimation(frameVector);
		frameVector.clear();

		modelMap[model->getName()] = model;

		character = character->NextSiblingElement();
	}
}

void CharacterManager::createNextAnimationVector(tinyxml2::XMLElement * root,std::string animationName,std::vector<std::string>& frameVec)
{
	tinyxml2::XMLElement* element = root->FirstChildElement(animationName.c_str());
	tinyxml2::XMLElement* frameElement = element->FirstChildElement();
	while (frameElement)
	{
		std::string frameName = frameElement->GetText();
		frameVec.push_back(frameName);
		frameElement = frameElement->NextSiblingElement();
	}
}

