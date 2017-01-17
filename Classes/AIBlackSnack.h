#pragma once

#include "AIBase.h"


class AIBlackSnack:public AIBase
{
public:
	AIBlackSnack();
	~AIBlackSnack();
	void update();
	void feedback(Character* character);
protected:
	//如果周围有点亮的星塔，尝试破坏
	//如果行动返回true，否则返回false
	bool tryDestroyShrine();
};

