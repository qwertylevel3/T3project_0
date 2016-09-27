#pragma once

#include<cocos2d.h>
#include<map>
#include"Skill.h"
#include <vector>

class GameScene;
class Inventory;
class InventoryInHand;
class Armor;
class Accessory;
class AIBase;
class InventoryHandler;

class Character
{
public:
	enum Type
	{
		Good, Neutral, Bad
	};
	enum Orientation
	{
		UP, DOWN, LEFT, RIGHT
	};
	Character();
	~Character();
	void update();

	void sufferDamage(int damage);

	//************************************
	// Method:    die
	// FullName:  Character::die
	// Access:    public 
	// Returns:   void
	// Qualifier: 这里不将该character从storey中移除。移除的工作由storey统一负责
	//************************************
	void die();
	bool isDead();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setOrientationUp();
	void setOrientationDown();
	void setOrientationLeft();
	void setOrientationRight();
	void showMoveUpAnimation();
	void showMoveDownAnimation();
	void showMoveLeftAnimation();
	void showMoveRightAnimation();

	void equipLeftHand(Inventory* inventory);
	void equipRightHand(Inventory* inventory);
	void equipArmor(Inventory* inventory);
	void equipAccessory(Inventory* inventory);

	void unequipLeftHand();
	void unequipRightHand();
	void unequipArmor();
	void unequipAccessory();



	//************************************
	// Method:    getLeftHandAtkArea
	// FullName:  Character::getLeftHandAtkArea
	// Access:    public 
	// Returns:   std::vector<cocos2d::Point >
	// Qualifier: 返回左手武器攻击范围
	//************************************
	std::vector<cocos2d::Point > getLeftHandAtkArea();
	//************************************
	// Method:    getRightHandAtkArea
	// FullName:  Character::getRightHandAtkArea
	// Access:    public 
	// Returns:   std::vector<cocos2d::Point >
	// Qualifier: 返回右手武器攻击范围
	//************************************
	std::vector<cocos2d::Point > getRightHandAtkArea();

	//返回在当前layer中的坐标
	cocos2d::Point getPosition();
	//返回世界坐标
	cocos2d::Point getWorldPosition();
	void setPosition(float x, float y);

	cocos2d::Node* getParent();

	void runSkill(std::string skillName);


	InventoryHandler* getInventoryHandler();
	//discard
	void addInventory(Inventory* inventory);
	void addInventory(const std::string& inventoryName);

	cocos2d::CCSprite* getSprite();
	void setSprite(std::string spriteName);

	void setAI(AIBase* a);
protected:
	//AI......
	AIBase* ai;

	//Skill......
	std::map<std::string, Skill*> skillBox;

	//Inventory......
	InventoryHandler* inventoryHandler;
	//std::vector<Inventory*> inventoryList;

	CC_SYNTHESIZE(InventoryInHand*, leftHand, LeftHand);
	CC_SYNTHESIZE(InventoryInHand*, rightHand, RightHand);
	CC_SYNTHESIZE(Armor*, armor, Armor);
	CC_SYNTHESIZE(Accessory* ,accessory, Accessory);

	//attribute......
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(cocos2d::Point, mapCoord, MapCoord);
	CC_SYNTHESIZE(int, strength, Strength);
	CC_SYNTHESIZE(int, intellect, Intellect);
	CC_SYNTHESIZE(int, agility, Agility);
	CC_SYNTHESIZE(int, maxHP, MaxHP);
	CC_SYNTHESIZE(int, maxMP, MaxMP);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, MP, MP);
	CC_SYNTHESIZE(Type, characterType, CharacterType);
	CC_SYNTHESIZE(int, viewSize, ViewSize);
	bool dead;

	cocos2d::CCSprite* sprite;
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
