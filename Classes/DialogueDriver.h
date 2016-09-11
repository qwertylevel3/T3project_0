#pragma once

#include <map>

#include "Singleton.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"

class Dialogue;
class Sentence;

class DialogueDriver:public Singleton<DialogueDriver>
{
public:
	DialogueDriver();
	~DialogueDriver();
	void init();
	int run(Dialogue* dialogue);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	std::map<std::string, cocos2d::Sprite* > actorSpriteBox;
	cocos2d::Sprite* dialogBk;
	cocos2d::Label* textLabel;
	int run(Sentence* sentence);
	void nextSentence();
};

