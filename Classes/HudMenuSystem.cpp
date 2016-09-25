#include "HudMenuSystem.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "cocos2d.h"
#include "HudMainMenu.h"
#include "HudInventoryMenu.h"
#include "HudEquipMenu.h"



HudMenuSystem::HudMenuSystem()
{
}


HudMenuSystem::~HudMenuSystem()
{
}

void HudMenuSystem::init()
{
	windowSize = cocos2d::Director::getInstance()->getWinSize();

	HudMainMenu::getInstance()->init();

	HudCursor::getInstance()->setCurMenu(HudMainMenu::getInstance());
	hide();
}

void HudMenuSystem::update()
{

}

void HudMenuSystem::show()
{
	HudCursor::getInstance()->setCurMenu(HudMainMenu::getInstance());
	HudCursor::getInstance()->show();
	HudMainMenu::getInstance()->show();
}

void HudMenuSystem::hide()
{
	HudCursor::getInstance()->hide();
	HudMainMenu::getInstance()->hide();
	HudInventoryMenu::getInstance()->hide();
	HudEquipMenu::getInstance()->hide();
}

void HudMenuSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}

