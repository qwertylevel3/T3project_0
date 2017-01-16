#include "Player.h"
#include "ExpHandler.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
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
#include "SkillFactory.h"
#include "MyCamera.h"

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
	faithValue = 0;
	historySize = 10;
	characterPtr = CharacterFactory::getInstance()->getCharacter("player");
	characterPtr->setAI("AIPlayer");


	configPlayer();

}

void Player::initMission()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point tempCoord = storey->getUpCoord();
	if (storey->getCharacter(tempCoord))
	{
		tempCoord = ToolFunction::findValidPlace(
			Field::Dungeon::getInstance()->getStorey(),
			tempCoord
		);
	}

	characterPtr->setMapCoord(tempCoord);


	storey->addCharacter(tempCoord, characterPtr);
}


void Player::restart()
{
	delete characterPtr;
	characterPtr = CharacterFactory::getInstance()->getCharacter("player");
	characterPtr->setAI("AIPlayer");

	configPlayer();
}

void Player::configPlayer()
{
//	characterPtr->addSkill(L"FireBall_快速火球_20_20_20_5");
//	characterPtr->addSkill(L"HPRecoverySelf_生命恢复_20_20_20");
//	characterPtr->addSkill(L"MPRecoverySelf_魔法恢复_20_20_100");
//	characterPtr->addSkill(L"HPRecoveryCast_治疗_20_20_100");
//	characterPtr->addSkill(L"MPRecoveryCast_魔法增量_20_20_100");
//	characterPtr->addSkill(L"ChantSelf_快速施法_20_0_100");
//	characterPtr->addSkill(L"BuffSelf_闪避buff_20_20_EvadeBuff_闪避buff_ATTR_Good_4_100_100");
//	characterPtr->addSkill(L"BuffCast_闪避buff祝福_20_20_EvadeBuff_闪避buff_ATTR_Good_4_100_100");
//	characterPtr->addSkill(L"Summon_召唤slime_20_20_slime");
//	characterPtr->addSkill(L"BlinkSelf_闪烁_20_10_3");
//	characterPtr->addSkill(L"Repel_击退_20_10_3_10");
//	characterPtr->addSkill(L"Thunder_闪电_20_10_-30");
//	characterPtr->addSkill(L"ExpAdd_经验增加_0_0_100");
//	characterPtr->addSkill(L"LearnSkill_学习火球术_0_0_FireBall_火球术_5_5_-20_5");
//	characterPtr->addSkill(L"BuffSelf_毒液_0_0_HPBuff_毒液_OnRoundStart_Bad_10_10_-3");

//	characterPtr->addSkill(L"RandomDirectDamage_死亡一指_10_10_-30_5_2");

	setName(ToolFunction::WStr2UTF8(L"你"));

	controlMode = NormalMode;

	characterPtr->setHP(100);
	characterPtr->setMaxHP(100);
	characterPtr->setMP(100);
	characterPtr->setMaxMP(100);

	characterPtr->setStrength(10);
	characterPtr->setAgility(10);
	characterPtr->setIntellect(10);
	characterPtr->setLuck(10);
	characterPtr->setViewSize(1);
	characterPtr->setCharacterType(Character::Good);
	characterPtr->setPlayType(Character::Player);

	//testInventory......

	Inventory* woodSword = InventoryFactory::getInstance()->getInventory("sword000");
	characterPtr->initLeftHand(woodSword);

	Inventory* armor = InventoryFactory::getInstance()->getInventory("armor000");
	characterPtr->initArmor(armor);

	characterPtr->addInventory("note000");
	characterPtr->addInventory("scroll017");
	characterPtr->addInventory("scroll003");

	characterPtr->addInventory("sword021");

	//////////////////////////////////////////////////////////////////////////
//	std::wstring buffname0 = L"WeightBuff_负重提高_ATTR_Good_4_-1_100";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname0));

//	std::wstring buffname1 = L"ChantBuff_自动吟唱_OnRoundStart_Good_10_20_1";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname1));

//	std::wstring buffname2 = L"BlockProBuff_格挡增加_ATTR_Good_4_100_100";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname2));

//	std::wstring buffname3 = L"AccuracyBuff_命中buff_ATTR_Good_4_100_100";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname3));

//	std::wstring buffname4 = L"BaseAttrBuff_测试buff_ATTR_Good_2_-1_3_0_0";
//	characterPtr->addBuff(ToolFunction::WStr2UTF8(buffname4));

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
		&& nextStep.y == startPoint.y)
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

void Player::addFaith(int value)
{
	HudMessageBox::getInstance()->addMessage(
		L"你获得了" +
		ToolFunction::string2wstring(ToolFunction::int2string(value)) +
		L"信仰值"
	);
	faithValue += value;
}

void Player::reduceFaith(int value)
{
	HudMessageBox::getInstance()->addMessage(
		L"你失去了" +
		ToolFunction::string2wstring(ToolFunction::int2string(value)) +
		L"信仰值"
	);
	faithValue -= value;
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
	if (!characterPtr->isMoveAble())
	{
		return false;
	}
	if (characterPtr->getWeight() < characterPtr->getSumWeight())
	{
		showCannotMoveReason();
		return false;
	}

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

	Storey* storey = Dungeon::getInstance()->getStorey();
	//Dungeon::getInstance()->getStorey()->isMoveAble(position);

	if (storey->isMoveAble(position))
	{
		return true;
	}
	else if (storey->isPartner(position))
	{
		return true;
	}
	return false;
}

void Player::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (controlMode)
	{
	case NormalMode:
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			playerAttack(keyCode);
			break;
		}
		if (keyCode==EventKeyboard::KeyCode::KEY_E)
		{
			playerInteraction(keyCode);
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
	characterPtr->attack();
}

void Player::playerMove(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!isMoveAble(keyCode))
	{
		playerSetOrientation(keyCode);
		return;
	}
	recodePath(characterPtr->getMapCoord());
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		characterPtr->moveUp();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(0, 32), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		characterPtr->moveDown();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(0, -32), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		characterPtr->moveLeft();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(-32, 0), 0.2);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		characterPtr->moveRight();
		MyCamera::getInstance()->moveCameraBy(cocos2d::Vec2(32, 0), 0.2);
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

void Player::playerInteraction(cocos2d::EventKeyboard::KeyCode keyCode)
{
	characterPtr->interaction();
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


std::vector<cocos2d::Point>& Player::getpathHistory()
{
	return pathHistory;
}

void Player::showCannotMoveReason()
{
	if (characterPtr->getWeight() < characterPtr->getSumWeight())
	{
		HudMessageBox::getInstance()->addMessage(
			L"负重不够！"
		);
	}
}

void Player::showAtkArea()
{
	std::vector<cocos2d::Point> atkCoords = characterPtr->getAtkArea();
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	for each (cocos2d::Point atkCoord in atkCoords)
	{
		cocos2d::Point atkPosition = storey->getTilePosition(atkCoord);
		cocos2d::Sprite* atkSprite = cocos2d::Sprite::create("sys/targetArea.png");
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

void Player::recodePath(cocos2d::Point coord)
{
	pathHistory.push_back(coord);

	if (pathHistory.size() > historySize)
	{
		pathHistory.erase(pathHistory.begin());
	}
}
