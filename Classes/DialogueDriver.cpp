#include "DialogueDriver.h"

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
	dialogBk->setContentSize(cocos2d::Size(750, 150));
	dialogBk->setOpacity(180);
	HudLayer::getInstance()->addChild(dialogBk);
	dialogBk->setLocalZOrder(1);
	dialogBk->setVisible(false);

	dialogBk->setPosition(400, 100);

	cocos2d::CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("dialogue/dialogueActor.plist");

	Sprite* testActor0Sprite = Sprite::createWithSpriteFrameName("vergil_normal.png");
	testActor0Sprite->setVisible(false);
	testActor0Sprite->setPosition(400, 150);
	actorSpriteBox["vergil_normal.png"] = testActor0Sprite;

	HudLayer::getInstance()->addChild(testActor0Sprite);
	testActor0Sprite->setLocalZOrder(0);



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
	textLabel->setOpacity(255);

	OptionCheckMenu::getInstance()->init();
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
	actorSpriteBox[actorSpriteName]->setVisible(false);

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

	std::string actorSpriteName = curSentence->getActorSpriteName();
	actorSpriteBox[actorSpriteName]->setVisible(false);

	KeyController::getInstance()->switchCtrlToPlayer();

	if (curActor)
	{
		curActor->handleDialogueResult(curDialogue->getName(), endResult);
	}
}