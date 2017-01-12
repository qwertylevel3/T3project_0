#include "EffectManager.h"
#include "2d/CCSpriteFrameCache.h"
#include "MainLayer.h"
#include "2d/CCNode.h"
#include "2d/CCActionInstant.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::init()
{
	initPlistFile();
	initAnimationBox();
}

void EffectManager::showEffect(const std::string& effectName, cocos2d::Point position, float duration)
{
	cocos2d::Animate* animate = cocos2d::Animate::create(
		getAnimation(effectName)
	);
	animate->setDuration(duration);

	cocos2d::Sprite* node = cocos2d::Sprite::create();
	MainLayer::getInstance()->addChild(node, 15);
	node->setPosition(position.x, position.y - 16);

	node->runAction(
		cocos2d::Sequence::create(
			animate,
			cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, node)),
			NULL
		)
	);
}

void EffectManager::initPlistFile()
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect/effect.plist");
}

void EffectManager::initAnimationBox()
{
	std::vector<std::string > hpRecoverySV;
	hpRecoverySV.push_back("HPRecovery1.png");
	hpRecoverySV.push_back("HPRecovery2.png");
	hpRecoverySV.push_back("HPRecovery3.png");

	animationBox["HPRecovery"] = hpRecoverySV;
	//////////////////////////////////////////////////////////////////////////
	std::vector<std::string > magicCircleSV;
	magicCircleSV.push_back("magicCircle1.png");
	magicCircleSV.push_back("magicCircle2.png");
	magicCircleSV.push_back("magicCircle3.png");

	animationBox["magicCircle"] = magicCircleSV;
	//////////////////////////////////////////////////////////////////////////
	std::vector<std::string > thunderSV;

	thunderSV.push_back("thunder1.png");
	thunderSV.push_back("thunder2.png");
	thunderSV.push_back("thunder3.png");
	thunderSV.push_back("thunder4.png");

	animationBox["thunder"] = thunderSV;
	//////////////////////////////////////////////////////////////////////////
	std::vector<std::string > summonSV;

	summonSV.push_back("summon1.png");
	summonSV.push_back("summon2.png");
	summonSV.push_back("summon3.png");

	animationBox["summon"] = summonSV;
}

cocos2d::Animation* EffectManager::getAnimation(const std::string& animationName)
{
	std::vector<std::string >& animationVector = animationBox[animationName];

	cocos2d::Vector< cocos2d::SpriteFrame* > animationSF = cocos2d::Vector< cocos2d::SpriteFrame* >::Vector();
	for each (std::string frameName in animationVector)
	{
		cocos2d::SpriteFrame* p = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		p->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
		animationSF.pushBack(p);
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animationSF, 0.1f);
	animation->setDelayPerUnit(0.2);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(3);
	return animation;
}