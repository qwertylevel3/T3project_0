#include "KeyController.h"
#include "Player.h"
#include "HudLayer.h"



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
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER
		&& control==PLAYER)
	{
		switchControlToHud();
		return;
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE
		&& control!=PLAYER)
	{
		switchControlToPlayer();
		return;
	}
	if (control==PLAYER)
	{
		Player::getInstance()->handleKeyPressed(keyCode);
	}
	else
	{
		HudLayer::getInstance()->handleKeyPressed(keyCode);
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
void KeyController::switchControlToPlayer()
{
	//InventoryMenu::getInstance()->hide();
	HudLayer::getInstance()->hide();
	control = PLAYER;
}

void KeyController::switchControlToHud()
{
	//InventoryMenu::getInstance()->show();
	HudLayer::getInstance()->show();
	control = HUD;
}


