#pragma once

#include "HudTrigger.h"

class HudTrigQuit:public HudTrigger
{
public:
	HudTrigQuit();
	~HudTrigQuit();
	void run();
};

