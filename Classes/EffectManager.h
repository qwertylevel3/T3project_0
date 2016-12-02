#pragma once

#include "Singleton.h"
#include <string>
#include "base/ccTypes.h"
#include "base/CCVector.h"

#include <map>

namespace cocos2d
{
	class Animate;
	class Animation;
	class SpriteFrame;
}

class EffectManager :public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();
	void init();
	void showEffect(const std::string& effectName,
		cocos2d::Point position,
		float duration);
protected:
	void initPlistFile();
	void initAnimationBox();
	cocos2d::Animation* getAnimation(const std::string& animationName);
	std::map<std::string, std::vector<std::string> > animationBox;
};
