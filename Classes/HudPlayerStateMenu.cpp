#include "HudPlayerStateMenu.h"
#include "cocos2d.h"
#include "ExpHandler.h"
#include "Player.h"
#include "BattleSystem.h"
#include "ToolFunction.h"
#include "HudLayer.h"
#include "HudLayout.h"
#include "ToolFunction.h"

USING_NS_CC;

HudPlayerStateMenu::HudPlayerStateMenu()
{
}

HudPlayerStateMenu::~HudPlayerStateMenu()
{
}

void HudPlayerStateMenu::init()
{
	//	bk = Sprite::create("HUD/StateMenu.png");

	bk = cocos2d::ui::Layout::create();
	bk->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->setBackGroundImageScale9Enabled(true);
	bk->setBackGroundImage("HUD/menu.png");

	bk->setSize(
		HudLayout::getInstance()->getPlayerStateSize()
	);
	bk->setPosition(
		HudLayout::getInstance()->getPlayerStatePosition()
	);
	bk->setOpacity(180);

	HudLayer::getInstance()->addChild(bk);

	playerNameLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	playerNameLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(playerNameLabel);

	hpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	hpLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(hpLabel);

	mpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	mpLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(mpLabel);

	chantLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	chantLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(chantLabel);

	strLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	strLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(strLabel);

	agiLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	agiLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(agiLabel);

	intLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	intLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(intLabel);
	//	luckLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	//	bk->addChild(luckLabel);

	weightLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	weightLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(weightLabel);
	//	goldLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	//	bk->addChild(goldLabel);

	strExpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	strExpLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(strExpLabel);

	agiExpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	agiExpLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(agiExpLabel);

	intExpLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	intExpLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	bk->addChild(intExpLabel);
	//	luckLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	//	bk->addChild(luckLabel);



	setPosition();

	update();

	hide();
}

void HudPlayerStateMenu::update()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	//////////////////////////////////////////////////////////////////////////

	std::string playerName = Player::getInstance()->getName();
	playerNameLabel->setString(
		ToolFunction::WStr2UTF8(L"玩家名:") +
		playerName
	);

	std::string maxHP = ToolFunction::int2string(characterPtr->getMaxHP());
	std::string HP = ToolFunction::int2string(characterPtr->getHP());
	hpLabel->setString(
		ToolFunction::WStr2UTF8(L"生命值:") +
		HP + "/" + maxHP
	);

	std::string maxMP = ToolFunction::int2string(characterPtr->getMaxMP());
	std::string MP = ToolFunction::int2string(characterPtr->getMP());
	mpLabel->setString(
		ToolFunction::WStr2UTF8(L"魔法值:") +
		MP + "/" + maxMP
	);

	std::string chant = ToolFunction::int2string(characterPtr->getChant());
	chantLabel->setString(
		ToolFunction::WStr2UTF8(L"吟唱点数:") +
		chant
	);

	//////////////////////////////////////////////////////////////////////////

	std::string strength = ToolFunction::int2string(characterPtr->getStrength());
	strLabel->setString(
		ToolFunction::WStr2UTF8(L"力量:") +
		strength
	);

	std::string agility = ToolFunction::int2string(characterPtr->getAgility());
	agiLabel->setString(
		ToolFunction::WStr2UTF8(L"敏捷:") +
		agility
	);

	std::string intellect = ToolFunction::int2string(characterPtr->getIntellect());
	intLabel->setString(
		ToolFunction::WStr2UTF8(L"智力:") +
		intellect
	);

	ExpHandler* expHandler = Player::getInstance()->getcharacterPtr()->getExphandler();



	std::string strExp = ToolFunction::int2string(expHandler->getCurStrExp());
	strExpLabel->setString(
		ToolFunction::WStr2UTF8(L"str Exp:") +
		strExp
	);

	std::string agiExp = ToolFunction::int2string(expHandler->getCurAgiExp());
	agiExpLabel->setString(
		ToolFunction::WStr2UTF8(L"agi Exp:") +
		agiExp
	);

	std::string intExp = ToolFunction::int2string(expHandler->getCurIntExp());
	intExpLabel->setString(
		ToolFunction::WStr2UTF8(L"int Exp:") +
		intExp
	);


	//////////////////////////////////////////////////////////////////////////

	std::string weight = ToolFunction::int2string(characterPtr->getWeight());
	weightLabel->setString(
		ToolFunction::WStr2UTF8(L"负重:") +
		ToolFunction::int2string(characterPtr->getSumWeight()) + "/"+weight
	);

	//	std::string gold = ToolFunction::int2string(playerPtr->getGold());
	//	goldLabel->setString(gold);
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
	//	bk->setPosition(bk->getTexture()->getPixelsWide() / 2, bk->getTexture()->getPixelsHigh() / 2);

	playerNameLabel->setPosition(30, 130);
	hpLabel->setPosition(30, 100);
	mpLabel->setPosition(30, 70);
	chantLabel->setPosition(30, 40);

	strLabel->setPosition(170, 130);
	agiLabel->setPosition(170, 100);
	intLabel->setPosition(170, 70);
	weightLabel->setPosition(170, 40);

	strExpLabel->setPosition(250, 130);
	agiExpLabel->setPosition(250, 100);
	intExpLabel->setPosition(250, 70);
}