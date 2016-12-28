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
	void initMission();




	//test...
	void autoNextStep();

	bool isInViewSize(cocos2d::Point coord);
	bool isMoveAble(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerAttack(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerMove(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerSetOrientation(cocos2d::EventKeyboard::KeyCode keyCode);
	void playerInteraction(cocos2d::EventKeyboard::KeyCode keyCode);
	std::string getName();
	void setName(const std::string& name);
protected:
	void showCannotMoveReason();
	void showAtkArea();
	void hideAtkArea();
	CC_SYNTHESIZE(Character*, characterPtr, characterPtr);

	ControlMode controlMode;

	std::vector<cocos2d::Sprite*> targetSprites;
};

