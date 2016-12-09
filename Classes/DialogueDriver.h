#pragma once

#include <map>

#include "Singleton.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include "ui/UIScale9Sprite.h"

class Dialogue;
class Sentence;
class Statement;
class Question;

class DialogueDriver:public Singleton<DialogueDriver>
{
public:
	DialogueDriver();
	~DialogueDriver();
	void init();
	void startDialogue(Dialogue* dialogue);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void endDialogue();
	void run(Statement* statement);
	void run(Question* question);
protected:
	std::map<std::string, cocos2d::Sprite* > actorSpriteBox;
	cocos2d::ui::Scale9Sprite* dialogBk;
	cocos2d::Label* textLabel;

	int nextSentence();
	int curIndex;
	Dialogue* curDialogue;
	Sentence* curSentence;
};

