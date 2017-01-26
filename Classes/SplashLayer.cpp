#include "SplashLayer.h"
#include "RandomNumber.h"
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
	white = cocos2d::Sprite::create("sys/white.png");
	white->setVisible(true);
	white->setOpacity(0);
	white->setPosition(400, 300);
	white->setScaleX(800 / white->getContentSize().width);
	white->setScaleY(600 / white->getContentSize().height);
	this->addChild(white);

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

	title = cocos2d::Sprite::create("sys/title.png");
	title->setPosition(400, 300);
	title->setOpacity(0);
	this->addChild(title);

	starSky = cocos2d::Sprite::create("sys/starSky.png");
	starSky->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	starSky->setPosition(0, 0);
	starSky->setOpacity(0);
	this->addChild(starSky);

	levelMessageLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 40);
	levelMessageLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	levelMessageLabel->setOpacity(0);
	levelMessageLabel->setPosition(400, 300);
	this->addChild(levelMessageLabel);

	return true;
}

void SplashLayer::startGame(float dt)
{
	black->setOpacity(255);

	//logo淡入淡出
	logo->setOpacity(0);
	auto logoAction = cocos2d::FadeIn::create(dt);
	auto logoActionBack = logoAction->reverse();
	logo->runAction(
		cocos2d::Sequence::create(logoAction, logoActionBack, nullptr)
	);

	//title淡入淡出
	title->setOpacity(0);
	auto titleAction = cocos2d::FadeIn::create(dt);
	auto titleActionBack = titleAction->reverse();
	title->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(dt * 2),
			cocos2d::Sequence::create(titleAction, titleActionBack, nullptr),
			cocos2d::CallFunc::create(
				CC_CALLBACK_0(
					SplashLayer::fadeoutBlackAndStart, this
				)
			),
			NULL
		)
	);
}

void SplashLayer::fadeOutBlackAndFloorNumber(float dt)
{
	fadeOutBlack(dt);
	fadeOutFloorNumber(dt);
}

void SplashLayer::nextMission(float dt)
{
	fadeInBlack(dt);
	fadeInFloorNumber(dt);

	this->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(1),
			cocos2d::CallFunc::create(
				CC_CALLBACK_0(
					SplashLayer::startMission, this
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

void SplashLayer::fadeInBlack(float dt)
{
	black->setOpacity(0);
	auto action = cocos2d::FadeIn::create(dt);
	black->runAction(
		action
	);
}

void SplashLayer::fadeInFloorNumber(float dt)
{
	int curLevel = GameController::getInstance()->getCurLevel();
	levelMessageLabel->setString(
		"FLOOR -" + ToolFunction::int2string(curLevel)
	);

	levelMessageLabel->runAction(
		cocos2d::FadeIn::create(dt)
	);
}

void SplashLayer::fadeOutFloorNumber(float dt)
{
	levelMessageLabel->runAction(
		cocos2d::FadeOut::create(dt)
	);
}

void SplashLayer::fadeOutBlack(float dt)
{
	black->setOpacity(255);
	auto action = cocos2d::FadeOut::create(dt);
	black->runAction(
		action
	);
}

void SplashLayer::fadeoutBlackAndStart(SplashLayer* layer)
{
	//	layer->fadeOutBlackAndFloorNumber(2);
	layer->showBlackAndFloorNumberAndStart(1.5);
}

void SplashLayer::fadeInWhite(float dt)
{
	white->setOpacity(0);
	auto action = cocos2d::FadeIn::create(dt);
	white->runAction(
		action
	);
}

void SplashLayer::clearGame()
{
	white->setOpacity(0);

	white->runAction(
		cocos2d::Sequence::create(
			cocos2d::FadeIn::create(2),
			cocos2d::DelayTime::create(9.9),
			cocos2d::FadeOut::create(0.1),
			NULL
		)

	);

	for (int i = 0; i < 20; i++)
	{
		cocos2d::Sprite* star = cocos2d::Sprite::create("sys/star.png");

		int x = RandomNumber::getInstance()->randomInt(50, 750);
		int y = RandomNumber::getInstance()->randomInt(400, 750);

		star->setPosition(x, y);

		starSky->addChild(star);

		int delay = RandomNumber::getInstance()->randomInt(1, 10);

		double delayTime = double(delay) / 10.0;

		star->runAction(
			cocos2d::RepeatForever::create(
				cocos2d::Sequence::create(
					cocos2d::DelayTime::create(delayTime),
					cocos2d::FadeOut::create(0.5),
					cocos2d::FadeIn::create(0.5),
					NULL
				)
			)
		);
	}

	starSky->setOpacity(0);
	starSky->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(2),
			cocos2d::Spawn::create(
				cocos2d::Sequence::create(
					cocos2d::FadeIn::create(5),
					cocos2d::DelayTime::create(5),
					NULL
				),
				cocos2d::MoveBy::create(10, cocos2d::Vec2(0, -200)),
				NULL
			),
			NULL
		)

	);
}

void SplashLayer::showBlackAndFloorNumberAndStart(float dt)
{
	black->setOpacity(255);
	black->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(dt),
			cocos2d::FadeOut::create(dt),
			NULL
		)
	);

	int curLevel = GameController::getInstance()->getCurLevel();
	levelMessageLabel->setString(
		"FLOOR -" + ToolFunction::int2string(curLevel)
	);

	levelMessageLabel->runAction(
		cocos2d::Sequence::create(
			cocos2d::FadeIn::create(dt),
			cocos2d::FadeOut::create(dt - 0.3),
			cocos2d::CallFunc::create(
				CC_CALLBACK_0(
					SplashLayer::startDialogue, this
				)
			),
			NULL
		)
	);
}

void SplashLayer::startDialogue(SplashLayer* layer)
{
	GameController::getInstance()->runStartDialogue();
}

void SplashLayer::reStartGame(float dt)
{
	starSky->stopAllActions();
	starSky->setOpacity(0);
	starSky->setPosition(0, 0);
	starSky->removeAllChildren();

	black->stopAllActions();
	black->setOpacity(255);

	//title淡入淡出
	title->setOpacity(0);
	auto titleAction = cocos2d::FadeIn::create(dt);
	auto titleActionBack = titleAction->reverse();
	title->runAction(
		cocos2d::Sequence::create(
			cocos2d::Sequence::create(titleAction, titleActionBack, nullptr),
			cocos2d::CallFunc::create(
				CC_CALLBACK_0(
					SplashLayer::fadeoutBlackAndStart, this
				)
			),
			NULL
		)
	);
}

void SplashLayer::showBlack()
{
	black->setOpacity(255);
}