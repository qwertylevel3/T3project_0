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
	node->setPosition(position);

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
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect/HPRecovery.plist");
}

void EffectManager::initAnimationBox()
{
	std::vector<std::string > hpRecoverySV;
	hpRecoverySV.push_back("HPRecovery1.png");
	hpRecoverySV.push_back("HPRecovery2.png");
	hpRecoverySV.push_back("HPRecovery3.png");

	animationBox["HPRecovery"] = hpRecoverySV;
}

cocos2d::Animation* EffectManager::getAnimation(const std::string& animationName)
{
	std::vector<std::string >& animationVector = animationBox[animationName];

	cocos2d::Vector< cocos2d::SpriteFrame* > animationSF = cocos2d::Vector< cocos2d::SpriteFrame* >::Vector();
	for each (std::string frameName in animationVector)
	{
		animationSF.pushBack(
			cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(
				frameName)
		);
	}
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animationSF, 0.1f);
	animation->setDelayPerUnit(0.01);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(3);
	return animation;
}