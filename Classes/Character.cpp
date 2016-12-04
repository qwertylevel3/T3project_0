#include "Character.h"
#include "RoundSystem.h"
#include "ToolFunction.h"
#include "RandomNumber.h"
#include"MainLayer.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"Inventory.h"
#include "InventoryInHand.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "AIBase.h"
#include "InventoryHandler.h"
#include "SkillHandler.h"
#include "SkillBase.h"
#include "Attack.h"
#include "Dungeon.h"
#include "FixedSelector.h"
#include "LinerSelector.h"
#include "SingleDirectionSearchSelector.h"
#include "CharacterAttrHandler.h"
#include "BuffHandler.h"
#include "Chant.h"
#include "BuffFactory.h"
#include "ui/UIScale9Sprite.h"
#include "AIFactory.h"
#include "SkillFactory.h"

USING_NS_CC;
using namespace Field;

Character::Character()
{
	roundHandler = new RoundHandler(this);

	skillHandler = new Skill::SkillHandler(this);

	addSkill(L"attack_¹¥»÷_0_0");
	addSkill(L"chant_Ò÷³ª_0_0");

	orientation = DOWN;
	dead = false;
	gold = 0;

	leftHand = nullptr;
	rightHand = nullptr;
	armor = nullptr;
	accessory = nullptr;

	ai = nullptr;

	inventoryHandler = new InventoryHandler();
	attrHandler = new CharacterAttrHandler(this);
	buffHandler = new Buff::BuffHandler(this);

	chant = 0;
}

Character::~Character()
{
	sprite->release();
	if (ai)
	{
		delete ai;
	}
	delete inventoryHandler;
	delete attrHandler;
	delete buffHandler;
	delete skillHandler;
}

bool Character::sufferHPEffect(int hpOffset)
{
	showHPEffect(hpOffset);
	HP += hpOffset;
	if (HP <= 0)
	{
		die();
		return false;
	}
	else if (HP >= getMaxHP())
	{
		HP = getMaxHP();
		return false;
	}
	return true;
}

void Character::showHPEffect(int hpOffset)
{
	int textSize = 16 + 16 * abs(hpOffset) / 10;
	textSize = textSize > 42 ? 42 : textSize;
	cocos2d::Label* messageLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", textSize);
	std::string labelText = ToolFunction::int2string(hpOffset);
	if (hpOffset > 0)
	{
		labelText = "+" + labelText;
	}
	messageLabel->setString(labelText);
	if (hpOffset >= 0)
	{
		messageLabel->setTextColor(cocos2d::Color4B(0, 255, 0, 255));
	}
	else
	{
		messageLabel->setTextColor(cocos2d::Color4B(255, 0, 0, 255));
	}

	cocos2d::Sprite* characterSprite = this->getSprite();
	messageLabel->setPosition(
		characterSprite->getPosition().x,
		characterSprite->getPosition().y
	);

	//	characterSprite->addChild(messageLabel);
	//	cocos2d::Node* parent = characterSprite->getScene();
	//	parent->addChild(messageLabel);
	MainLayer::getInstance()->addChild(messageLabel);

	if (hpOffset > 0)
	{
		messageLabel->runAction(
			cocos2d::Spawn::create(
				cocos2d::Sequence::create(
					cocos2d::DelayTime::create(0.5),
					cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, messageLabel)),
					NULL
				),
				cocos2d::MoveBy::create(0.2, cocos2d::Vec2(0, 32)),
				NULL
			)
		);
	}
	else
	{
		cocos2d::Vec2 jumpPosition;
		int jumpHeight;

		jumpPosition.x = RandomNumber::getInstance()->randomInt(-64, 64);
		jumpHeight = 64 + hpOffset / 10;
		jumpHeight = jumpHeight > 128 ? 128 : jumpHeight;
		jumpPosition.y = jumpHeight / 2;

		messageLabel->runAction(
			cocos2d::Spawn::create(
				cocos2d::Sequence::create(
					cocos2d::DelayTime::create(0.5),
					cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, messageLabel)),
					NULL
				),
				//cocos2d::MoveBy::create(0.2, cocos2d::Vec2(0, 32)),
				//			cocos2d::FadeOut::create(0.2),
				//cocos2d::JumpBy::create(0.2, cocos2d::Vec2(64, 0),64, 0.2),
				cocos2d::JumpBy::create(0.5, jumpPosition, jumpHeight, 1),
				NULL
			)
		);
	}
}

