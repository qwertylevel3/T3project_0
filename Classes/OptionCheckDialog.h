#pragma once

#include "Singleton.h"
#include <vector>
#include <string>
#include "base\ccTypes.h"
#include "base\CCEventKeyboard.h"

class HudMenu;
class Question;


class OptionCheckDialog:public Singleton<OptionCheckDialog>
{
public:
	OptionCheckDialog();
	~OptionCheckDialog();
	void init();
	void show();
	void hide();
	void clear();
	void run(Question* question);
	void choosePrevious();
	void chooseNext();
	void addOption(const std::string& optionLabel);
	void setPosition(cocos2d::Point position);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void initHeight();
	HudMenu* dialog;
	int curIndex;
	Question* curQuestion;
};

