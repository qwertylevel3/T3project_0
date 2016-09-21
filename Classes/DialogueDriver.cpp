#include "DialogueDriver.h"

#include "HudLayer.h"
#include "Sentence.h"
#include "Question.h"
#include "Statement.h"
#include "base\ccMacros.h"
#include "Dialogue.h"
#include "KeyController.h"
#include "OptionCheckDialog.h"

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

	dialogBk = cocos2d::Sprite::create("menu.png",cocos2d::Rect(0,0,740,150));
	HudLayer::getInstance()->addChild(dialogBk);
	dialogBk->setLocalZOrder(1);
	dialogBk->setVisible(false);


	dialogBk->setPosition(400, 100);

	cocos2d::CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("actor.plist");
	
	Sprite* testActor0Sprite = Sprite::createWithSpriteFrameName("testActor0.png");
	Sprite* testActor1Sprite = Sprite::createWithSpriteFrameName("testActor1.png");

	testActor0Sprite->setVisible(false);
	testActor1Sprite->setVisible(false);
	testActor0Sprite->setPosition(400, 300);
	testActor1Sprite->setPosition(400, 300);

	actorSpriteBox["testActor0.png"] = testActor0Sprite;
	actorSpriteBox["testActor1.png"] = testActor1Sprite;

	HudLayer::getInstance()->addChild(testActor0Sprite);
	HudLayer::getInstance()->addChild(testActor1Sprite);

	testActor0Sprite->setLocalZOrder(0);
	testActor1Sprite->setLocalZOrder(0);

	textLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 24);
	textLabel->setVisible(false);
	HudLayer::getInstance()->addChild(textLabel);
	textLabel->setLocalZOrder(3);
	textLabel->setPosition(400, 100);
	textLabel->setAlignment(CCTextAlignment::LEFT, CCVerticalTextAlignment::TOP);
	textLabel->setWidth(700);
	textLabel->setHeight(24 * 4);
	textLabel->setMaxLineWidth(700);
	textLabel->setLineBreakWithoutSpace(false);
	textLabel->enableShadow();

	OptionCheckDialog::getInstance()->init();
}


void DialogueDriver::run(Statement* statement)
{
	std::string actorSpriteName = statement->getActorSpriteName();
	std::string word = statement->getWord();

	actorSpriteBox[actorSpriteName]->setVisible(true);
	dialogBk->setVisible(true);
	textLabel->setVisible(true);
	textLabel->setString(word);
}

void DialogueDriver::run(Question* question)
{
	std::string actorSpriteName = question->getActorSpriteName();
	std::string word = question->getWord();

	actorSpriteBox[actorSpriteName]->setVisible(true);
	dialogBk->setVisible(true);
	textLabel->setVisible(true);
	textLabel->setString(word);

	OptionCheckDialog::getInstance()->clear();
	OptionCheckDialog::getInstance()->run(question);
}

void DialogueDriver::startDialogue(Dialogue* dialogue)
{
	curIndex = 0;
	curDialogue = dialogue;
	curSentence = dialogue->getSentence(curIndex);
	curSentence->run();
}

int DialogueDriver::nextSentence()
{
	std::string actorSpriteName = curSentence->getActorSpriteName();
	actorSpriteBox[actorSpriteName]->setVisible(false);

	curIndex = curSentence->next();
	if (curIndex<0)
	{
		return curIndex;
	}
	curSentence = curDialogue->getSentence(curIndex);
	curSentence->run();
	return curIndex;
}

void DialogueDriver::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode==cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
	{
		if (nextSentence() < 0)
		{
			endDialogue();
		}
	}
}

void DialogueDriver::endDialogue()
{
	dialogBk->setVisible(false);
	textLabel->setVisible(false);

	std::string actorSpriteName = curSentence->getActorSpriteName();
	actorSpriteBox[actorSpriteName]->setVisible(false);

	KeyController::getInstance()->switchCtrlToPlayer();
}
