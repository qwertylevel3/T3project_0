#include "HudLayer.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include "HudMenuSystem.h"
#include "HudPlayerStateMenu.h"
#include "DialogueSystem.h"
#include "HudLayout.h"
#include "HudBar.h"
#include "HudMessageBox.h"

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
	HudBar::getInstance()->init();
	HudMessageBox::getInstance()->init();
	
	HudMessageBox::getInstance()->addMessage(L"消息0");
	HudMessageBox::getInstance()->addMessage(L"消息1");
	HudMessageBox::getInstance()->addMessage(L"消息2");
	HudMessageBox::getInstance()->addMessage(L"消息3");
	HudMessageBox::getInstance()->addMessage(L"消息4");
	HudMessageBox::getInstance()->addMessage(L"消息5");
	HudMessageBox::getInstance()->addMessage(L"消息6");
	HudMessageBox::getInstance()->addMessage(L"消息7");
	HudMessageBox::getInstance()->addMessage(L"消息8");
	HudMessageBox::getInstance()->addMessage(L"消息9");


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
