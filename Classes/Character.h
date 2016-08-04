#pragma once

#include<cocos2d.h>
#include"Dungeon.h"
#include<map>
#include"Skill.h"

class GameScene;
class Inventory;

class Character
{
public:
	enum Orientation
	{
		UP,DOWN,LEFT,RIGHT
	};
	Character();
	~Character();

	bool isMoveAble(cocos2d::Point position);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setOrientationUp();
	void setOrientationDown();
	void setOrientationLeft();
	void setOrientationRight();

	cocos2d::Point getPosition();
	void setPosition(float x, float y);

	cocos2d::Node* getParent();

	void runSkill(std::string skillName);

	void addInventory(Inventory* inventory);
	std::vector<Inventory*>& getInventoryList();
protected:
	//Skill......
	std::map<std::string, Skill*> skillBox;

	//Inventory......
	std::vector<Inventory*> inventoryList;

	//attribute......
	CC_SYNTHESIZE(cocos2d::Point, mapCoord, MapCoord);
	CC_SYNTHESIZE(int, strength, Strength);
	CC_SYNTHESIZE(int, intellect, Intellect);
	CC_SYNTHESIZE(int, agility, Agility);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, MP, MP);
	CC_SYNTHESIZE(int, curHP, CurHP);
	CC_SYNTHESIZE(int, curMP, CurMP);
	CC_SYNTHESIZE(Field::Dungeon*, dungeon, Dungeon);
	CC_SYNTHESIZE(GameScene*, scene, Scene);
	CC_SYNTHESIZE(cocos2d::CCSprite*, sprite, Sprite);
	CC_SYNTHESIZE(Orientation, orientation, Orientation);

	//Animation......
	void setMoveUpAnimation(cocos2d::CCAnimation* animation);
	void setMoveDownAnimation(cocos2d::CCAnimation* animation);
	void setMoveLeftAnimation(cocos2d::CCAnimation* animation);
	void setMoveRightAnimation(cocos2d::CCAnimation* animation);

	void setStandUpAnimation(cocos2d::CCAnimation* animation);
	void setStandDownAnimation(cocos2d::CCAnimation* animation);
	void setStandLeftAnimation(cocos2d::CCAnimation* animation);
	void setStandRightAnimation(cocos2d::CCAnimation* animation);

	cocos2d::CCAnimation* moveUpAnimation;
	cocos2d::CCAnimation* moveDownAnimation;
	cocos2d::CCAnimation* moveLeftAnimation;
	cocos2d::CCAnimation* moveRightAnimation;

	cocos2d::CCAnimation* standUpAnimation;
	cocos2d::CCAnimation* standDownAnimation;
	cocos2d::CCAnimation* standLeftAnimation;
	cocos2d::CCAnimation* standRightAnimation;
};
