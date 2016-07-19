#pragma once

#include<cocos2d.h>
#include"Dungeon.h"

class GameScene;

class Character
{
public:
	Character();
	~Character();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	cocos2d::Point getPosition();
	void setPosition(float x, float y);
protected:

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

	void createMoveUpAnimation();
	void createMoveDownAnimation();
	void createMoveLeftAnimation();
	void createMoveRightAnimation();

	void setMoveUpAnimation(cocos2d::CCAnimation* animation);
	void setMoveDownAnimation(cocos2d::CCAnimation* animation);
	void setMoveLeftAnimation(cocos2d::CCAnimation* animation);
	void setMoveRightAnimation(cocos2d::CCAnimation* animation);

	cocos2d::CCAnimation* moveUpAnimation;
	cocos2d::CCAnimation* moveDownAnimation;
	cocos2d::CCAnimation* moveLeftAnimation;
	cocos2d::CCAnimation* moveRightAnimation;

};