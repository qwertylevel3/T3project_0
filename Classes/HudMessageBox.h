#pragma once

#include "Singleton.h"
#include <vector>

namespace cocos2d
{
	class Label;
	class Sprite;
}

class HudMessageBox:public Singleton<HudMessageBox>
{
public:
	HudMessageBox();
	~HudMessageBox();
	void init();
	void update();
	void show();
	void hide();
	void addMessage(std::wstring message);
	void addMessage(std::string message);
protected:
	void formatMessageBox();

	cocos2d::Sprite* bk;
	std::vector<cocos2d::Label*> messageBox;

	//保存的最大数目
	int maxMessageNumber;
};

