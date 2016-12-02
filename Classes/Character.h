#pragma once

#include<cocos2d.h>
#include<map>
#include <vector>
#include "CharacterAttr.h"
#include "DogTag.h"

class CharacterAttrHandler;
class MainLayer;
class Inventory;
class InventoryInHand;
class Armor;
class Accessory;
class AIBase;
class InventoryHandler;
class RoundHandler;


namespace Buff
{
	class BuffBase;
	class BuffHandler;
}

namespace Skill
{
	class SkillBase;
	class SkillHandler;
}

class Character
{
public:
	enum PlayType
	{
		Player, Hero, Enemy
	};
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

	//************************************
	// Method:    update
	// FullName:  Character::update
	// Access:    public
	// Returns:   void
	// Qualifier: update character every round
	//************************************
	void update();
	void action();

	void processAction(float delayTime);
	int getActionPoint();

	void startRound();
	void endRound();

	bool sufferHPEffect(int hpOffset);
	void showHPEffect(int hpOffset);
	bool sufferMPEffect(int mpOffset);

	bool accumulateChant(int value);
	void clearChant();

	//************************************
	// Method:    die
	// FullName:  Character::die
	// Access:    public
	// Returns:   void
	// Qualifier: 这里不将该character从storey中移除。移除的工作由storey统一负责
	//************************************
	void die();
	bool isDead();
	void idle();
	void speak(std::wstring sentence);
	void attack();
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

	//返回在当前layer中的坐标
	cocos2d::Point getPosition();
	//返回世界坐标
	cocos2d::Point getWorldPosition();
	void setPosition(float x, float y);
	void setPosition(cocos2d::Point position);

	cocos2d::Node* getParent();

	void runSkill(std::string skillName);

	std::vector<cocos2d::Point> getAtkArea();
	std::vector<cocos2d::Point> getAtkSelect();

	InventoryHandler* getInventoryHandler();
	Skill::SkillHandler* getSkillHandler();
	Buff::BuffHandler* getBuffHandler();
	RoundHandler* getRoundHandler();
	//discard
	void addInventory(Inventory* inventory);
	void addInventory(const std::string& inventoryName);

	cocos2d::CCSprite* getSprite();
	void setSprite(std::string spriteName);

	void setAI(const std::string& AIName);

	void addBuff(std::string buffID);
	void removeBuff(std::string buffID);
	void addSkill(std::wstring skillID);
	//////////////////////////////////////////////////////////////////////////
	bool isPhysicalImmune();
	bool isMagicImmune();

	bool isMoveAble();
	bool isAttackAble();
	bool isChantAble();
	bool isSkillAble();
	bool isActionAble();

	int getMaxHP();
	int getMaxMP();
	int getStrength();
	int getIntellect();
	int getAgility();
	int getViewSize();
	int getLuck();

	//////////////////////////////////////////////////////////////////////////

	void setPhysicalImmune(bool b);
	void setMagicImmnue(bool b);

	void setMoveAble(bool b);
	void setAttackAble(bool b);
	void setSkillAble(bool b);
	void setChantAble(bool b);
	void setActionAble(bool b);

	void setMaxHP(int h);
	void setMaxMP(int m);
	void setStrength(int strength);
	void setIntellect(int intellect);
	void setAgility(int agility);
	void setViewSize(int viewSize);
	void setLuck(int luck);


	//////////////////////////////////////////////////////////////////////////

	int getEvadePro();
	int getAccuracuPro();
	int getCriticalPro();
	int getCriticalPer();
	int getCriticalPoint();
	int getBlockPro();
	int getBlockPoint();
	int getComboPro();
	int getWeight();

	int getArmorPoint();
protected:
	//每回合开始调用，防止position与坐标发生偏移
	void fixPosition();
	void recalculateHP();
	void recalculateMP();

	void loadInventoryBuff(Inventory* inventory);
	void unloadInventoryBuff(Inventory* inventory);

	std::vector<cocos2d::Point> getOneHandAtkArea();
	std::vector<cocos2d::Point> getTwoHandAtkArea();
	//返回弓类武器攻击范围
	std::vector<cocos2d::Point> getBowAtkArea();
	//返回弓类武器真实选择坐标
	std::vector<cocos2d::Point> getBowAtkSelect();

	//////////////////////////////////////////////////////////////////////////
	
	//round handler
	RoundHandler* roundHandler;

	//DOGTAG : could identify unique character
	DogTag dogTag;

	//AI......
	AIBase* ai;

	//Skill......
	Skill::SkillHandler* skillHandler;

	//Inventory......
	InventoryHandler* inventoryHandler;
	//std::vector<Inventory*> inventoryList;

	CC_SYNTHESIZE(InventoryInHand*, leftHand, LeftHand);
	CC_SYNTHESIZE(InventoryInHand*, rightHand, RightHand);
	CC_SYNTHESIZE(Armor*, armor, Armor);
	CC_SYNTHESIZE(Accessory*, accessory, Accessory);

	//attribute......
	CC_SYNTHESIZE(Type, characterType, CharacterType);
	CC_SYNTHESIZE(PlayType, playType, PlayType);
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(cocos2d::Point, mapCoord, MapCoord);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, MP, MP);
	CC_SYNTHESIZE(int, chant, Chant);
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(CharacterAttrHandler*, attrHandler, AttrHandler);
	CC_SYNTHESIZE(int, level, Level);

	bool dead;

	cocos2d::CCSprite* sprite;
	CC_SYNTHESIZE(Orientation, orientation, Orientation);

	//buff handler
	Buff::BuffHandler* buffHandler;

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
