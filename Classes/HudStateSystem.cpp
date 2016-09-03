#include "HudStateSystem.h"
#include "cocos2d.h"
#include "Player.h"
#include "BattleSystem.h"
#include "ToolFunction.h"
#include "HudLayer.h"


USING_NS_CC;

HudStateSystem::HudStateSystem()
{
}


HudStateSystem::~HudStateSystem()
{
}

void HudStateSystem::init()
{
	playerNameLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(playerNameLabel);

	hpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(hpLabel);

	mpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(mpLabel);

	strLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(strLabel);
	agiLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(agiLabel);
	intLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(intLabel);

	leftAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(leftAtkLabel);
	rightAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(rightAtkLabel);
	leftCriAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(leftCriAtkLabel);
	rightCriAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(rightCriAtkLabel);
	leftCriProLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(leftCriProLabel);
	rightCriProLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(rightCriProLabel);
	leftAccuracyCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(leftAccuracyCountLabel);
	rightAccuracyCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(rightAccuracyCountLabel);

	evadeCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(evadeCountLabel);
	blockCountLable = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(blockCountLable);
	blockProCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(blockProCountLabel);
	comboProCountLable = Label::createWithTTF("", "fonts/arialuni.ttf", 18);
	HudLayer::getInstance()->addChild(comboProCountLable);

	setPosition();

	update();
}

void HudStateSystem::update()
{
	Character* playerPtr = Player::getInstance()->getcharacterPtr();

	std::string playerName = Player::getInstance()->getName();
	playerNameLabel->setString(playerName);

	std::string maxHP = ToolFunction::int2string(playerPtr->getMaxHP());
	std::string HP = ToolFunction::int2string(playerPtr->getHP());
	hpLabel->setString("HP:" + HP + "/" + maxHP);

	std::string maxMP = ToolFunction::int2string(playerPtr->getMaxMP());
	std::string MP = ToolFunction::int2string(playerPtr->getMP());
	mpLabel->setString("MP:" + MP + "/" + maxMP);

	std::string strength = ToolFunction::int2string(playerPtr->getStrength());
	strLabel->setString("strength:" + strength);

	std::string agility = ToolFunction::int2string(playerPtr->getAgility());
	agiLabel->setString("agility:" + agility);

	std::string intellect = ToolFunction::int2string(playerPtr->getIntellect());
	intLabel->setString("intellect:" + intellect);

	std::string leftAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getAttackCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftAtkLabel->setString("leftAtk:" + leftAtk);

	std::string rightAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getAttackCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightAtkLabel->setString("rightAtk:" + rightAtk);

	std::string leftCriAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalAttackCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftCriAtkLabel->setString("leftCriticalAtk:" + leftCriAtk);

	std::string rightCriAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalAttackCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightCriAtkLabel->setString("rightCriticalAtk:" + rightCriAtk);

	std::string leftCriPro = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalProCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftCriProLabel->setString("leftCriticalPro:" + leftCriPro);

	std::string rightCriPro = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalProCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightCriProLabel->setString("rightCriticalPro:" + rightCriPro);

	std::string leftAccuracuCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getAccuracyCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftAccuracyCountLabel->setString("leftAccuracy:" + leftAccuracuCount);

	std::string rightAccuracyCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getAccuracyCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightAccuracyCountLabel->setString("rightAccuracy:" + rightAccuracyCount);

	std::string evadeCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getEvadeCount(playerPtr)
	);
	evadeCountLabel->setString("evadeCount:" + evadeCount);

	std::string blockCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getBlockCount(playerPtr)
	);
	blockCountLable->setString(blockCount);

	std::string blockProCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getBlockProCount(playerPtr)
	);
	blockProCountLabel->setString(blockProCount);

	std::string comboCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getComboProCount(playerPtr)
	);
	comboProCountLable->setString(comboCount);

}

void HudStateSystem::setPosition()
{
	playerNameLabel->setPosition(100, 100);
	hpLabel->setPosition(100, 70);
	mpLabel->setPosition(100, 40);

	strLabel->setPosition(230, 100);
	agiLabel->setPosition(230, 70);
	intLabel->setPosition(230, 40);

	leftAtkLabel->setPosition(430, 100);
	rightAtkLabel->setPosition(430, 70);
	leftCriAtkLabel->setPosition(430, 40);

	rightCriAtkLabel->setPosition(630, 100);
	leftCriProLabel->setPosition(630, 70);
	rightCriProLabel->setPosition(630, 40);

//	leftAccuracyCountLabel->setPosition(230, 40);
//	rightAccuracyCountLabel->setPosition(230, 40);
}
