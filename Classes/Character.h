#pragma once

#include<cocos2d.h>
#include"Dungeon.h"

class GameScene;

class Character
{
public:
	static Character* create(const std::string& filename);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	cocos2d::Point getPosition();
	void setPosition(float x, float y);
protected:
	Character();
	~Character();
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

	cocos2d::CCSpriteFrameCache * cache;


	void setFrameCache(std::string filename);

	void createMoveUpAnimation();
	void createMoveDownAnimation();
	void createMoveLeftAnimation();
	void createMoveRightAnimation();


	cocos2d::CCAnimation* moveUpAnimation;
	cocos2d::CCAnimation* moveDownAnimation;
	cocos2d::CCAnimation* moveLeftAnimation;
	cocos2d::CCAnimation* moveRightAnimation;
	cocos2d::CCAnimation* stopUpAnimation;
	cocos2d::CCAnimation* stopDownAnimation;
	cocos2d::CCAnimation* stopLeftAnimation;
	cocos2d::CCAnimation* stopRightAnimation;

};