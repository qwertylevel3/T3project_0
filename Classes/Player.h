#pragma once

#include"Character.h"
#include"Singleton.h"

class Player:public Singleton<Player>
{
public:
	enum ControlMode
	{
		MoveMode,
		StandMode,
		AttackMode
	};
	Player();
	~Player();
	void init();

	bool isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerAttack(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerMove(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerSetOrientation(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	CC_SYNTHESIZE(Character*, characterPtr, characterPtr);
	ControlMode controlMode;
};

