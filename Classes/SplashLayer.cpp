#include "SplashLayer.h"
#include "ToolFunction.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "GameController.h"
#include "2d/CCLabel.h"

SplashLayer::SplashLayer()
{
}

SplashLayer::~SplashLayer()
{
}

bool SplashLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	black = cocos2d::Sprite::create("sys/black.png");
	black->setVisible(true);
	black->setOpacity(0);
	black->setPosition(400, 300);
	black->setScaleX(800 / black->getContentSize().width);
	black->setScaleY(600 / black->getContentSize().height);
	this->addChild(black);

	logo = cocos2d::Sprite::create("sys/logo.png");
	logo->setPosition(400, 300);
	logo->setOpacity(0);
	this->addChild(logo);

	levelMessageLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 40);
	levelMessageLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	levelMessageLabel->setOpacity(0);
	levelMessageLabel->setPosition(400, 300);
	this->addChild(levelMessageLabel);


	return true;
}

void SplashLayer::showLogo(float dt)
{
	black->setOpacity(255);

	logo->setOpacity(0);
	auto logoAction = cocos2d::FadeIn::create(dt);
	auto logoActionBack = logoAction->reverse();
	logo->runAction(
		cocos2d::Sequence::create(logoAction, logoActionBack, nullptr)
	);

	black->setOpacity(255);
	auto blackAction = cocos2d::FadeOut::create(dt);
	black->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(dt*2),
			blackAction,
			nullptr
			)
	);
}

void SplashLayer::fadeOutBlack(float dt)
{
	black->setOpacity(255);
	auto action = cocos2d::FadeOut::create(dt);
	black->runAction(
		action
	);

	levelMessageLabel->runAction(
		cocos2d::FadeOut::create(dt)
	);
}

void SplashLayer::fadeInBlack(float dt)
{
	black->setOpacity(0);
	auto action = cocos2d::FadeIn::create(dt);
	black->runAction(
		action
	);

	int curLevel = GameController::getInstance()->getCurLevel();
	levelMessageLabel->setString(
		"Floor -" + ToolFunction::int2string(curLevel)
	);

	levelMessageLabel->runAction(
		cocos2d::FadeIn::create(dt)
	);


	this->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(1),
			cocos2d::CallFunc::create(
				CC_CALLBACK_0(
					SplashLayer::startMission,this
				)
			),
			nullptr
		)
	);
}

void SplashLayer::startMission(SplashLayer* layer)
{
	GameController::getInstance()->startMission();
}