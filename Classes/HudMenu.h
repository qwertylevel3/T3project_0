#pragma once

#include"Singleton.h"
class HudMenuItem;
#include <vector>
#include"2d\CCSprite.h"
#include "ui/UIListView.h"


class HudMenu
{
public:
	HudMenu(cocos2d::Rect rect=cocos2d::Rect(0,0,0,0));
	virtual ~HudMenu();
	virtual void update();

	//处理键盘按键
	virtual void handleUp();
	virtual void handleDown();
	virtual void handleLeft();
	virtual void handleRight();

	int getCurIndex();

	void show();
	void hide();

	void clear();

	void setWidth(int w);
	void setHeight(int h);
	int getWidth();
	int getHeight();

	void setPosition(int x,int y);

	void initCursor();
	virtual void addItem(HudMenuItem* item);

	void chooseItem(int index);
	void activeChildMenu(int index);
	void setParent(HudMenu* p);


	//************************************
	// Method:    closeMenu
	// FullName:  HudMenu::closeMenu
	// Access:    public 
	// Returns:   void
	// Qualifier: 关闭当前菜单，返回上级菜单
	//************************************
	void closeMenu();

	cocos2d::ui::ListView* getListView();
	int getMarginalWidth();
	int getMarginalHeight();
	void removeChild(HudMenu* c);
	void setBKImage(std::string fileName);
protected:
	void addChildMenu(HudMenu* c);
	void setCursorPosition(int index);
	void increaseIndex();
	void decreaseIndex();
	void removeFromParentMenu();

	HudMenu* parent;
	std::vector<HudMenu*> childMenu;
	//内边框距
	cocos2d::Vec2 marginal;
//	cocos2d::Sprite* sprite;
	cocos2d::ui::ListView* listView;
	cocos2d::ui::Layout* layout;
	std::vector<HudMenuItem*> itemList;
	int itemIndex;
};

