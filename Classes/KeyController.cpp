#include "KeyController.h"
#include "Player.h"
#include "RoundSystem.h"
#include "HudMenuSystem.h"
#include "DialogueSystem.h"
#include "HudPlayerStateMenu.h"
#include "OptionCheckMenu.h"
#include "HudBar.h"
#include "HudCursor.h"



KeyController::KeyController()
{
}


KeyController::~KeyController()
{
}

void KeyController::init()
{
	control = PLAYER;
	block = false;
}

void KeyController::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (block || !RoundSystem::getInstance()->isCircleOver())
	{
		return;
	}
//	if(keyCode==cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
//	{
//		Player::getInstance()->autoNextStep();
//	}


	//open or close menu
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER
		&& control==PLAYER)
	{
		switchCtrlToMenu();
		return;
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE
		&& control==MENU)
	{
		switchCtrlToPlayer();
		return;
	}


	//handle key
	if (control==PLAYER)
	{
		Player::getInstance()->handleKeyPressed(keyCode);
	}
	else if(control==MENU)
	{
		HudCursor::getInstance()->handleKeyPressed(keyCode);
		//HudMenuSystem::getInstance()->handleKeyPressed(keyCode);
	}
	else if (control == DIALOG)
	{
		DialogueSystem::getInstance()->handleKeyPressed(keyCode);
	}
	else if (control == OPTION)
	{
		HudCursor::getInstance()->handleKeyPressed(keyCode);
		//OptionCheckMenu::getInstance()->handleKeyPressed(keyCode);
	}
}

void KeyController::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (block)
	{
		return;
	}

	if (control==PLAYER)
	{
		Player::getInstance()->handleKeyReleased(keyCode);
	}
	else
	{

	}
}

void KeyController::setBlock(bool b)
{
	block = b;
}

void KeyController::switchCtrlToPlayer()
{
	//InventoryMenu::getInstance()->hide();
	HudMenuSystem::getInstance()->hide();
	HudPlayerStateMenu::getInstance()->hide();
	HudBar::getInstance()->show();
	control = PLAYER;
}

void KeyController::switchCtrlToMenu()
{
	//InventoryMenu::getInstance()->show();
	HudPlayerStateMenu::getInstance()->show();
	HudMenuSystem::getInstance()->show();
	HudBar::getInstance()->hide();
	control = MENU;
}

void KeyController::switchCtrlToOption()
{
	control = OPTION;
}

void KeyController::switchCtrlToDialog()
{
	HudMenuSystem::getInstance()->hide();
	HudPlayerStateMenu::getInstance()->hide();
	HudBar::getInstance()->hide();
	control = DIALOG;
}