bool Character::sufferMPEffect(int mpOffset)
{
	MP += mpOffset;
	if (MP < 0)
	{
		MP = 0;
		return false;
	}
	else if (MP > getMaxMP())
	{
		MP = getMaxMP();
		return false;
	}
	return true;
}

bool Character::accumulateChant(int value)
{
	chant += value;
	return true;
}

void Character::clearChant()
{
	chant = 0;
}

void Character::die()
{
	sprite->setVisible(false);
	unequipLeftHand();
	unequipRightHand();
	unequipArmor();
	unequipAccessory();

	inventoryHandler->drop(this->getMapCoord());

	dead = true;
}

bool Character::isDead()
{
	return dead;
}

void Character::idle()
{
	processAction(0);
}

void Character::speak(std::wstring sentence)
{
	ui::Scale9Sprite* bk = ui::Scale9Sprite::create("HUD/sentenceLabel.png");
	cocos2d::Label* messageLabel = cocos2d::Label::createWithTTF(ToolFunction::WStr2UTF8(sentence), "fonts/arialuni.ttf", 16);
	messageLabel->setMaxLineWidth(200);

	bk->setCapInsets(cocos2d::Rect(10, 10, 100, 20));
	bk->setScale9Enabled(true);

	sprite->addChild(bk);
	sprite->addChild(messageLabel);

	cocos2d::Rect bound = messageLabel->getBoundingBox();

	messageLabel->setPosition(sprite->getPosition() + cocos2d::Vec2(20, 50));
	//	bk->setScaleX(bound.size.width / bk->getContentSize().width+0.1);
	//	bk->setScaleY(bound.size.height / bk->getContentSize().height+0.1);

		//bk->setScale(5, 2);

	bk->setContentSize(cocos2d::Size(bound.size.width + 10, bound.size.height + 10));
	bk->setPosition(messageLabel->getPosition() - Vec2(0, 3));
	bk->setOpacity(180);

	bk->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(4),
			cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, bk)),
			NULL
		)
	);
	messageLabel->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(4),
			cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, messageLabel)),
			NULL
		)
	);
}

void Character::attack()
{
	runSkill(ToolFunction::WStr2UTF8(L"attack_¹¥»÷_0_0"));
	clearChant();
}

void Character::moveUp()
{
	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->characterMoveUp(this);
	processAction(0);
	clearChant();
}

void Character::moveDown()
{
	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->characterMoveDown(this);
	processAction(0);
	clearChant();
}

void Character::moveLeft()
{
	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->characterMoveLeft(this);
	processAction(0);
	clearChant();
}

void Character::moveRight()
{
	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->characterMoveRight(this);
	processAction(0);
	clearChant();
}

void Character::setOrientationUp()
{
	Animate* action = Animate::create(standUpAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::UP);
}

void Character::setOrientationDown()
{
	Animate* action = Animate::create(standDownAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::DOWN);
}

void Character::setOrientationLeft()
{
	Animate* action = Animate::create(standLeftAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::LEFT);
}

