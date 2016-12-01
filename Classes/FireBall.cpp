#include "FireBall.h"
#include "LinerSelector.h"
#include "ToolFunction.h"
#include "MainLayer.h"

Skill::FireBall::FireBall(Character* character)
	:SkillBase(character)
{
	this->setName("FireBall");
	this->setCname(ToolFunction::WStr2UTF8(L"¿ìËÙ»ðÇò"));
	this->setChantCost(20);
	this->setMpCost(20);
}

Skill::FireBall::~FireBall()
{
}

void Skill::FireBall::run()
{
	LinerSelector selector;
	std::vector<cocos2d::Point > coord = selector.select(caster);

	if (coord.empty())
	{
		cocos2d::Point offset;
		switch (caster->getOrientation())
		{
		case Character::Orientation::UP:
			offset = cocos2d::Point(0, 1);
			break;
		case Character::Orientation::DOWN:
			offset = cocos2d::Point(0, -1);
			break;
		case Character::Orientation::LEFT:
			offset = cocos2d::Point(-1, 0);
			break;
		case Character::Orientation::RIGHT:
			offset = cocos2d::Point(1, 0);
			break;
		}
		cocos2d::Point targetPosition = caster->getPosition() + 32 * 4 * offset;

		showFireBall(caster->getPosition(), targetPosition);

		return;
	}

	cocos2d::Point targetCoord = coord[0];

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	Character* targetCharacter = storey->getCharacter(targetCoord);
	cocos2d::Point targetPosition = storey->getTilePosition(targetCoord);

	showFireBall(caster->getPosition(), targetPosition);

	//damage
	if (!targetCharacter)
	{
		return;
	}
	targetCharacter->sufferHPEffect(-15);
}

void Skill::FireBall::showFireBall(cocos2d::Point oriPosition, cocos2d::Point dstPosition)
{
	cocos2d::Sprite* fireBallSprite = cocos2d::Sprite::create("effect/fireBall.png");
	fireBallSprite->setPosition(oriPosition);
	MainLayer::getInstance()->addChild(fireBallSprite);

	fireBallSprite->runAction(
		cocos2d::Spawn::create(
			cocos2d::Sequence::create(
				cocos2d::DelayTime::create(0.1),
				cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, fireBallSprite)),
				NULL
			),
			cocos2d::MoveTo::create(0.1, dstPosition),
			NULL
		)
	);
}
