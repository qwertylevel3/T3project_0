#pragma once

#include "AIBase.h"

class AIDestroyWizard:public AIBase
{
public:
	AIDestroyWizard();
	~AIDestroyWizard();
	void update();

protected:
	bool isInMagicArea(int distance);
};

