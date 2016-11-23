#include "HudBar.h"
#include "Player.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "HudLayer.h"
#include "HudLayout.h"
#include "Character.h"



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

	hpBarBk->setPosition(HudLayout::getInstance()->getHpBarPosition());
	mpBarBk->setPosition(HudLayout::getInstance()->getMpBarPosition());
	hpBar->setPosition(HudLayout::getInstance()->getHpBarPosition());
	mpBar->setPosition(HudLayout::getInstance()->getMpBarPosition());

	HudLayer::getInstance()->addChild(hpBarBk);
	HudLayer::getInstance()->addChild(hpBar);

	HudLayer::getInstance()->addChild(mpBarBk);
	HudLayer::getInstance()->addChild(mpBar);
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
}

void HudBar::show()
{
	hpBarBk->setVisible(true);
	mpBarBk->setVisible(true);
	hpBar->setVisible(true);
	mpBar->setVisible(true);
}

void HudBar::hide()
{
	hpBarBk->setVisible(false);
	mpBarBk->setVisible(false);
	hpBar->setVisible(false);
	mpBar->setVisible(false);
}
