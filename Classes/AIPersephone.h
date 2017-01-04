#pragma once

#include "AIBase.h"

class AIPersephone:public AIBase
{
public:
	AIPersephone();
	~AIPersephone();
	void update();
	void feedback(Character* character);
	void lastWords();
protected:
};

