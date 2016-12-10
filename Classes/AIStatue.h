#pragma once

#include "AIBase.h"

class AIStatue:public AIBase
{
public:
	AIStatue();
	~AIStatue();
	void feedback(Character* character);
protected:
	int count;
};

