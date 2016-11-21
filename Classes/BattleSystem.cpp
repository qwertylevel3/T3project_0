#include "BattleSystem.h"
#include <iostream>
#include<cstdlib>
#include<ctime>
#include"armor.h"
#include"accessory.h"
#include"Character.h"
#include "Weapon.h"
#include "WeaponSphereHandler.h"
#include "SphereBase.h"
#include "InventoryHandler.h"
#include "Dungeon.h"
#include "MainLayer.h"
#include "2d/CCAnimation.h"
#include "ToolFunction.h"
#include "base/ccTypes.h"
#include "MainLayer.h"
#include "RandomNumber.h"

#include "Marco.h"

using namespace std;

BattleSystem::BattleSystem()
{
}

BattleSystem::~BattleSystem()
{
}

void BattleSystem::init()
{
	combo = 0;
	srand(unsigned(time(0)));

	cocos2d::SpriteFrame* frame0 = cocos2d::SpriteFrame::create("effect_0.png", cocos2d::Rect(0, 0, 32, 32));
	cocos2d::Vector<cocos2d::SpriteFrame*> frameVec;
	frameVec.pushBack(frame0);
	animation = cocos2d::Animation::createWithSpriteFrames(frameVec, 0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}

void BattleSystem::showAttackEffect(Character* caster, AttackHand hand)
{
	MainLayer::getInstance()->unfocusPlayer();

	cocos2d::Vec2 direction;
	switch (caster->getOrientation())
	{
	case Character::UP:
		direction = cocos2d::ccp(0, 3);
		break;
	case Character::DOWN:
		direction = cocos2d::ccp(0, -3);
		break;
	case Character::LEFT:
		direction = cocos2d::ccp(-3, 0);
	case Character::RIGHT:
		direction = cocos2d::ccp(3, 0);
		break;
	default:
		break;
	}

	cocos2d::ActionInterval *shake0 = cocos2d::MoveBy::create(0.05, direction);
	cocos2d::ActionInterval *shake1 = shake0->reverse();
	caster->getSprite()->runAction(
		cocos2d::Sequence::create(shake0, shake1, NULL)
	);

	switch (hand)
	{
	case LeftHand:
		showOneHandEffect(caster);
		break;
	case RightHand:
		showOneHandEffect(caster);
		break;
	case DoubleHand:
		showTwoHandEffect(caster);
		break;
	case Bow:
		showBowEffect(caster);
		break;
	default:
		break;
	}
}

void BattleSystem::showOneHandEffect(Character* caster)
{
	cocos2d::Point position = caster->getPosition();
	cocos2d::Node* scene = caster->getParent();
	cocos2d::Sprite* node = cocos2d::Sprite::create();//Sprite::createWithSpriteFrameName("effect_0.png");

	int rotateAngle = 0;
	cocos2d::Point targetCoord;

	switch (caster->getOrientation())
	{
	case Character::Orientation::UP:
		node->setPosition(cocos2d::Point(position.x, position.y + 32));
		rotateAngle = 0;
		break;
	case Character::Orientation::DOWN:
		node->setPosition(cocos2d::Point(position.x, position.y - 32));
		rotateAngle = 180;
		break;
	case Character::Orientation::LEFT:
		node->setPosition(cocos2d::Point(position.x - 32, position.y));
		rotateAngle = 270;
		break;
	case Character::Orientation::RIGHT:
		node->setPosition(cocos2d::Point(position.x + 32, position.y));
		rotateAngle = 90;
		break;
	}

	node->setVisible(true);
	scene->addChild(node, 15);

	cocos2d::Animate* animate = cocos2d::CCAnimate::create(animation);
	animate->setDuration(0.2);

	cocos2d::ActionInterval* rotateAction = cocos2d::CCRotateTo::create(0.0, rotateAngle);
	//node->runAction(rotateAction);

	node->runAction(cocos2d::Sequence::create(
		rotateAction,
		animate,
		cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, node)),
		NULL));
}

