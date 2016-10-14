#pragma once

#include "EffectBase.h"
#include "2d/CCAnimation.h"

namespace Skill
{
	class AttackEffect:public EffectBase
	{
	public:
		AttackEffect();
		~AttackEffect();
		void run(Character* caster,std::vector<cocos2d::Point>& coord);
	protected:
		cocos2d::Animation* animation;
		void showOneHandEffect(Character* caster, std::vector<cocos2d::Point>& coord);
		void showTwoHandEffect(Character* caster, std::vector<cocos2d::Point>& coord);
		void showBowEffect(Character* caster, std::vector<cocos2d::Point>& coord);
	};
}
