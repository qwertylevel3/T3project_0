#pragma once

#include "AIBase.h"

class AIStatue:public AIBase
{
public:
	AIStatue();
	~AIStatue();
	void feedback(Character* character);
	void handleDialogueResult(std::string dialogueName, int resultNumber);
protected:
	int count;
	void handlePray();
	void handleLevelUp();
};

