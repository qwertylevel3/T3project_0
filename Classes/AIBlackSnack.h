#pragma once

#include "AIBase.h"


class AIBlackSnack:public AIBase
{
public:
	AIBlackSnack();
	~AIBlackSnack();
	void update();
	void feedback(Character* character);
};

