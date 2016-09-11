#pragma once

#include "Singleton.h"
#include "base/CCEventKeyboard.h"

class KeyController:public Singleton<KeyController>
{
public:
	enum CurControl
	{
		PLAYER,MENU,DIALOG
	};
	KeyController();
	~KeyController();
	void init();
	void changeControl(CurControl c);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void switchCtrlFromMenuToPlayer();
	void switchCtrlFromPlayerToMenu();
	void switchCtrlFromMenuToDialog();
	CurControl control;
};

