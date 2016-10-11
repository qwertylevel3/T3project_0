#include "AttackEffect.h"
#include "BattleSystem.h"
#include "Dungeon.h"
#include "2d/CCAnimation.h"

using namespace Skill;


AttackEffect::AttackEffect()
{
	cocos2d::SpriteFrame* frame0 = cocos2d::CCSpriteFrameCache::getInstance()->getSpriteFrameByName("effect_0.png");
	cocos2d::Vector<cocos2d::SpriteFrame*> frameVec;
	frameVec.pushBack(frame0);
	animation = cocos2d::Animation::createWithSpriteFrames(frameVec, 0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}


AttackEffect::~AttackEffect()
{
}

void Skill::AttackEffect::run(Character* caster, std::vector<cocos2d::Point>& coord)
{
	std::set<Character* > targetCharacters;
	for each (cocos2d::Point targetPosition in coord)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(targetPosition.x, targetPosition.y);
		if (target && !target->isDead())
		{
			targetCharacters.insert(target);
		}
	}
	for each (Character* target in targetCharacters)
	{
		BattleSystem::getInstance()->attack(caster, target);
	}


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
	animate->setDuration(0.3);

	cocos2d::ActionInterval* rotateAction = cocos2d::CCRotateTo::create(0.0, rotateAngle);
	//node->runAction(rotateAction);

	node->runAction(cocos2d::Sequence::create(rotateAction, animate, cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, node)), NULL));

}
