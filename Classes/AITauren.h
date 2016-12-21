#pragma once

#include "AIBase.h"

class AITauren:public AIBase
{
public:
	AITauren();
	~AITauren();
	void update();
	void feedback(Character* character);
};

