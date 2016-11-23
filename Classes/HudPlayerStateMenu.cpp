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
	bk = Sprite::create("HUD/StateMenu.png");
	HudLayer::getInstance()->addChild(bk);

	playerNameLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(playerNameLabel);
	hpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(hpLabel);
	mpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(mpLabel);
	chantLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(chantLabel);



	strLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(strLabel);
	agiLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(agiLabel);
	intLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(intLabel);
	luckLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(luckLabel);

	weightLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(weightLabel);
	goldLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	bk->addChild(goldLabel);



	setPosition();

	update();

	hide();
}

void HudPlayerStateMenu::update()
{
	Character* playerPtr = Player::getInstance()->getcharacterPtr();

	//////////////////////////////////////////////////////////////////////////

	std::string playerName = Player::getInstance()->getName();
	playerNameLabel->setString(playerName);

	std::string maxHP = ToolFunction::int2string(playerPtr->getMaxHP());
	std::string HP = ToolFunction::int2string(playerPtr->getHP());
	hpLabel->setString(HP + "/" + maxHP);

	std::string maxMP = ToolFunction::int2string(playerPtr->getMaxMP());
	std::string MP = ToolFunction::int2string(playerPtr->getMP());
	mpLabel->setString(MP + "/" + maxMP);

	std::string chant = ToolFunction::int2string(playerPtr->getChant());
	chantLabel->setString(chant);

	//////////////////////////////////////////////////////////////////////////

	std::string strength = ToolFunction::int2string(playerPtr->getStrength());
	strLabel->setString(strength);

	std::string agility = ToolFunction::int2string(playerPtr->getAgility());
	agiLabel->setString(agility);

	std::string intellect = ToolFunction::int2string(playerPtr->getIntellect());
	intLabel->setString(intellect);

	std::string luck = ToolFunction::int2string(playerPtr->getLuck());
	luckLabel->setString(luck);

	//////////////////////////////////////////////////////////////////////////

	std::string weight = ToolFunction::int2string(playerPtr->getWeight());
	weightLabel->setString(weight);

	std::string gold = ToolFunction::int2string(playerPtr->getGold());
	goldLabel->setString(gold);

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

	playerNameLabel->setPosition(100, 100);
	hpLabel->setPosition(100, 70);
	mpLabel->setPosition(100, 45);
	chantLabel->setPosition(100, 20);

	strLabel->setPosition(230, 100);
	agiLabel->setPosition(230, 70);
	intLabel->setPosition(230, 45);
	luckLabel->setPosition(230, 20);

	goldLabel->setPosition(350, 100);
	weightLabel->setPosition(350, 70);
}
