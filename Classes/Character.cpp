#include "Character.h"
#include "RoundSystem.h"
#include "ExpHandler.h"
#include "CharacterSpeakLabel.h"
#include "HudMessageBox.h"
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
#include "CharacterBar.h"
#include "SkillFactory.h"
#include "2d/CCAnimation.h"

USING_NS_CC;
using namespace Field;

Character::Character()
{
	roundHandler = new RoundHandler(this);

	skillHandler = new Skill::SkillHandler(this);

	addSkill(L"attack_攻击_0_0");
	addSkill(L"chant_吟唱_0_0");

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
	expHandler = new ExpHandler(this);

	chantCount = 0;

	characterBar = new CharacterBar();
	speakLabel = new CharacterSpeakLabel();
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
	delete characterBar;
	delete speakLabel;
}

bool Character::sufferHPEffect(int hpOffset)
{
	showHPEffect(hpOffset);
	HP += hpOffset;
	characterBar->update();
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
		showVibrateEffect();
	}
}

bool Character::sufferMPEffect(int mpOffset)
{
	MP += mpOffset;
	if (MP < 0)
	{
		MP = 0;
		characterBar->update();

		return false;
	}
	else if (MP > getMaxMP())
	{
		MP = getMaxMP();
		characterBar->update();

		return false;
	}
	characterBar->update();
	return true;
}

void Character::showVibrateEffect()
{
	//	MainLayer::getInstance()->unfocusPlayer();
	//	cocos2d::DelayTime* delayTime = cocos2d::DelayTime::create(0.1);
	//	cocos2d::CallFunc *callFunc = cocos2d::CallFunc::create(MainLayer::getInstance(), callfunc_selector(MainLayer::focusPlayer));
	//	cocos2d::Sequence *action = cocos2d::Sequence::create(delayTime, callFunc, NULL);

	cocos2d::Vec2 shakeA;
	cocos2d::Vec2 shakeB;

	switch (getOrientation())
	{
	case Character::UP:
	case Character::DOWN:
		shakeA = cocos2d::ccp(5, 0);
		shakeB = cocos2d::ccp(-5, 0);
		break;
	case Character::LEFT:
	case Character::RIGHT:
		shakeA = cocos2d::ccp(0, 5);
		shakeB = cocos2d::ccp(0, -5);
		break;
	default:
		break;
	}

	cocos2d::ActionInterval *shake0 = cocos2d::MoveBy::create(0.025, shakeA);
	cocos2d::ActionInterval *shake1 = shake0->reverse();
	cocos2d::ActionInterval *shake2 = cocos2d::MoveBy::create(0.025, shakeB);
	cocos2d::ActionInterval *shake3 = shake2->reverse();

	getSprite()->runAction(
		cocos2d::Sequence::create(shake0, shake1, shake2, shake3, NULL)
	);
}

bool Character::accumulateChant(int value)
{
	chantCount += value;
	return true;
}

void Character::clearChant()
{
	chantCount = 0;
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

	if (ai)
	{
		ai->lastWords();
	}
}

bool Character::isDead()
{
	return dead;
}

void Character::idle()
{
	processAction(0);
}

ExpHandler* Character::getExphandler()
{
	return expHandler;
}

void Character::addExp(const int value)
{
	expHandler->addExp(value);
}

void Character::speak(std::wstring sentence)
{
	speakLabel->speak(sentence);
}

void Character::levelUp()
{
	if (ai)
	{
		ai->levelUp();
	}

}

void Character::interaction()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point playerCoord = getMapCoord();

	cocos2d::Point targetCoord;

	switch (getOrientation())
	{
	case Character::UP:
		targetCoord.x = playerCoord.x;
		targetCoord.y = playerCoord.y - 1;
		break;
	case Character::DOWN:
		targetCoord.x = playerCoord.x;
		targetCoord.y = playerCoord.y + 1;
		break;
	case Character::LEFT:
		targetCoord.x = playerCoord.x - 1;
		targetCoord.y = playerCoord.y;
		break;
	case Character::RIGHT:
		targetCoord.x = playerCoord.x + 1;
		targetCoord.y = playerCoord.y;
		break;
	}
	Character* targetCharacter = storey->getCharacter(targetCoord);

	if (!targetCharacter)
	{
		HudMessageBox::getInstance()->addMessage(L"面前没有任何单位");
		return;
	}

	targetCharacter->feedback(this);
}

void Character::feedback(Character* character)
{
	if (ai)
	{
		ai->feedback(character);
	}
}

void Character::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	ai->handleDialogueResult(dialogueName, resultNumber);
}

void Character::attack()
{
	runSkill(ToolFunction::WStr2UTF8(L"attack_攻击_0_0"));
	clearChant();
}

void Character::chant()
{
	runSkill(ToolFunction::WStr2UTF8(L"chant_吟唱_0_0"));
}

void Character::moveUp()
{
	//	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->moveUp(this);

	clearChant();
	processAction(0);

}

void Character::moveDown()
{
	//	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->moveDown(this);
	clearChant();
	processAction(0);

}

void Character::moveLeft()
{
	//	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->moveLeft(this);
	clearChant();
	processAction(0);

}

void Character::moveRight()
{
	//	MainLayer::getInstance()->focusPlayer();
	Dungeon::getInstance()->getStorey()->moveRight(this);
	clearChant();
	processAction(0);

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
	setOrientation(Orientation::RIGHT);
}

