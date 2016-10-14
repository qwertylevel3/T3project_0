#pragma once

#include "SelectorBase.h"

namespace Skill
{
	class LinerSelector:public SelectorBase
	{
	public:
		// 5 | 1 | 6		
		//-----------
		// 3 | 0 | 4
		//-----------
		// 7 | 2 | 8
		enum LinerOrientation
		{
			ZERO,UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT
		};
		LinerSelector();
		~LinerSelector();
		std::vector<cocos2d::Point> select(Character* caster);
		void setOrientation(LinerOrientation ori);
		void setImpactNumber(int number);
		void setMaxLength(int length);
	protected:
		cocos2d::Point getOffset(Character* caster);
		//朝向，以caster向上为基准，默认向上
		LinerOrientation orientation;
		//影响单位个数，默认为1,-1为仅作用于环境
		int impactNumber;
		//长度，默认为5
		int maxLength;
	};
}
