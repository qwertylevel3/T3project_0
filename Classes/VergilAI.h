#pragma once

#include "AIBase.h"

class VergilAI:public AIBase
{
public:
	VergilAI();
	~VergilAI();
	void update();
	void talk();
	void handleDialogueResult(std::string dialogueName, int resultNumber);
protected:

};

