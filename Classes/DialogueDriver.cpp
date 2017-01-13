#include "DialogueDriver.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "HudLayer.h"
#include "Sentence.h"
#include "Question.h"
#include "Statement.h"
#include "base\ccMacros.h"
#include "Dialogue.h"
#include "KeyController.h"
#include "OptionCheckMenu.h"
#include "Character.h"

USING_NS_CC;

DialogueDriver::DialogueDriver()
{
}

DialogueDriver::~DialogueDriver()
{
}

void DialogueDriver::init()
{
	curIndex = 0;
	curDialogue = nullptr;

	dialogBk = cocos2d::ui::Scale9Sprite::create("HUD/menu.png");
	dialogBk->setScale9Enabled(true);
	dialogBk->setContentSize(cocos2d::Size(810, 160));
	dialogBk->setOpacity(180);
	HudLayer::getInstance()->addChild(dialogBk);
	dialogBk->setLocalZOrder(1);
	dialogBk->setVisible(false);

	dialogBk->setPosition(400,70);

	cocos2d::CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("dialogue/dialogueActor.plist");

	//////////////////////////////////////////////////////////////////////////

//	Sprite* testActor0Sprite = Sprite::createWithSpriteFrameName("vergil1.png");
//	testActor0Sprite->setVisible(false);
//	testActor0Sprite->setPosition(400, 150);
//	actorSpriteBox["vergil1.png"] = testActor0Sprite;
//	HudLayer::getInstance()->addChild(testActor0Sprite);
//	testActor0Sprite->setLocalZOrder(0);

//	Sprite* testActor1Sprite = Sprite::createWithSpriteFrameName("vergil2.png");
//	testActor1Sprite->setVisible(false);
//	testActor1Sprite->setPosition(400, 150);
//	actorSpriteBox["vergil2.png"] = testActor1Sprite;
//	HudLayer::getInstance()->addChild(testActor1Sprite);
//	testActor1Sprite->setLocalZOrder(0);

	//////////////////////////////////////////////////////////////////////////

	textLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 24);
	textLabel->setVisible(false);
	HudLayer::getInstance()->addChild(textLabel);
	textLabel->setLocalZOrder(3);
	textLabel->setPosition(450, 95);
	textLabel->setAlignment(CCTextAlignment::LEFT, CCVerticalTextAlignment::TOP);
	textLabel->setWidth(600);
	textLabel->setHeight(24 * 4);
	textLabel->setMaxLineWidth(600);
	textLabel->setLineBreakWithoutSpace(false);
	textLabel->enableShadow();
	textLabel->setOpacity(255);

	enterSprite = cocos2d::Sprite::create("sys/enter.png");
	HudLayer::getInstance()->addChild(enterSprite);
	enterSprite->setPosition(700, 50);
	enterSprite->setVisible(false);


	OptionCheckMenu::getInstance()->init();
}

void DialogueDriver::run(Statement* statement)
{
	std::string actorSpriteName = statement->getActorSpriteName();
	std::string word = statement->getWord();

	//	actorSpriteBox[actorSpriteName]->setVisible(true);


	if (actorSpriteName != "NULL")
	{
		actorSprite = Sprite::createWithSpriteFrameName(actorSpriteName);
		actorSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
//		actorSprite->setPosition(75, 100);
		actorSprite->getTexture()->setAliasTexParameters();


		HudLayer::getInstance()->addChild(actorSprite);
		actorSprite->setLocalZOrder(2);
	}
	else
	{
		actorSprite = Sprite::create();
		HudLayer::getInstance()->addChild(actorSprite);
	}

	dialogBk->setVisible(true);
	textLabel->setVisible(true);
	textLabel->setString(word);

	enterSprite->setLocalZOrder(3);
	enterSprite->stopAllActions();
	enterSprite->setVisible(true);
	enterSprite->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::Sequence::create(
				cocos2d::MoveBy::create(1,cocos2d::Vec2(0,-5)),
				cocos2d::MoveBy::create(0.01,cocos2d::Vec2(0,5)),
				NULL
			)
		)
	);
}

void DialogueDriver::run(Question* question)
{
	std::string actorSpriteName = question->getActorSpriteName();
	std::string word = question->getWord();

	//	actorSpriteBox[actorSpriteName]->setVisible(true);

	if (actorSpriteName != "NULL")
	{
		actorSprite = Sprite::createWithSpriteFrameName(actorSpriteName);
		actorSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
//		actorSprite->setPosition(75, 100);
		actorSprite->getTexture()->setAliasTexParameters();


		HudLayer::getInstance()->addChild(actorSprite);
		actorSprite->setLocalZOrder(2);
	}
	else
	{
		actorSprite = Sprite::create();
		HudLayer::getInstance()->addChild(actorSprite);
	}

	dialogBk->setVisible(true);
	textLabel->setVisible(true);
	textLabel->setString(word);

	OptionCheckMenu::getInstance()->clear();
	OptionCheckMenu::getInstance()->run(question);
}

void DialogueDriver::startDialogue(Dialogue* dialogue)
{
	curIndex = 1;
	curDialogue = dialogue;
	curSentence = dialogue->getSentence(curIndex);
	curSentence->run();
}

int DialogueDriver::nextSentence()
{
	std::string actorSpriteName = curSentence->getActorSpriteName();
	//	actorSpriteBox[actorSpriteName]->setVisible(false);
	actorSprite->removeFromParent();

	curIndex = curSentence->next();
	if (curIndex < 0)
	{
		return curIndex;
	}
	curSentence = curDialogue->getSentence(curIndex);
	curSentence->run();
	return curIndex;
}

void DialogueDriver::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
	{
		int nextIndex = nextSentence();
		if (nextIndex < 0)
		{
			endDialogue(nextIndex);
		}
	}
}

void DialogueDriver::setCurActor(Character* actor)
{
	curActor = actor;
}

void DialogueDriver::endDialogue(int endResult)
{
	dialogBk->setVisible(false);
	textLabel->setVisible(false);
	enterSprite->setVisible(false);

	std::string actorSpriteName = curSentence->getActorSpriteName();
	//	actorSpriteBox[actorSpriteName]->setVisible(false);
	//	actorSprite->removeFromParent();

	KeyController::getInstance()->switchCtrlToPlayer();

	if (curActor)
	{
		curActor->handleDialogueResult(curDialogue->getName(), endResult);
	}
}