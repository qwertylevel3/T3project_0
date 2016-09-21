#pragma once

#include "Singleton.h"
#include <vector>
#include <string>
#include "base\ccTypes.h"
#include "base\CCEventKeyboard.h"
#include "HudMenu.h"

class Question;


class OptionCheckMenu:public HudMenu,public Singleton<OptionCheckMenu>
{
public:
	OptionCheckMenu();
	~OptionCheckMenu();

	virtual void handleUp();
	virtual void handleDown();
	virtual void handleRight();

	void show();
	void hide();
	void init();
	void run(Question* question);
	void choosePrevious();
	void chooseNext();
	void addOption(const std::string& optionLabel);
	void setPosition(cocos2d::Point position);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void initHeight();
	int curIndex;
	Question* curQuestion;
};

