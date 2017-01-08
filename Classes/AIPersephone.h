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
	//是否和player对话0：否，1：已经对话完毕
	int talkFlag;
};

