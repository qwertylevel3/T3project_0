#include "HudPlayerStateMenu.h"
#include "cocos2d.h"
#include "Player.h"
#include "BattleSystem.h"
#include "ToolFunction.h"
#include "HudLayer.h"


USING_NS_CC;

HudPlayerStateMenu::HudPlayerStateMenu()
{
}


HudPlayerStateMenu::~HudPlayerStateMenu()
{
}

void HudPlayerStateMenu::init()
{
	bk = Sprite::create("StateMenu.png");
	HudLayer::getInstance()->addChild(bk);

	playerNameLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(playerNameLabel);

	hpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(hpLabel);

	mpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(mpLabel);

	strLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(strLabel);
	agiLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(agiLabel);
	intLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(intLabel);

	leftAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(leftAtkLabel);
	rightAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(rightAtkLabel);
	leftCriAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(leftCriAtkLabel);
	rightCriAtkLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(rightCriAtkLabel);
	leftCriProLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(leftCriProLabel);
	rightCriProLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(rightCriProLabel);
	leftAccuracyCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(leftAccuracyCountLabel);
	rightAccuracyCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(rightAccuracyCountLabel);

	evadeCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(evadeCountLabel);
	blockCountLable = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(blockCountLable);
	blockProCountLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(blockProCountLabel);
	comboProCountLable = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(comboProCountLable);

	setPosition();

	update();

	hide();
}

void HudPlayerStateMenu::update()
{
	Character* playerPtr = Player::getInstance()->getcharacterPtr();

	std::string playerName = Player::getInstance()->getName();
	playerNameLabel->setString(playerName);

	std::string maxHP = ToolFunction::int2string(playerPtr->getMaxHP());
	std::string HP = ToolFunction::int2string(playerPtr->getHP());
	hpLabel->setString(HP + "/" + maxHP);

	std::string maxMP = ToolFunction::int2string(playerPtr->getMaxMP());
	std::string MP = ToolFunction::int2string(playerPtr->getMP());
	mpLabel->setString(MP + "/" + maxMP);

	std::string strength = ToolFunction::int2string(playerPtr->getStrength());
	strLabel->setString(strength);

	std::string agility = ToolFunction::int2string(playerPtr->getAgility());
	agiLabel->setString(agility);

	std::string intellect = ToolFunction::int2string(playerPtr->getIntellect());
	intLabel->setString(intellect);

	std::string leftAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getAttackCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftAtkLabel->setString(leftAtk);

	std::string rightAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getAttackCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightAtkLabel->setString(rightAtk);

	std::string leftCriAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalAttackCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftCriAtkLabel->setString(leftCriAtk);

	std::string rightCriAtk = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalAttackCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightCriAtkLabel->setString(rightCriAtk);

	std::string leftCriPro = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalProCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftCriProLabel->setString(leftCriPro);

	std::string rightCriPro = ToolFunction::int2string(
		BattleSystem::getInstance()->getCriticalProCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightCriProLabel->setString(rightCriPro);

	std::string leftAccuracuCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getAccuracyCount(playerPtr, BattleSystem::AttackHand::LeftHand)
	);
	leftAccuracyCountLabel->setString(leftAccuracuCount);

	std::string rightAccuracyCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getAccuracyCount(playerPtr, BattleSystem::AttackHand::RightHand)
	);
	rightAccuracyCountLabel->setString(rightAccuracyCount);

	std::string evadeCount = ToolFunction::int2string(
		BattleSystem::getInstance()->getEvadeCount(playerPtr)
	);
	evadeCountLabel->setString(evadeCount);

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

void HudPlayerStateMenu::show()
{
	bk->setVisible(true);
}

void HudPlayerStateMenu::hide()
{
	bk->setVisible(false);
}

void HudPlayerStateMenu::setPosition()
{
	bk->setPosition(bk->getTexture()->getPixelsWide() / 2, bk->getTexture()->getPixelsHigh() / 2);

	playerNameLabel->setPosition(100, 90);
	hpLabel->setPosition(100, 60);
	mpLabel->setPosition(100, 30);

	strLabel->setPosition(200, 90);
	agiLabel->setPosition(200, 60);
	intLabel->setPosition(200, 30);

	leftAtkLabel->setPosition(375, 78);
	leftCriAtkLabel->setPosition(375, 60);
	leftCriProLabel->setPosition(375, 40);
	leftAccuracyCountLabel->setPosition(375, 22);

	rightAtkLabel->setPosition(545, 78);
	rightCriAtkLabel->setPosition(545, 60);
	rightCriProLabel->setPosition(545, 40);
	rightAccuracyCountLabel->setPosition(545, 22);

	evadeCountLabel->setPosition(755,95);
	blockCountLable->setPosition(755,70);
	blockProCountLabel->setPosition(755,45);
	comboProCountLable->setPosition(755,20);
}
