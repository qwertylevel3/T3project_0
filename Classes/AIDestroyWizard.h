#pragma once

#include "AIBase.h"

class AIDestroyWizard:public AIBase
{
public:
	AIDestroyWizard();
	~AIDestroyWizard();
	void update();
	void feedback(Character* character);

};

