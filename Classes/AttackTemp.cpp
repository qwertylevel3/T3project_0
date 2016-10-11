#include "AttackTemp.h"
#include"Dungeon.h"
#include"Character.h"
#include"CharacterManager.h"
#include "BattleSystem.h"

USING_NS_CC;

AttackTemp::AttackTemp(Character* character)
	:SkillTemp(character)
{
	SpriteFrame* frame0 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("effect_0.png");
	Vector<SpriteFrame*> frameVec;
	frameVec.pushBack(frame0);
	animation = Animation::createWithSpriteFrames(frameVec, 0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}

AttackTemp::~AttackTemp()
{
}

int AttackTemp::run()
{
	Point position = caster->getPosition();
	Point curCoord = caster->getMapCoord();

	showEffect();

	return 0;
}


std::set<Character* > AttackTemp::getAllTargetCharacter()
{
	std::set<Character* > targetCharacters;
	std::vector<cocos2d::Point> leftHandAtkArea = caster->getLeftHandAtkArea();
	for each (cocos2d::Point point in leftHandAtkArea)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(point.x, point.y);
		if (target && !target->isDead())
		{
			targetCharacters.insert(target);
		}
	}
	std::vector<cocos2d::Point> rightHandAtkArea = caster->getRightHandAtkArea();
	for each (cocos2d::Point point in rightHandAtkArea)
	{
		Character* target = Field::Dungeon::getInstance()->getCharacter(point.x, point.y);
		if (target && !target->isDead())
		{
			targetCharacters.insert(target);
		}
	}
	return targetCharacters;
}

void AttackTemp::showEffect()
{
	Point position = caster->getPosition();

	cocos2d::Node* scene = caster->getParent();

	cocos2d::Sprite* node = Sprite::create();//Sprite::createWithSpriteFrameName("effect_0.png");

	int rotateAngle = 0;
	cocos2d::Point targetCoord;

	switch (caster->getOrientation())
	{
	case Character::Orientation::UP:
		node->setPosition(Point(position.x, position.y + 32));
		targetCoord.x = caster->getMapCoord().x;
		targetCoord.y = caster->getMapCoord().y-1;
		rotateAngle = 0;
		break;
	case Character::Orientation::DOWN:
		node->setPosition(Point(position.x, position.y - 32));
		targetCoord.x = caster->getMapCoord().x;
		targetCoord.y = caster->getMapCoord().y + 1;
		rotateAngle = 180;
		break;
	case Character::Orientation::LEFT:
		node->setPosition(Point(position.x - 32, position.y));
		targetCoord.x = caster->getMapCoord().x - 1;
		targetCoord.y = caster->getMapCoord().y;
		rotateAngle = 270;
		break;
	case Character::Orientation::RIGHT:
		node->setPosition(Point(position.x + 32, position.y));
		targetCoord.x = caster->getMapCoord().x + 1;
		targetCoord.y = caster->getMapCoord().y;
		rotateAngle = 90;
		break;
	}

	node->setVisible(true);
	scene->addChild(node, 2);

	Animate* animate = CCAnimate::create(animation);
	animate->setDuration(0.3);

	ActionInterval* rotateAction = CCRotateTo::create(0.0, rotateAngle);
	//node->runAction(rotateAction);

	node->runAction(Sequence::create(rotateAction,animate, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, node)), NULL));

	//attack an character;
	std::set<Character* >targetCharacters = getAllTargetCharacter();
	for each (Character*  target in targetCharacters)
	{
		BattleSystem::getInstance()->attack(caster, target);
	}
}