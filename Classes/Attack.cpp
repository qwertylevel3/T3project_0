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
	animation = Animation::createWithSpriteFrames(frameVec,0.1f);
	//animation->setDelayPerUnit(0.5);
	animation->retain();
}


Attack::~Attack()
{
}

int Attack::run()
{
	Field::Dungeon* dungeon = caster->getDungeon();
	Point position = caster->getPosition();
	Point curCoord = caster->getMapCoord();
	Point castCoord = curCoord;
	castCoord.x++;

	showEffect();
	
	return 0;
}

void Attack::showEffect()
{
	Field::Dungeon* dungeon = caster->getDungeon();
	Point position = caster->getPosition();

	cocos2d::Node* scene = caster->getParent();

	cocos2d::Sprite* node = Sprite::create();//Sprite::createWithSpriteFrameName("effect_0.png");
	node->setPosition(Point(position.x, position.y + 32));
	node->setVisible(true);
	scene->addChild(node, 2);

	CCAnimate* animate = CCAnimate::create(animation);
	animate->setDuration(0.3);

	node->runAction(Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, node)), NULL));

}
