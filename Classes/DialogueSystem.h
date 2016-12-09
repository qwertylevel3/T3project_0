#pragma once

#include "Singleton.h"
#include <string>
#include "base/CCEventKeyboard.h"

class Character;

class DialogueSystem:public Singleton<DialogueSystem>
{
public:
	DialogueSystem();
	~DialogueSystem();
	void init();
	void runDialogue(const std::string& dialogueName,Character* actor=nullptr);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void setCurActor(Character* actor);
};

