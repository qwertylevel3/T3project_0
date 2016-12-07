#include "HudBar.h"
#include "Player.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCLabel.h"
#include "HudLayer.h"
#include "HudLayout.h"
#include "Character.h"
#include "ToolFunction.h"



HudBar::HudBar()
{
}


HudBar::~HudBar()
{
}

void HudBar::init()
{

	hpBarBk = cocos2d::Sprite::create("HUD/barBk.png");
	mpBarBk = cocos2d::Sprite::create("HUD/barBk.png");
	hpBar = cocos2d::Sprite::create("HUD/HP.png");
	mpBar = cocos2d::Sprite::create("HUD/MP.png");
	hpLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	mpLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 16);

	hpBarBk->setPosition(HudLayout::getInstance()->getHpBarPosition());
	mpBarBk->setPosition(HudLayout::getInstance()->getMpBarPosition());
	hpBar->setPosition(HudLayout::getInstance()->getHpBarPosition());
	mpBar->setPosition(HudLayout::getInstance()->getMpBarPosition());
	hpLabel->setPosition(HudLayout::getInstance()->getHpBarPosition());
	mpLabel->setPosition(HudLayout::getInstance()->getMpBarPosition());

	HudLayer::getInstance()->addChild(hpBarBk);
	HudLayer::getInstance()->addChild(hpBar);

	HudLayer::getInstance()->addChild(mpBarBk);
	HudLayer::getInstance()->addChild(mpBar);

	HudLayer::getInstance()->addChild(hpLabel);
	HudLayer::getInstance()->addChild(mpLabel);

}

void HudBar::update()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();
	float hp = characterPtr->getHP();
	float maxHp = characterPtr->getMaxHP();
	float mp = characterPtr->getMP();
	float maxMp = characterPtr->getMaxMP();

	float ratioHP = hp / maxHp;
	float ratioMP = mp / maxMp;

	hpBar->setScaleX(ratioHP);
	mpBar->setScaleX(ratioMP);

	int deltaHp = (hpBarBk->getContentSize().width-hpBar->getContentSize().width*ratioHP)/2;
	int deltaMp = (mpBarBk->getContentSize().width-mpBar->getContentSize().width*ratioMP)/2;

	hpBar->setPosition(HudLayout::getInstance()->getHpBarPosition().x - deltaHp,
		HudLayout::getInstance()->getHpBarPosition().y);
	mpBar->setPosition(HudLayout::getInstance()->getMpBarPosition().x - deltaMp,
		HudLayout::getInstance()->getMpBarPosition().y);

	hpLabel->setString(
		ToolFunction::int2string(hp)+"/"+ToolFunction::int2string(maxHp)
	);
	mpLabel->setString(
		ToolFunction::int2string(mp)+"/"+ToolFunction::int2string(maxMp)
	);
}

void HudBar::show()
{
	hpBarBk->setVisible(true);
	mpBarBk->setVisible(true);
	hpBar->setVisible(true);
	mpBar->setVisible(true);
	hpLabel->setVisible(true);
	mpLabel->setVisible(true);
}

void HudBar::hide()
{
	hpBarBk->setVisible(false);
	mpBarBk->setVisible(false);
	hpBar->setVisible(false);
	mpBar->setVisible(false);
	hpLabel->setVisible(false);
	mpLabel->setVisible(false);
}