void Character::showMoveUpAnimation()
{
	Animate* action1 = Animate::create(moveUpAnimation);
	action1->setDuration(0.2);

	Animate* action2 = Animate::create(standUpAnimation);

	sprite->runAction(
		cocos2d::Sequence::create(
			action1,
			action2,
			NULL
		)
	);
}

void Character::showMoveDownAnimation()
{
	Animate* action1 = Animate::create(moveDownAnimation);
	action1->setDuration(0.2);

	Animate* action2 = Animate::create(standDownAnimation);

	sprite->runAction(
		cocos2d::Sequence::create(
			action1,
			action2,
			NULL
		)
	);
}

void Character::showMoveLeftAnimation()
{
	Animate* action1 = Animate::create(moveLeftAnimation);
	action1->setDuration(0.2);

	Animate* action2 = Animate::create(standLeftAnimation);

	sprite->runAction(
		cocos2d::Sequence::create(
			action1,
			action2,
			NULL
		)
	);
}

void Character::showMoveRightAnimation()
{
	Animate* action1 = Animate::create(moveRightAnimation);
	action1->setDuration(0.2);

	Animate* action2 = Animate::create(standRightAnimation);

	sprite->runAction(
		cocos2d::Sequence::create(
			action1,
			action2,
			NULL
		)
	);
}

void Character::equipLeftHand(Inventory* inventory)
{
	//	MainLayer::getInstance()->focusPlayer();
	inventory->equipLeftHand(this);
	loadInventoryBuff(inventory);
	processAction(0);
}

void Character::equipRightHand(Inventory* inventory)
{
	inventory->equipRightHand(this);
	loadInventoryBuff(inventory);
	processAction(0);
}

void Character::equipArmor(Inventory* inventory)
{
	inventory->equipArmor(this);
	loadInventoryBuff(inventory);
	processAction(0);
}

void Character::equipAccessory(Inventory* inventory)
{
	inventory->equipAccessory(this);
	loadInventoryBuff(inventory);
	processAction(0);
}

void Character::initLeftHand(Inventory* inventory)
{
	inventory->equipLeftHand(this);
	loadInventoryBuff(inventory);
}

void Character::initRightHand(Inventory* inventory)
{
	inventory->equipRightHand(this);
	loadInventoryBuff(inventory);

}

void Character::initArmor(Inventory* inventory)
{
	inventory->equipArmor(this);
	loadInventoryBuff(inventory);
}

void Character::initAccessory(Inventory* inventory)
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
		if (skillName != ToolFunction::WStr2UTF8(L"attack_攻击_0_0")
			&& skillName != ToolFunction::WStr2UTF8(L"chant_吟唱_0_0"))
		{
			addExp(ExpHandler::skillExpAdd);
		}
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

int Character::getSumWeight()
{
	int leftWeight = leftHand ? leftHand->getWeight() : 0;
	int rightWeight = rightHand ? rightHand->getWeight() : 0;
	int armorWeight = armor ? armor->getWeight() : 0;
	int accessoryWeight = accessory ? accessory->getWeight() : 0;

	if (leftHand && rightHand && leftHand == rightHand)
	{
		return leftWeight + armorWeight + accessoryWeight +
			inventoryHandler->calculateSumWeight();
	}
	else
	{
		return inventoryHandler->calculateSumWeight()
			+ leftWeight + rightWeight + armorWeight + accessoryWeight;
	}
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

void Character::removeInventory(const std::string& inventoryName)
{
	inventoryHandler->removeInventory(inventoryName);
}

std::string Character::queryInventoryNameByIndex(int index)
{
	return inventoryHandler->queryInventoryNameByIndex(index);
}

Sprite * Character::getSprite()
{
	return sprite;
}

void Character::setSprite(std::string spriteName)
{
	sprite = Sprite::createWithSpriteFrameName(spriteName);
	characterBar->setCharacter(this);
	speakLabel->setCharacter(this);

	sprite->retain();
}

void Character::setAI(const std::string& AIName)
{
	ai = AIFactory::getInstance()->getAI(AIName);
	if (ai)
	{
		ai->setCharacter(this);
	}
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

void Character::addSkill(std::string skillID)
{
	skillHandler->addSkill(
		Skill::SkillFactory::getInstance()->getSkill(
			this,
			skillID
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

int Character::getOriStrength()
{
	return attrHandler->getOriStrength();
}

int Character::getOriAgility()
{
	return attrHandler->getOriAgility();
}

int Character::getOriIntellect()
{
	return attrHandler->getOriIntellect();
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
	buffHandler->calculateAttr();
}

void Character::setIntellect(int intellect)
{
	attrHandler->setIntellect(intellect);
	buffHandler->calculateAttr();
}

void Character::setAgility(int agility)
{
	attrHandler->setAgility(agility);
	buffHandler->calculateAttr();
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

int Character::getLevel()
{
	return expHandler->getCurLevel();
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
		else
		{
			idle();
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
	roundHandler->startRound();
	buffHandler->onRoundStart();
	recalculateHP();
	recalculateMP();

	Storey* storey = Dungeon::getInstance()->getStorey();

	//如果站在Trap上，掉血
	if (storey->isTrap(mapCoord)
		&& !this->isDead())
	{
		sufferHPEffect(-5);
	}
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
