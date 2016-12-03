#pragma once


//#include "extensions/cocos-ext.h"

#include "ui/UIListView.h"

#include "Singleton.h"


class MainMenu:public Singleton<MainMenu>
{
public:
	MainMenu();
	~MainMenu();
	void init();
	void show();
	void hide();
protected:
	cocos2d::ui::ListView* listView;
};

