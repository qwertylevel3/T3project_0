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
	void startDialogue(Dialogue* dialogue);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void endDialogue();
protected:
	std::map<std::string, cocos2d::Sprite* > actorSpriteBox;
	cocos2d::Sprite* dialogBk;
	cocos2d::Label* textLabel;
	void run(Sentence* sentence);
	int nextSentence();
	int curIndex;
	Dialogue* curDialogue;
	Sentence* curSentence;
};

