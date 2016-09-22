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
	void addOption(const std::string& optionLabel);
protected:
	void initHeight();
	Question* curQuestion;
};

