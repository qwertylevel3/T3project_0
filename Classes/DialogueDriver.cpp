#include "DialogueDriver.h"

#include "HudLayer.h"
#include "Sentence.h"

USING_NS_CC;


DialogueDriver::DialogueDriver()
{
}


DialogueDriver::~DialogueDriver()
{
}

void DialogueDriver::init()
{
	dialogBk = cocos2d::Sprite::create("menu.png",cocos2d::Rect(0,0,600,120));
	HudLayer::getInstance()->addChild(dialogBk);
	dialogBk->setVisible(false);
	cocos2d::CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("actor.plist");
	
	Sprite* testActor0Sprite = Sprite::createWithSpriteFrameName("testActor0.png");
	Sprite* testActor1Sprite = Sprite::createWithSpriteFrameName("testActor1.png");

	testActor0Sprite->setVisible(false);
	testActor1Sprite->setVisible(false);

	actorSpriteBox["testActor0.png"] = testActor0Sprite;
	actorSpriteBox["testActor1.png"] = testActor1Sprite;

	HudLayer::getInstance()->addChild(testActor0Sprite);
	HudLayer::getInstance()->addChild(testActor1Sprite);

	textLabel = Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	textLabel->setVisible(false);
}

void DialogueDriver::run(Sentence* sentence)
{
	std::string actorSpriteName = sentence->getActorSpriteName();
	std::string word = sentence->getWord();

	actorSpriteBox[actorSpriteName]->setVisible(true);
	dialogBk->setVisible(true);
	textLabel->setString(word);

}
