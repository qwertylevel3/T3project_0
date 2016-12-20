#pragma once

#include "AIBase.h"

class AICentaur:public AIBase
{
public:
	AICentaur();
	~AICentaur();
	void update();
	void feedback(Character* character);
};

