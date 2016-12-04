#pragma once

#include "Singleton.h"
#include <string>
#include "ui/UILayout.h"
#include "ui/UIText.h"

class HudDescriptionMenu :public Singleton<HudDescriptionMenu>
{
public:
	HudDescriptionMenu();
	~HudDescriptionMenu();
	void init();
	void show();
	void hide();
	void setDescription(const std::string& des);
	void setDescription(const std::wstring& des);
protected:
	cocos2d::ui::Text* title;
	cocos2d::ui::Text*	description;
	cocos2d::ui::Layout* layout;
};