void Character::setOrientationRight()
{
	Animate* action = Animate::create(standRightAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	int a = 0;
	setOrientation(Orientation::RIGHT);
	int b = 5;
	int c = a - b;
}

void Character::showMoveUpAnimation()
{
	Animate* action = Animate::create(moveUpAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveDownAnimation()
{
	Animate* action = Animate::create(moveDownAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveLeftAnimation()
{
	Animate* action = Animate::create(moveLeftAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveRightAnimation()
{
	Animate* action = Animate::create(moveRightAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::equipLeftHand(Inventory* inventory)
{
	MainLayer::getInstance()->focusPlayer();
	inventory->equipLeftHand(this);
	loadInventoryBuff(inventory);
}

void Character::equipRightHand(Inventory* inventory)
{
	inventory->equipRightHand(this);
	loadInventoryBuff(inventory);
}

void Character::equipArmor(Inventory* inventory)
{
	inventory->equipArmor(this);
	loadInventoryBuff(inventory);
}

void Character::equipAccessory(Inventory* inventory)
{
	inventory->equipAccessory(this);
	loadInventoryBuff(inventory);
}

void Character::unequipLeftHand()
{
	if (leftHand && leftHand->getInventoryType() == Inventory::OneHandWeapon)
	{
		this->unloadInventoryBuff(leftHand);
		inventoryHandler->addInventory(leftHand);
		leftHand = nullptr;
	}
	else if (leftHand &&
		(leftHand->getInventoryType() == Inventory::TwoHandWeapon ||
			leftHand->getInventoryType() == Inventory::Bow))
	{
		this->unloadInventoryBuff(leftHand);
		inventoryHandler->addInventory(leftHand);
		leftHand = nullptr;
		rightHand = nullptr;
	}
}

void Character::unequipRightHand()
{
	if (rightHand && rightHand->getInventoryType() == Inventory::OneHandWeapon)
	{
		this->unloadInventoryBuff(rightHand);
		inventoryHandler->addInventory(rightHand);
		rightHand = nullptr;
	}
	else if (rightHand &&
		(rightHand->getInventoryType() == Inventory::TwoHandWeapon ||
			rightHand->getInventoryType() == Inventory::Bow))
	{
		this->unloadInventoryBuff(rightHand);
		inventoryHandler->addInventory(rightHand);
		leftHand = nullptr;
		rightHand = nullptr;
	}
}

void Character::unequipArmor()
{
	if (armor)
	{
		this->unloadInventoryBuff(armor);
		inventoryHandler->addInventory(armor);
		armor = nullptr;
	}
}

void Character::unequipAccessory()
{
	if (accessory)
	{
		this->unloadInventoryBuff(accessory);
		inventoryHandler->addInventory(accessory);
		accessory = nullptr;
	}
}

cocos2d::Point Character::getPosition()
{
	return sprite->getPosition();
}

cocos2d::Point Character::getWorldPosition()
{
	Node* layer = sprite->getParent();

	cocos2d::Point spritePosition = sprite->getPosition();
	cocos2d::Point layerPositioin = layer->getPosition();

	return spritePosition + layerPositioin;
}

void Character::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

void Character::setPosition(cocos2d::Point position)
{
	sprite->setPosition(position);
}

cocos2d::Node * Character::getParent()
{
	return sprite->getParent();
}

void Character::runSkill(std::string skillName)
{
	if (skillHandler->runSkill(skillName))
	{
		processAction(0.2);
	}
}

std::vector<cocos2d::Point> Character::getAtkArea()
{
	std::vector<cocos2d::Point> vec;
	if ((leftHand && leftHand->getInventoryType() == Inventory::OneHandWeapon) ||
		(rightHand && rightHand->getInventoryType() == Inventory::OneHandWeapon)
		)
	{
		return getOneHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::TwoHandWeapon)
	{
		return getTwoHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::Bow)
	{
		return getBowAtkArea();
	}
	return vec;
}

std::vector<cocos2d::Point> Character::getAtkSelect()
{
	std::vector<cocos2d::Point> vec;
	if ((leftHand && leftHand->getInventoryType() == Inventory::OneHandWeapon) ||
		(rightHand && rightHand->getInventoryType() == Inventory::OneHandWeapon)
		)
	{
		return getOneHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::TwoHandWeapon)
	{
		return getTwoHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::Bow)
	{
		return getBowAtkSelect();
	}
	return vec;
}

InventoryHandler* Character::getInventoryHandler()
{
	return inventoryHandler;
}

Skill::SkillHandler* Character::getSkillHandler()
{
	return skillHandler;
}

Buff::BuffHandler* Character::getBuffHandler()
{
	return buffHandler;
}

RoundHandler* Character::getRoundHandler()
{
	return roundHandler;
}

void Character::addInventory(Inventory * inventory)
{
	inventoryHandler->addInventory(inventory);
}

void Character::addInventory(const std::string& inventoryName)
{
	inventoryHandler->addInventory(inventoryName, 1);
}

Sprite * Character::getSprite()
{
	return sprite;
}

void Character::setSprite(std::string spriteName)
{
	sprite = Sprite::createWithSpriteFrameName(spriteName);
	sprite->retain();
}

void Character::setAI(const std::string& AIName)
{
	ai = AIFactory::getInstance()->getAI(AIName);
	ai->setCharacter(this);
}

void Character::addBuff(std::string buffID)
{
	buffHandler->addBuff(buffID);
}

void Character::removeBuff(std::string buffID)
{
	buffHandler->removeBuff(buffID);
}

void Character::addSkill(std::wstring skillID)
{
	skillHandler->addSkill(
		Skill::SkillFactory::getInstance()->getSkill(
			this,
			ToolFunction::WStr2UTF8(skillID)
		)
	);
}

bool Character::isPhysicalImmune()
{
	return attrHandler->isPhysicalImmune();
}

bool Character::isMagicImmune()
{
	return attrHandler->isMagicImmune();
}

bool Character::isMoveAble()
{
	return attrHandler->isMoveAble();
}

bool Character::isAttackAble()
{
	return attrHandler->isAttackAble();
}

bool Character::isChantAble()
{
	return attrHandler->isChantAble();
}

bool Character::isSkillAble()
{
	return attrHandler->isSkillAble();
}

bool Character::isActionAble()
{
	return attrHandler->isActionAble();
}

int Character::getMaxHP()
{
	return attrHandler->getMaxHP();
}

int Character::getMaxMP()
{
	return attrHandler->getMaxMP();
}

int Character::getStrength()
{
	return attrHandler->getStrength();
}

int Character::getIntellect()
{
	return attrHandler->getIntellect();
}

int Character::getAgility()
{
	return attrHandler->getAgility();
}

int Character::getViewSize()
{
	return attrHandler->getViewSize();
}

int Character::getLuck()
{
	return attrHandler->getLuck();
}

void Character::setPhysicalImmune(bool b)
{
	attrHandler->setPhysicalImmune(b);
}

void Character::setMagicImmnue(bool b)
{
	attrHandler->setMagicImmnue(b);
}

void Character::setMoveAble(bool b)
{
	attrHandler->setMoveAble(b);
}

void Character::setAttackAble(bool b)
{
	attrHandler->setAttackAble(b);
}

void Character::setSkillAble(bool b)
{
	attrHandler->setSkillAble(b);
}

void Character::setChantAble(bool b)
{
	attrHandler->setChantAble(b);
}

void Character::setActionAble(bool b)
{
	attrHandler->setActionAble(b);
}

void Character::setMaxHP(int h)
{
	attrHandler->setMaxHP(h);
}

void Character::setMaxMP(int m)
{
	attrHandler->setMaxMP(m);
}

void Character::setStrength(int strength)
{
	attrHandler->setStrength(strength);
}

void Character::setIntellect(int intellect)
{
	attrHandler->setIntellect(intellect);
}

void Character::setAgility(int agility)
{
	attrHandler->setAgility(agility);
}

void Character::setViewSize(int viewSize)
{
	attrHandler->setViewSize(viewSize);
}

void Character::setLuck(int luck)
{
	attrHandler->setLuck(luck);
}

int Character::getEvadePro()
{
	return attrHandler->getEvadePoint();
}

int Character::getAccuracuPro()
{
	return attrHandler->getAccuracyPoint();
}

int Character::getCriticalPro()
{
	return attrHandler->getCriticalPro();
}

int Character::getCriticalPer()
{
	return attrHandler->getCriticalPer();
}

int Character::getCriticalPoint()
{
	return attrHandler->getCriticalPoint();
}

int Character::getBlockPro()
{
	return attrHandler->getBlockPro();
}

int Character::getBlockPoint()
{
	return attrHandler->getBlockPoint();
}

int Character::getComboPro()
{
	return attrHandler->getComboPro();
}

int Character::getWeight()
{
	return attrHandler->getWeight();
}

int Character::getArmorPoint()
{
	if (armor)
	{
		return armor->getArmorCount();
	}
	return 0;
}

void Character::update()
{
	buffHandler->update();
}

void Character::action()
{
	if (roundHandler->isSkipNextRound())
	{
		//fixPosition();
		roundHandler->setSkipNextRound(false);
		idle();
	}
	else
	{
		if (ai)
		{
			ai->update();
		}
	}
}

void Character::processAction(float delayTime)
{
	roundHandler->processAction(delayTime);
}

int Character::getActionPoint()
{
	return roundHandler->getActionPoint();
}

void Character::startRound()
{
	//	fixPosition();
	roundHandler->startRound();
	buffHandler->onRoundStart();
	recalculateHP();
	recalculateMP();
}

void Character::endRound()
{
	//	fixPosition();
	buffHandler->onRoundEnd();
	recalculateHP();
	recalculateMP();
	//	clearChant();
}

void Character::fixPosition()
{
	Field::Dungeon::getInstance()->getStorey()->setPositionByCoord(this, this->getMapCoord());
}

void Character::recalculateHP()
{
	if (HP > getMaxHP())
	{
		HP = getMaxHP();
	}
}

void Character::recalculateMP()
{
	if (MP > getMaxMP())
	{
		MP = getMaxMP();
	}
}

void Character::loadInventoryBuff(Inventory* inventory)
{
	std::vector<std::string> buffBox = inventory->getAllInventoryBuff();
	for each (std::string buffID in buffBox)
	{
		this->addBuff(buffID);
	}
}

void Character::unloadInventoryBuff(Inventory* inventory)
{
	std::vector<std::string> buffBox = inventory->getAllInventoryBuff();
	for each (std::string buffID in buffBox)
	{
		this->removeBuff(buffID);
	}
}

std::vector<cocos2d::Point> Character::getOneHandAtkArea()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	return selector.select(this);
}

// x | x | x
//-----------
//   | c |
//-----------
//   |   |
std::vector<cocos2d::Point> Character::getTwoHandAtkArea()
{
	FixedSelector selector;
	selector.addRelativeCoord(0, 1);
	selector.addRelativeCoord(-1, 1);
	selector.addRelativeCoord(1, 1);
	return selector.select(this);
}

std::vector<cocos2d::Point> Character::getBowAtkArea()
{
	SingleDirectionSearchSelector selector;
	selector.setImpactNumber(-1);
	return selector.select(this);
}

std::vector<cocos2d::Point> Character::getBowAtkSelect()
{
	LinerSelector linerSelector;
	linerSelector.setMaxLength(5);
	std::vector<cocos2d::Point> result = linerSelector.select(this);
	if (!result.empty())
	{
		return result;
	}
	SingleDirectionSearchSelector singleDirectionSelector;
	singleDirectionSelector.setImpactNumber(1);
	return singleDirectionSelector.select(this);
}

void Character::setMoveUpAnimation(cocos2d::Animation* animation)
{
	moveUpAnimation = animation;
}

void Character::setMoveDownAnimation(cocos2d::Animation* animation)
{
	moveDownAnimation = animation;
}

void Character::setMoveLeftAnimation(cocos2d::Animation* animation)
{
	moveLeftAnimation = animation;
}

void Character::setMoveRightAnimation(cocos2d::Animation* animation)
{
	moveRightAnimation = animation;
}

void Character::setStandUpAnimation(cocos2d::Animation * animation)
{
	standUpAnimation = animation;
}

void Character::setStandDownAnimation(cocos2d::Animation * animation)
{
	standDownAnimation = animation;
}

void Character::setStandLeftAnimation(cocos2d::Animation * animation)
{
	standLeftAnimation = animation;
}

void Character::setStandRightAnimation(cocos2d::Animation * animation)
{
	standRightAnimation = animation;
}