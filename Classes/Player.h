#pragma once

#include"Character.h"
#include"Singleton.h"

class Player:public Singleton<Player>
{
public:
	enum ControlMode
	{
		NormalMode,
		HaltMode
	};
	Player();
	~Player();
	void init();
	//test...
	void autoNextStep();

	bool isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerAttack(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerMove(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerSetOrientation(cocos2d::EventKeyboard::KeyCode keyCode);
	std::vector<Inventory*>& getInventoryList();
protected:
	CC_SYNTHESIZE(Character*, characterPtr, characterPtr);
	ControlMode controlMode;

};