void BattleSystem::showTwoHandEffect(Character* caster)
{
	cocos2d::Point position = caster->getPosition();
	cocos2d::Node* scene = caster->getParent();
	cocos2d::Sprite* node = cocos2d::Sprite::create();//Sprite::createWithSpriteFrameName("effect_0.png");

	int rotateAngle = 0;
	cocos2d::Point targetCoord;

	switch (caster->getOrientation())
	{
	case Character::Orientation::UP:
		node->setPosition(cocos2d::Point(position.x, position.y + 32));
		rotateAngle = 0;
		break;
	case Character::Orientation::DOWN:
		node->setPosition(cocos2d::Point(position.x, position.y - 32));
		rotateAngle = 180;
		break;
	case Character::Orientation::LEFT:
		node->setPosition(cocos2d::Point(position.x - 32, position.y));
		rotateAngle = 270;
		break;
	case Character::Orientation::RIGHT:
		node->setPosition(cocos2d::Point(position.x + 32, position.y));
		rotateAngle = 90;
		break;
	}

	node->setScaleX(3);
	node->setVisible(true);
	scene->addChild(node, 15);

	cocos2d::Animate* animate = cocos2d::CCAnimate::create(animation);
	animate->setDuration(0.2);

	cocos2d::ActionInterval* rotateAction = cocos2d::CCRotateTo::create(0.0, rotateAngle);
	//node->runAction(rotateAction);

	node->runAction(cocos2d::Sequence::create(rotateAction, animate, cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, node)), NULL));
}

void BattleSystem::showBowEffect(Character* caster)
{
	//	cocos2d::Point targetCoord=coord[0];
	//	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	//	cocos2d::Point oriPosition = caster->getPosition();
	//	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);
	//	cocos2d::Node* scene = caster->getParent();

	//	cocos2d::Sprite* arrowSprite = cocos2d::Sprite::create("arrow_effect.png");
	//	arrowSprite->setPosition(oriPosition);
	//	scene->addChild(arrowSprite, 15);
	//	cocos2d::ActionInterval* moveAction = cocos2d::CCMoveTo::create(0.3, cocos2d::Vec2(targetPosition));

	//	cocos2d::Vec2 targetVec = targetPosition - oriPosition;

	//	float angle=-cocos2d::ccpAngle(cocos2d::Vec2(0, 1), targetVec);
	//	angle = angle * 180.0 / 3.14;

	//	cocos2d::ActionInterval* rotateAction = cocos2d::CCRotateTo::create(0.0, angle);

	//	arrowSprite->runAction(cocos2d::Sequence::create(
	//		rotateAction,moveAction,
	//		cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, arrowSprite)), NULL));
}

void BattleSystem::showSufferDamageEffect(Character* character, Character::Orientation direction, int damage, bool isBlock)
{
	MainLayer::getInstance()->unfocusPlayer();
	cocos2d::DelayTime* delayTime = cocos2d::DelayTime::create(0.1);
	cocos2d::CallFunc *callFunc = cocos2d::CallFunc::create(MainLayer::getInstance(), callfunc_selector(MainLayer::focusPlayer));
	cocos2d::Sequence *action = cocos2d::Sequence::create(delayTime, callFunc, NULL);

	cocos2d::Vec2 shakeA;
	cocos2d::Vec2 shakeB;

	switch (direction)
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

	//block 情况下不颤动
	if (isBlock)
	{
		shakeA = cocos2d::Vec2(0, 0);
		shakeB = cocos2d::Vec2(0, 0);
	}

	cocos2d::ActionInterval *shake0 = cocos2d::MoveBy::create(0.025, shakeA);
	cocos2d::ActionInterval *shake1 = shake0->reverse();
	cocos2d::ActionInterval *shake2 = cocos2d::MoveBy::create(0.025, shakeB);
	cocos2d::ActionInterval *shake3 = shake2->reverse();
	character->getSprite()->runAction(
		cocos2d::Spawn::create(
			action,
			cocos2d::Sequence::create(shake0, shake1, shake2, shake3, NULL),
			NULL
		)
	);
	if (isBlock)
	{
		//showBlock(character);
		//闪白
		character->getSprite()->runAction(
			cocos2d::TintBy::create(0.2, 0, 0, 0)
		);
	}
	else
	{
		//闪红
		character->getSprite()->runAction(
			cocos2d::TintBy::create(0.2, 0, 255, 255)
		);
	}
}

