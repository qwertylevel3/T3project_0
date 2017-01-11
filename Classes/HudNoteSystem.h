#pragma once

#include "Singleton.h"
#include "ui/UILayout.h"
#include "ui/UIText.h"
#include "2d/CCSprite.h"
#include "NoteTextFactory.h"


class HudNoteSystem:public Singleton<HudNoteSystem>
{
public:
	HudNoteSystem();
	~HudNoteSystem();
	void init();
	void openNote(std::string noteID);
	void openNote(NoteText note);

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void nextPage();
	void previousPage();
	void hide();
	void show();
	void setText(std::string str);
	void updateFooter();
	void showLeftArrow();
	void showRightArrow();
	void hideLeftArrow();
	void hideRightArrow();
	cocos2d::ui::Text* text;
	cocos2d::ui::Text* footer;
	cocos2d::ui::Layout* layout;
	cocos2d::Sprite* leftArrow;
	cocos2d::Sprite* rightArrow;


	NoteText curNote;
	int curPageIndex;

	std::vector<std::wstring> allText;
};

