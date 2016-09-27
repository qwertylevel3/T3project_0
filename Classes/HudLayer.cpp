#include "HudLayer.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include "HudMenuSystem.h"
#include "HudPlayerStateMenu.h"
#include "DialogueSystem.h"
#include "HudLayout.h"

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
	HudMenuSystem::getInstance()->init();
	HudPlayerStateMenu::getInstance()->init();
	DialogueSystem::getInstance()->init();

	DialogueSystem::getInstance()->runDialogue("testDialogue");

	return true;
}

void HudLayer::update()
{
	HudMenuSystem::getInstance()->update();
	HudPlayerStateMenu::getInstance()->update();
}

void HudLayer::show()
{
	HudMenuSystem::getInstance()->show();
}

void HudLayer::hide()
{
	HudMenuSystem::getInstance()->hide();
}