void BattleSystem::showMiss(Character* character)
{
	cocos2d::Label* messageLabel = cocos2d::Label::createWithTTF("MISS", "fonts/arialuni.ttf", 22);
	messageLabel->setTextColor(cocos2d::Color4B(0, 0, 255, 255));

	//	int positionXoffset = RandomNumber::getInstance()->randomInt(-10, 10);
	//	int positionYoffset = RandomNumber::getInstance()->randomInt(-10, 10);

	cocos2d::Sprite* characterSprite = character->getSprite();
	messageLabel->setPosition(
		characterSprite->getPosition().x,// + positionXoffset,
		characterSprite->getPosition().y// + positionYoffset
	);

	//	characterSprite->addChild(messageLabel);
	//	cocos2d::Node* parent = characterSprite->getScene();
	//	parent->addChild(messageLabel);
	MainLayer::getInstance()->addChild(messageLabel);

	messageLabel->runAction(
		cocos2d::Spawn::create(
			cocos2d::Sequence::create(
				cocos2d::DelayTime::create(0.3),
				cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, messageLabel)),
				NULL
			),
			cocos2d::MoveBy::create(0.3, cocos2d::Vec2(0, 32)),
			//			cocos2d::FadeOut::create(0.2),
			NULL
		)
	);
}

void BattleSystem::showBlock(Character* character)
{
	cocos2d::Label* messageLabel = cocos2d::Label::createWithTTF("BLOCK", "fonts/arialuni.ttf", 22);
	messageLabel->setZOrder(20);
//	messageLabel->setTextColor(cocos2d::Color4B(0, 0, 255, 255));

	//	int positionXoffset = RandomNumber::getInstance()->randomInt(-10, 10);
	//	int positionYoffset = RandomNumber::getInstance()->randomInt(-10, 10);

	cocos2d::Sprite* characterSprite = character->getSprite();
	messageLabel->setPosition(
		characterSprite->getPosition().x,// + positionXoffset,
		characterSprite->getPosition().y// + positionYoffset
	);

	//	characterSprite->addChild(messageLabel);
	//	cocos2d::Node* parent = characterSprite->getScene();
	//	parent->addChild(messageLabel);
	MainLayer::getInstance()->addChild(messageLabel);

	messageLabel->runAction(
		cocos2d::Spawn::create(
			cocos2d::Sequence::create(
				cocos2d::DelayTime::create(0.3),
				cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, messageLabel)),
				NULL
			),
//			cocos2d::MoveBy::create(0.3, cocos2d::Vec2(0, 32)),
			//			cocos2d::FadeOut::create(0.2),
			NULL
		)
	);

}

Weapon* BattleSystem::getWeapon(Character* c, AttackHand hand)
{
	Weapon* weapon;
	Inventory::Type type;
	switch (hand)
	{
	case LeftHand:
	case DoubleHand:
	case Bow:
		type = c->getLeftHand() ? c->getLeftHand()->getInventoryType() : Inventory::Type::Empty;
		if (type == Inventory::OneHandWeapon ||
			type == Inventory::TwoHandWeapon ||
			type == Inventory::Bow)
		{
			weapon = static_cast<Weapon*>(c->getLeftHand());
		}
		else
		{
			weapon = nullptr;
		}

		break;
	case RightHand:
		type = c->getRightHand() ? c->getRightHand()->getInventoryType() : Inventory::Empty;
		if (type == Inventory::OneHandWeapon
			|| type == Inventory::TwoHandWeapon
			|| type == Inventory::Bow)
		{
			weapon = static_cast<Weapon*>(c->getRightHand());
		}
		else
		{
			weapon = nullptr;
		}
		break;
	}
	return weapon;
}

void BattleSystem::attack(Character * a, Character * b)
{
#ifdef SHOWMESSAGE
	cout << "########################################" << endl;
	cout << a->getName() << "(HP:" << a->getHP() << ")" << " -> "
		<< b->getName() << "(HP:" << b->getHP() << ")" << endl;
	cout << "-----attack start------" << endl;
#endif
	combo = 0;
	do
	{
		if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~leftHand:" << endl;
#endif
			attack(a, b, LeftHand);
			if (a->getRightHand() && a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
			{
#ifdef SHOWMESSAGE
				cout << "~rightHand:" << endl;
#endif
				attack(a, b, RightHand);
			}
		}
		else if (a->getRightHand() && a->getRightHand()->getInventoryType() == Inventory::OneHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~rightHand:" << endl;
#endif
			attack(a, b, RightHand);
		}
		else if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::TwoHandWeapon)
		{
#ifdef SHOWMESSAGE
			cout << "~doubleHand:" << endl;
#endif
			attack(a, b, DoubleHand);
		}
		else if (a->getLeftHand() && a->getLeftHand()->getInventoryType() == Inventory::Bow)
		{
#ifdef SHOWMESSAGE
			cout << "~doubleHand:" << endl;
#endif
			attack(a, b, Bow);
		}

		if (!isCombo(a))
		{
			break;
		}
		else
		{
#ifdef SHOWMESSAGE
			cout << "combo!" << endl;
#endif
			combo++;
		}
	} while (!b->isDead());
