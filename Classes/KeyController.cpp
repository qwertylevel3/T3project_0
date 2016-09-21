#include "KeyController.h"
#include "Player.h"
#include "HudMenuSystem.h"
#include "DialogueManager.h"
#include "HudStateSystem.h"
#include "OptionCheckMenu.h"
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
}

void KeyController::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if(keyCode==cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
	{
		Player::getInstance()->autoNextStep();
	}


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
		DialogueManager::getInstance()->handleKeyPressed(keyCode);
	}
	else if (control == OPTION)
	{
		OptionCheckMenu::getInstance()->handleKeyPressed(keyCode);
	}
}

void KeyController::handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (control==PLAYER)
	{
		Player::getInstance()->handleKeyReleased(keyCode);
	}
	else
	{

	}
}
void KeyController::switchCtrlToPlayer()
{
	//InventoryMenu::getInstance()->hide();
	HudMenuSystem::getInstance()->hide();
	HudStateSystem::getInstance()->hide();
	control = PLAYER;
}

void KeyController::switchCtrlToMenu()
{
	//InventoryMenu::getInstance()->show();
	HudStateSystem::getInstance()->show();
	HudMenuSystem::getInstance()->show();
	control = MENU;
}

void KeyController::switchCtrlToOption()
{
	control = OPTION;
}

void KeyController::switchCtrlToDialog()
{
	HudMenuSystem::getInstance()->hide();
	HudStateSystem::getInstance()->hide();
	control = DIALOG;
}

