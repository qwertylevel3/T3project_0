#include "HudLayer.h"
#include "HudNoteSystem.h"
#include "HudExchangeInventorySystem.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include "HudMenuSystem.h"
#include "HudPlayerStateMenu.h"
#include "DialogueSystem.h"
#include "HudLayout.h"
#include "HudBar.h"
#include "HudMessageBox.h"
#include "HudDescriptionMenu.h"

USING_NS_CC;

HudLayer::HudLayer()
{
}


HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	HudLayout::getInstance()->init();
	HudDescriptionMenu::getInstance()->init();
	HudMenuSystem::getInstance()->init();
	HudPlayerStateMenu::getInstance()->init();
	DialogueSystem::getInstance()->init();
	HudBar::getInstance()->init();
	HudMessageBox::getInstance()->init();
	HudExchangeInventorySystem::getInstance()->init();
	HudNoteSystem::getInstance()->init();
	




//	DialogueSystem::getInstance()->runDialogue("testDialogue");

	return true;
}

void HudLayer::update()
{
	HudMenuSystem::getInstance()->update();
	HudPlayerStateMenu::getInstance()->update();
	HudBar::getInstance()->update();
}

void HudLayer::show()
{
	HudMenuSystem::getInstance()->show();
}

void HudLayer::hide()
{
	HudMenuSystem::getInstance()->hide();
}