#ifdef SHOWMESSAGE
	cout << "-----attack end------" << endl;
	cout << a->getName() << "(HP:" << a->getHP() << ")" << " -> "
		<< b->getName() << "(HP:" << b->getHP() << ")" << endl;
	cout << "#######################################" << endl;
#endif
}

void BattleSystem::attack(Character* a, Character* b, AttackHand hand)
{
	if (!isInAtkArea(a, b, hand))
	{
#ifdef SHOWMESSAGE
		cout << "is not in atk area" << endl;
#endif
		return;
	}
	if (isEvade(a, b, hand))
	{
#ifdef SHOWMESSAGE
		cout << "evade!" << endl;
#endif
		showMiss(b);
		return;
	}

	int attackCount = 0;
	if (isCritical(a))
	{
		attackCount = getCriticalAttackCount(a, hand);
#ifdef SHOWMESSAGE
		cout << "critical atk!" << endl;
		cout << "atk count:" << attackCount << endl;
#endif
	}
	else
	{
		attackCount = getAttackCount(a, hand);
#ifdef SHOWMESSAGE
		cout << "atk count:" << attackCount << endl;
#endif
	}
	int realDamage = sufferAttack(a, b, hand, attackCount);
	//sphereEffect 调用点
	Weapon* weapon = getWeapon(a, hand);
	if (!weapon)
	{
		return;
	}
	WeaponSphereHandler* sphereHandler = weapon->getSphereHandler();
	std::vector<Sphere::SphereBase*> sphereBox = sphereHandler->getSphereBoxRef();
	for each (Sphere::SphereBase* sphere in sphereBox)
	{
		sphere->run(a, b, realDamage);
	}
}

void BattleSystem::attack(Character* caster, std::vector<cocos2d::Point>& coords)
{
	std::set<Character* > targetCharacters;
	for each (cocos2d::Point targetPosition in coords)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(targetPosition.x, targetPosition.y);
		if (target && !target->isDead())
		{
			targetCharacters.insert(target);
		}
	}

	for each (Character* target in targetCharacters)
	{
		if (caster->getLeftHand() &&
			caster->getLeftHand()->getInventoryType() == Inventory::Bow)
		{
			Inventory* arrow = caster->getInventoryHandler()->getInventory("arrow000");
			if (arrow)
			{
				delete arrow;
			}
			else
			{
				return;
			}
		}

		attack(caster, target);
	}

	if (targetCharacters.empty())
	{
		Weapon* leftWeapon = getWeapon(caster, LeftHand);
		Weapon* rightWeapon = getWeapon(caster, RightHand);
		if (leftWeapon && leftWeapon->getInventoryType() == Inventory::OneHandWeapon)
		{
			showAttackEffect(caster, LeftHand);
		}
		if (rightWeapon && rightWeapon->getInventoryType() == Inventory::OneHandWeapon)
		{
			showAttackEffect(caster, RightHand);
		}
		if (leftWeapon && leftWeapon->getInventoryType() == Inventory::TwoHandWeapon)
		{
			showAttackEffect(caster, DoubleHand);
		}
		if (leftWeapon && leftWeapon->getInventoryType() == Inventory::Bow)
		{
			showAttackEffect(caster, Bow);
		}
	}
}

int BattleSystem::sufferAttack(Character* a, Character * b, AttackHand hand, int attackCount)
{
	if (b->isPhysicalImmune())
	{
#ifdef SHOWMESSAGE
		cout << b->getName() << " is physical Immune!" << endl;
#endif
		return 0;
	}
	int armorPoint = b->getArmorPoint();
	int blockCount = 0;
	bool block = isBlock(b);
	if (block)
	{
		blockCount = getBlockCount(b);
#ifdef SHOWMESSAGE
		cout << "block!" << endl;
		cout << "blockCount:" << blockCount << endl;
#endif
	}

	int damage = attackCount - armorPoint - blockCount;
	damage = damage >= 1 ? damage : 1;
#ifdef SHOWMESSAGE
	cout << "suffer damage:" << damage << endl;
#endif

	b->sufferHPEffect(-damage);
	//showDamage(c, damage);

	showAttackEffect(a, hand);
	showSufferDamageEffect(b, a->getOrientation(), damage, block);

	return damage;
}

