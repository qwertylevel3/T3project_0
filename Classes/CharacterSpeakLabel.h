#pragma once

#include "ui/UIScale9Sprite.h"
#include "2d/CCLabel.h"


class Character;

class CharacterSpeakLabel
{
public:
	static void hide(CharacterSpeakLabel* speakLabel);
	CharacterSpeakLabel();
	~CharacterSpeakLabel();
	void setCharacter(Character* character);
	void speak(std::wstring sentence);
	void setVisibleFalse();
protected:
	cocos2d::ui::Scale9Sprite* bk;
	cocos2d::Label* messageLabel;
	Character* characterPtr;
};

