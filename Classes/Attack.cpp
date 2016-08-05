#include "Attack.h"
#include"Dungeon.h"
#include"Character.h"
#include"CharacterManager.h"

USING_NS_CC;

Attack::Attack(Character* character)
	:Skill(character)
{
	SpriteFrame* frame0 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("effect_0.png");
	Vector<SpriteFrame*> frameVec;
	frameVec.pushBack(frame0);
	animation = Animation::createWithSpriteFrames(frameVec, 0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}

Attack::~Attack()
{
}

int Attack::run()
{
	Point position = caster->getPosition();
	Point curCoord = caster->getMapCoord();
	Point castCoord = curCoord;
	castCoord.x++;

	showEffect();

	return 0;
}

void Attack::showEffect()
{
	Point position = caster->getPosition();

	cocos2d::Node* scene = caster->getParent();

	cocos2d::Sprite* node = Sprite::create();//Sprite::createWithSpriteFrameName("effect_0.png");

	int rotateAngle = 0;
	cocos2d::Point targetPosition;

	switch (caster->getOrientation())
	{
	case Character::Orientation::UP:
		node->setPosition(Point(position.x, position.y + 32));
		targetPosition.x = caster->getMapCoord().x;
		targetPosition.y = caster->getMapCoord().y-1;
		rotateAngle = 0;
		break;
	case Character::Orientation::DOWN:
		node->setPosition(Point(position.x, position.y - 32));
		targetPosition.x = caster->getMapCoord().x;
		targetPosition.y = caster->getMapCoord().y + 1;
		rotateAngle = 180;
		break;
	case Character::Orientation::LEFT:
		node->setPosition(Point(position.x - 32, position.y));
		targetPosition.x = caster->getMapCoord().x - 1;
		targetPosition.y = caster->getMapCoord().y;
		rotateAngle = 270;
		break;
	case Character::Orientation::RIGHT:
		node->setPosition(Point(position.x + 32, position.y));
		targetPosition.x = caster->getMapCoord().x + 1;
		targetPosition.y = caster->getMapCoord().y;
		rotateAngle = 90;
		break;
	}

	node->setVisible(true);
	scene->addChild(node, 2);

	CCAnimate* animate = CCAnimate::create(animation);
	animate->setDuration(0.3);

	CCActionInterval* rotateAction = CCRotateTo::create(0.0, rotateAngle);
	//node->runAction(rotateAction);

	node->runAction(Sequence::create(rotateAction,animate, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, node)), NULL));

	//attack an character;
	Character* targetCharacter = Field::Dungeon::getInstance()->getCharacter(targetPosition.x, targetPosition.y);
	if (targetCharacter)
	{
		int curHp = targetCharacter->getCurHP();
		targetCharacter->setCurHP(curHp - 10);
	}

}