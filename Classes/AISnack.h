#pragma once

#include "AIBase.h"

class AISnack:public AIBase
{
public:
	AISnack();
	~AISnack();
	void update();
	void feedback(Character* character);

};

