#pragma once

#include "AIBase.h"

class AIShrine:public AIBase
{
public:
	AIShrine();
	~AIShrine();
	void update();
	void feedback(Character* character);
protected:
	bool light;
};

