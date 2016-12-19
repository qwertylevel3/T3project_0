#pragma once

#include<AIBase.h>

class AIEnts:public AIBase
{
public:
	AIEnts();
	~AIEnts();
	void update();
	void feedback(Character* character);
protected:
};

