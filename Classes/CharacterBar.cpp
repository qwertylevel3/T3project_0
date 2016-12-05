#include "CharacterBar.h"
#include "2d/CCSprite.h"
#include "Character.h"

CharacterBar::CharacterBar()
{
	characterPtr = nullptr;
}

CharacterBar::~CharacterBar()
{
}

void CharacterBar::update()
{
	if (!characterPtr)
	{
		return;
	}


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

	hpBar->setPosition(hpBarBk->getPosition().x- deltaHp,
		hpBarBk->getPosition().y);
	mpBar->setPosition(mpBarBk->getPosition().x- deltaMp,
		mpBarBk->getPosition().y);
}

void CharacterBar::setCharacter(Character* character)
{
	characterPtr = character;

	hpBarBk = cocos2d::Sprite::create("character/barBk.png");
	mpBarBk = cocos2d::Sprite::create("character/barBk.png");
	hpBar = cocos2d::Sprite::create("character/HP.png");
	mpBar = cocos2d::Sprite::create("character/MP.png");

//	hpBar->retain();
//	hpBarBk->retain();
//	mpBar->retain();
//	mpBarBk->retain();

	//	hpBarBk->setPosition();
	//	mpBarBk->setPosition(HudLayout::getInstance()->getMpBarPosition());
	//	hpBar->setPosition(HudLayout::getInstance()->getHpBarPosition());
	//	mpBar->setPosition(HudLayout::getInstance()->getMpBarPosition());

	character->getSprite()->addChild(hpBarBk);
	character->getSprite()->addChild(hpBar);
	character->getSprite()->addChild(mpBarBk);
	character->getSprite()->addChild(mpBar);

	hpBar->setPosition(16, 20+16);
	hpBarBk->setPosition(16, 20+16);
	mpBar->setPosition(16, 17+16);
	mpBarBk->setPosition(16, 17+16);

	hpBar->setOpacity(180);
	mpBar->setOpacity(180);
	hpBarBk->setOpacity(180);
	mpBarBk->setOpacity(180);
}
