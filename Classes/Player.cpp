#include "Player.h"
#include"CharacterFactory.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"InventoryFactory.h"
#include"ToolFunction.h"
#include "InventoryInHand.h"
#include "Accessory.h"
#include "Armor.h"
#include "RoundSystem.h"
#include "MainLayer.h"
#include "BuffFactory.h"

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
	characterPtr = CharacterFactory::getInstance()->getCharacter("Actor0");

	setName("qwerty");

	controlMode = NormalMode;

	characterPtr->setHP(100);
	characterPtr->setMaxHP(100);
	characterPtr->setMP(100);
	characterPtr->setMaxMP(100);

	characterPtr->setStrength(10);
	characterPtr->setAgility(10);
	characterPtr->setIntellect(10);
	characterPtr->setLuck(10);
	characterPtr->setViewSize(5);
	characterPtr->setCharacterType(Character::Good);

	//testInventory......

	Inventory* woodSword = InventoryFactory::getInstance()->getInventory("sword000");
	woodSword->equipLeftHand(characterPtr);

	Inventory* ironSword = InventoryFactory::getInstance()->getInventory("sword001");
	ironSword->equipRightHand(characterPtr);

	Inventory* testItem0 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem1 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem2 = InventoryFactory::getInstance()->getInventory("sword001");
	Inventory* testItem3 = InventoryFactory::getInstance()->getInventory("sword001");
	

	characterPtr->addInventory(testItem0);
	characterPtr->addInventory(testItem1);
	characterPtr->addInventory(testItem2);
	characterPtr->addInventory(testItem3);

	characterPtr->addInventory("bigSword000");
	characterPtr->addInventory("sword002");
	characterPtr->addInventory("torch000");
	characterPtr->addInventory("torch000");


	//////////////////////////////////////////////////////////////////////////
	std::wstring buffname0 = L"WeightBuff_负重提高_ATTR_Good_4_20_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname0));

	std::wstring buffname1 = L"ChantBuff_自动吟唱_OnRoundStart_Good_10_20_1";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname1));

	std::wstring buffname2 = L"BlockProBuff_格挡增加_ATTR_Good_4_100_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname2));

	std::wstring buffname3 = L"EvadeBuff_闪避buff_ATTR_Good_4_100_100";
	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname3));



//	std::wstring buffname2 = L"VertigoBuff_眩晕_ATTR_Bad_2_10";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname2));


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

bool Player::isInViewSize(cocos2d::Point coord)
{
	cocos2d::Point playerCoord = characterPtr->getMapCoord();
	int dx = abs(coord.x - playerCoord.x);
	int dy = abs(coord.y - playerCoord.y);
	int d = dx + dy;
	return d < characterPtr->getViewSize();
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
			showAtkArea();
			break;
		}
		playerMove(keyCode);
		break;
	case HaltMode:
		playerSetOrientation(keyCode);
		hideAtkArea();
		showAtkArea();
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
			hideAtkArea();
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
	if (!isMoveAble(keyCode))
	{
		playerSetOrientation(keyCode);
		return;
	}
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->moveUp();
		RoundSystem::getInstance()->nextRound();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->moveDown();
		RoundSystem::getInstance()->nextRound();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->moveLeft();
		RoundSystem::getInstance()->nextRound();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->moveRight();
		RoundSystem::getInstance()->nextRound();
		break;
	}

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


std::string Player::getName()
{
	return characterPtr->getName();
}

void Player::setName(const std::string& name)
{
	CCAssert(characterPtr, "characterPtr is null");
	characterPtr->setName(name);
}

void Player::showAtkArea()
{
	std::vector<cocos2d::Point> atkCoords = characterPtr->getAtkArea();
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	for each (cocos2d::Point atkCoord in atkCoords)
	{
		cocos2d::Point atkPosition = storey->getTilePosition(atkCoord);
		cocos2d::Sprite* atkSprite = cocos2d::Sprite::create("targetArea.png");
		targetSprites.push_back(atkSprite);
		atkSprite->setPosition(atkPosition);
		MainLayer::getInstance()->addChild(atkSprite, 20);
	}
}

void Player::hideAtkArea()
{
	for each (cocos2d::Sprite* targetSprite in targetSprites)
	{
		targetSprite->removeFromParent();
	}
	targetSprites.clear();
}
