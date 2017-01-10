#pragma once

#include "Singleton.h"
#include "ui/UILayout.h"
#include "ui/UIText.h"


class HudNoteSystem:public Singleton<HudNoteSystem>
{
public:
	HudNoteSystem();
	~HudNoteSystem();
	void init();
	void openNote(std::string noteID);

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void nextPage();
	void hide();
	void show();
	void setText(std::string str);
	cocos2d::ui::Text* text;
	cocos2d::ui::Layout* layout;

	std::vector<std::wstring> allText;
};

