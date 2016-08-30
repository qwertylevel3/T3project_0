#include "Player.h"
#include"CharacterManager.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"InventoryManager.h"
#include"ToolFunction.h"
#include "InventoryInHand.h"
#include "Accessory.h"
#include "Armor.h"
#include "RoundSystem.h"

USING_NS_CC;
using namespace Field;

Player::Player()
{
}


Player::~Player()
{
}

void Player::init()
{
	characterPtr = CharacterManager::getInstance()->getCharacter("Actor0");
	controlMode = NormalMode;

	characterPtr->setStrength(10);
	characterPtr->setAgility(10);
	characterPtr->setIntellect(10);
	characterPtr->setCharacterType(Character::Good);

	//testInventory......

	Inventory* woodSword = InventoryManager::getInstance()->getInventory("sword000");
	woodSword->equipLeftHand(characterPtr);

	Inventory* ironSword = InventoryManager::getInstance()->getInventory("sword001");
	ironSword->equipRightHand(characterPtr);

	Inventory* testItem0 = InventoryManager::getInstance()->getInventory("sword001");
	Inventory* testItem1 = InventoryManager::getInstance()->getInventory("sword001");
	Inventory* testItem2 = InventoryManager::getInstance()->getInventory("sword001");
	Inventory* testItem3 = InventoryManager::getInstance()->getInventory("sword001");
	characterPtr->addInventory(testItem0);
	characterPtr->addInventory(testItem1);
	characterPtr->addInventory(testItem2);
	characterPtr->addInventory(testItem3);

//	Armor* armor = new Armor();
//	armor->setArmorCount(5);
//	characterPtr->setArmor(armor);
}

void Player::autoNextStep()
{
	cocos2d::Point startPoint = characterPtr->getMapCoord();
	cocos2d::Point endPoint = Dungeon::getInstance()->getStorey()->getDownCoord();
	cocos2d::Point nextStep = ToolFunction::nextStep(startPoint, endPoint);

	if (nextStep.x == startPoint.x + 1
		&& nextStep.y == startPoint.y)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	}
	else if (nextStep.x == startPoint.x - 1
		&& nextStep.y==startPoint.y)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW);
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y - 1)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW);
	}
	else if (nextStep.x == startPoint.x
		&& nextStep.y == startPoint.y + 1)
	{
		handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW);
	}
}

bool Player::isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode)
{
	cocos2d::Point position = characterPtr->getMapCoord();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		position.y -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		position.y += 1;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		position.x -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		position.x += 1;
		break;
	default:
		return false;
	}
	return Dungeon::getInstance()->getStorey()->isMoveAble(position);
}

void Player::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case NormalMode:
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			playerAttack(keyCode);
			break;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
		{
			controlMode = HaltMode;
			break;
		}
		playerMove(keyCode);
		break;
	case HaltMode:
		playerSetOrientation(keyCode);
		break;
	}

}

void Player::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case HaltMode:
		if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
		{
			controlMode = NormalMode;
		}
		break;
	}
}

void Player::playerAttack(cocos2d::EventKeyboard::KeyCode keyCode)
{

	characterPtr->runSkill("attack");
	RoundSystem::getInstance()->nextRound();
}

void Player::playerMove(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->moveUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->moveDown();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->moveLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->moveRight();
		break;
	}
	RoundSystem::getInstance()->nextRound();
}

void Player::playerSetOrientation(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->setOrientationUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->setOrientationDown();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->setOrientationLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->setOrientationRight();
		break;

	}
}

std::vector<Inventory*>& Player::getInventoryList()
{
	return characterPtr->getInventoryList();
}
