#include "Chant.h"
#include "Character.h"
#include "FixedSelector.h"
#include "ToolFunction.h"

Skill::Chant::Chant()
{
	this->setCname(ToolFunction::WStr2UTF8(L"吟唱"));
	this->setChantCost(0);
	this->setMpCost(0);
}

Skill::Chant::~Chant()
{
}

Skill::Chant* Skill::Chant::createPrototype()
{
	return new Chant();
}

std::string  Skill::Chant::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"增加吟唱点")
		+ ToolFunction::int2string(caster->getIntellect());
}

void Skill::Chant::initExtraMessage(std::vector<std::string> extraMessage)
{
	return;
}

void Skill::Chant::run()
{
	caster->accumulateChant(caster->getIntellect());

	cocos2d::Sprite* magicCircle = cocos2d::Sprite::create("effect/magicCircle.png");

	caster->getSprite()->addChild(magicCircle);
	magicCircle->setPosition(16, 10);

	magicCircle->runAction(
		cocos2d::Spawn::create(
			cocos2d::MoveBy::create(1, cocos2d::Vec2(0, 30)),
			cocos2d::FadeOut::create(1),
			cocos2d::Sequence::create(
				cocos2d::DelayTime::create(1),
				cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, magicCircle)),
				NULL
			),
			NULL
		)
	);
}