int BattleSystem::getAttackCount(Character* a, AttackHand hand)
{
	double agility = a->getAgility();
	double strength = a->getStrength();

	Weapon* weapon = getWeapon(a, hand);
	double agiReq = 0;
	double strReq = 0;
	double attackCount = 0;

	if (!weapon)
	{
		return 0;
	}

	agiReq = weapon->getAgiRequire();
	strReq = weapon->getStrRequire();

	attackCount = weapon->getWeaponDamage();

	if (agiReq != 0 && agiReq >= agility)
	{
		attackCount = attackCount*agility / agiReq;
	}
	if (strReq != 0 && strReq >= strength)
	{
		attackCount = attackCount*strength / strReq;
	}

	return int(attackCount < 1 ? 1 : attackCount);
}

int BattleSystem::getCriticalAttackCount(Character* c, AttackHand hand)
{
	double k1 = 0.01;
	int attackCount = getAttackCount(c, hand);
	double criPer = c->getCriticalPer();
	double criPoint = c->getCriticalPoint();
	double criticalAttack = double(attackCount)*criPer / 100 + criPoint;
	return int(criticalAttack < 1 ? 1 : criticalAttack);
}

int BattleSystem::getCriticalPoint(Character* c)
{
	return c->getCriticalPoint();
}

int BattleSystem::getBlockCount(Character* c)
{
	return c->getBlockPoint();
}

bool BattleSystem::isInAtkArea(Character* a, Character* b, AttackHand hand)
{
	std::vector<cocos2d::Point> atkArea;
	atkArea = a->getAtkArea();
	for each (cocos2d::Point point in atkArea)
	{
		if (point == b->getMapCoord())
		{
			return true;
		}
	}
	return false;
}

bool BattleSystem::isEvade(Character* a, Character* b, AttackHand hand)
{
	int temp = getAccuracyCount(a) - getEvadeCount(b);
	temp = 100 - temp;
	temp = temp < 0 ? 0 : temp;
	temp = temp > 90 ? 90 : temp;
#ifdef SHOWMESSAGE
	cout << "evade chance:" << temp << endl;
#endif
	return roll(temp);
}

bool BattleSystem::isCritical(Character* c)
{
	int criPro = getCriticalProCount(c);
	criPro = criPro > 90 ? 90 : criPro;
#ifdef SHOWMESSAGE
	cout << "cirtical chance:" << criPro << endl;
#endif
	return roll(criPro);
}

bool BattleSystem::isBlock(Character* c)
{
	int blockPro = getBlockProCount(c);
	blockPro = blockPro > 90 ? 90 : blockPro;
#ifdef SHOWMESSAGE
	cout << "block chance:" << blockPro << endl;
#endif

	return roll(blockPro);
}

bool BattleSystem::isCombo(Character* c)
{
	Weapon* weapon = getWeapon(c, LeftHand);
	if (weapon && weapon->getInventoryType() == Inventory::Bow)
	{
		return false;
	}
	int comboPro = getComboProCount(c);
	comboPro = comboPro > 90 ? 90 : comboPro;
#ifdef SHOWMESSAGE
	cout << "combo chance:" << comboPro << endl;
#endif
	return roll(comboPro);
}

double BattleSystem::getRandom(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

bool BattleSystem::roll(double m)
{
	double rand = getRandom(0, 100);
#ifdef SHOWMESSAGE
	cout << "	(roll:" << rand << ")" << endl;
#endif
	if (rand < m)
	{
		return true;
	}
	return false;
}

int BattleSystem::getEvadeCount(Character* c)
{
	return c->getEvadePro();
}

int BattleSystem::getAccuracyCount(Character* c)
{
	return c->getAccuracuPro();
}

int BattleSystem::getCriticalProCount(Character* c)
{
	return c->getCriticalPro();
}

int BattleSystem::getBlockProCount(Character* c)
{
	return c->getBlockPro();
}

int BattleSystem::getComboProCount(Character* c)
{
	return c->getComboPro();
}
