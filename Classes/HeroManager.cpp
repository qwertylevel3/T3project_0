#include "HeroManager.h"
#include <io.h>
#include <iostream>
#include "CharacterFactory.h"
#include "AIFactory.h"
#include "InventoryFactory.h"
#include "platform/CCFileUtils.h"
#include "MainLayer.h"
#include "Player.h"
#include "ToolFunction.h"

HeroManager::HeroManager()
{
}

HeroManager::~HeroManager()
{
	for each (Character* hero in heroBox)
	{
		delete hero;
	}
}

void HeroManager::init()
{
	_finddata_t fileDir;
	std::string dir = ".\\hero\\*.xml";
	long lfDir;

	if ((lfDir = _findfirst(dir.c_str(), &fileDir)) == -1l)
	{
		return;
	}
	else
	{
		do
		{
			if (fileDir.name != "."
				&& fileDir.name != "..")
			{
				initHero(fileDir.name);
				//std::cout << cocos2d::FileUtils::getInstance()->fullPathForFilename(fileDir.name) << std::endl;
			}
		} while (_findnext(lfDir, &fileDir) == 0);
	}
	_findclose(lfDir);
}

void HeroManager::initMission()
{
	Character* playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	cocos2d::Point playerCoord = playerCharacterPtr->getMapCoord();

	for each (Character*  hero in heroBox)
	{
		if (!hero->isDead())
		{
			cocos2d::Point coord = ToolFunction::findValidPlace(
				Field::Dungeon::getInstance()->getStorey(),
				playerCoord
			);
			//		hero->setMapCoord(cocos2d::Point(playerCoord.x, playerCoord.y + 1));
			hero->setMapCoord(coord);
			Field::Dungeon::getInstance()->addCharacter(hero);
		}
	}
}

void HeroManager::initHero(const std::string& fileName)
{
	std::string tempFileName = ".\\hero\\" + fileName;
	std::cout << tempFileName << std::endl;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(tempFileName.c_str());
	tinyxml2::XMLElement *heroElement = doc.RootElement();

	std::string heroName = getChildElementStrAttr(heroElement, "name");
	std::string characterName = getChildElementStrAttr(heroElement, "characterName");

	Character* characterPtr = CharacterFactory::getInstance()->getCharacter(characterName);
	characterPtr->setName(heroName);
	characterPtr->setCharacterType(Character::Good);
	characterPtr->setPlayType(Character::Hero);

	characterPtr->setAI(getChildElementStrAttr(heroElement, "AI"));
	characterPtr->setLevel(getChildElementIntAttr(heroElement, "level"));
	characterPtr->setHP(getChildElementIntAttr(heroElement, "HP"));
	characterPtr->setMaxHP(getChildElementIntAttr(heroElement, "HP"));
	characterPtr->setMP(getChildElementIntAttr(heroElement, "MP"));
	characterPtr->setMaxMP(getChildElementIntAttr(heroElement, "MP"));
	characterPtr->setStrength(getChildElementIntAttr(heroElement, "STR"));
	characterPtr->setAgility(getChildElementIntAttr(heroElement, "AGI"));
	characterPtr->setIntellect(getChildElementIntAttr(heroElement, "INT"));
	characterPtr->setLuck(getChildElementIntAttr(heroElement, "luck"));

	std::string leftHandName = getChildElementStrAttr(heroElement, "leftHand");
	std::string rightHandName = getChildElementStrAttr(heroElement, "rightHand");
	std::string armorName = getChildElementStrAttr(heroElement, "armor");
	std::string accessoryName = getChildElementStrAttr(heroElement, "accessory");

	if (leftHandName != "NULL")
	{
		Inventory* left = InventoryFactory::getInstance()->getInventory(leftHandName);
		characterPtr->equipLeftHand(left);
	}
	if (rightHandName != "NULL")
	{
		Inventory* right = InventoryFactory::getInstance()->getInventory(rightHandName);
		characterPtr->equipRightHand(right);
	}
	if (armorName != "NULL")
	{
		Inventory* armor = InventoryFactory::getInstance()->getInventory(armorName);
		characterPtr->equipArmor(armor);
	}

	if (accessoryName != "NULL")
	{
		Inventory* accessory = InventoryFactory::getInstance()->getInventory(accessoryName);
		characterPtr->equipAccessory(accessory);
	}

	tinyxml2::XMLElement* inventoryListElement = getChildElement(heroElement, "inventoryList");
	tinyxml2::XMLElement* inventoryElement = getChildElement(inventoryListElement, "inventory");

	while (inventoryElement)
	{
		std::string inventoryName = inventoryElement->GetText();
		characterPtr->addInventory(inventoryName);

		inventoryElement = inventoryElement->NextSiblingElement();
	}

	heroBox.push_back(characterPtr);
}