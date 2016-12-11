#pragma once

#include "AIBase.h"

class AIPortal:public AIBase
{
public:
	AIPortal();
	~AIPortal();
	void update();
	void feedback(Character* character);
protected:
	bool isPlayerNear();
};

