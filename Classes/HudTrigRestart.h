#pragma once

#include "HudTrigger.h"

class HudTrigRestart :public HudTrigger
{
public:
	HudTrigRestart();
	~HudTrigRestart();
	void run();
};

