#include "HudMenuSystem.h"
#include "ToolFunction.h"
#include "HudLayer.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "cocos2d.h"
#include "HudMainMenu.h"
#include "HudInventoryMenu.h"
#include "HudEquipMenu.h"
#include "HudDescriptionMenu.h"

HudMenuSystem::HudMenuSystem()
{
}

HudMenuSystem::~HudMenuSystem()
{
}

void HudMenuSystem::init()
{
	open = false;

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
	open = true;
}

void HudMenuSystem::hide()
{
	HudCursor::getInstance()->hide();
	HudMainMenu::getInstance()->hide();
	HudDescriptionMenu::getInstance()->hide();
	open = false;
}


void HudMenuSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}

bool HudMenuSystem::isOpen()
{
	return open;
}
