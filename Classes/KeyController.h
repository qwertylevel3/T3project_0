#pragma once

#include "Singleton.h"
#include "base/CCEventKeyboard.h"

class KeyController:public Singleton<KeyController>
{
public:
	enum CurControl
	{
		PLAYER,MENU,DIALOG,OPTION
	};
	KeyController();
	~KeyController();
	void init();
	void switchCtrlToDialog();
	void switchCtrlToPlayer();
	void switchCtrlToMenu();
	void switchCtrlToOption();

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	void setBlock(bool b);
protected:
	bool block;

	CurControl control;
};

