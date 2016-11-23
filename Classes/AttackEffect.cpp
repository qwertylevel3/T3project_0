#include "AttackEffect.h"
#include "BattleSystem.h"
#include "Dungeon.h"
#include "2d/CCAnimation.h"
#include "InventoryInHand.h"
#include "Arrow.h"
#include "InventoryHandler.h"

using namespace Skill;


AttackEffect::AttackEffect()
{
	cocos2d::SpriteFrame* frame0 = cocos2d::SpriteFrame::create("battle/effect_0.png",cocos2d::Rect(0,0,32,32));
	cocos2d::Vector<cocos2d::SpriteFrame*> frameVec;
	frameVec.pushBack(frame0);
	animation = cocos2d::Animation::createWithSpriteFrames(frameVec, 0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}


AttackEffect::~AttackEffect()
{
	animation->release();
}

bool Skill::AttackEffect::run(Character* caster, std::vector<cocos2d::Point>& coord)
{
	BattleSystem::getInstance()->attack(caster, coord);
	return true;
}

void Skill::AttackEffect::showOneHandEffect(Character* caster, std::vector<cocos2d::Point>& coord)
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

void Skill::AttackEffect::showTwoHandEffect(Character* caster, std::vector<cocos2d::Point>& coord)
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

void Skill::AttackEffect::showBowEffect(Character* caster, std::vector<cocos2d::Point>& coord)
{
	if (coord.empty())
	{
		return;
	}
	cocos2d::Point targetCoord=coord[0];
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriPosition = caster->getPosition();
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);
	cocos2d::Node* scene = caster->getParent();

	cocos2d::Sprite* arrowSprite = cocos2d::Sprite::create("battle/arrow_effect.png");
	arrowSprite->setPosition(oriPosition);
	scene->addChild(arrowSprite, 15);
	cocos2d::ActionInterval* moveAction = cocos2d::CCMoveTo::create(0.3, cocos2d::Vec2(targetPosition));


	cocos2d::Vec2 targetVec = targetPosition - oriPosition;

	float angle=-cocos2d::ccpAngle(cocos2d::Vec2(0, 1), targetVec);
	angle = angle * 180.0 / 3.14;

	cocos2d::ActionInterval* rotateAction = cocos2d::CCRotateTo::create(0.0, angle);

	arrowSprite->runAction(cocos2d::Sequence::create(
		rotateAction,moveAction, 
		cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, arrowSprite)), NULL));
}
