#include "KeyController.h"
#include "Player.h"
#include "HudMenuSystem.h"
#include "DialogueSystem.h"



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

void KeyController::changeControl(CurControl c)
{

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
		switchCtrlFromPlayerToMenu();
		return;
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE
		&& control==MENU)
	{
		switchCtrlFromMenuToPlayer();
		return;
	}


	//handle key
	if (control==PLAYER)
	{
		Player::getInstance()->handleKeyPressed(keyCode);
	}
	else if(control==MENU)
	{
		HudMenuSystem::getInstance()->handleKeyPressed(keyCode);
	}
	else if (control == DIALOG)
	{
		DialogueSystem::getInstance()->handleKeyPressed(keyCode);
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
void KeyController::switchCtrlFromMenuToPlayer()
{
	//InventoryMenu::getInstance()->hide();
	HudMenuSystem::getInstance()->hide();

	control = PLAYER;
}

void KeyController::switchCtrlFromPlayerToMenu()
{
	//InventoryMenu::getInstance()->show();
	HudMenuSystem::getInstance()->show();
	control = MENU;
}

void KeyController::switchCtrlFromMenuToDialog()
{
	control = DIALOG;
}

