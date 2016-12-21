#pragma once

#include "AIBase.h"

class AISummonWizard:public AIBase
{
public:
	AISummonWizard();
	~AISummonWizard();

	void update();
	void feedback(Character* character);
};

