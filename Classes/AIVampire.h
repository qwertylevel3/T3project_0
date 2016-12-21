#pragma once

#include "AIBase.h"


class AIVampire:public AIBase
{
public:
	AIVampire();
	~AIVampire();
	void update();
	void feedback(Character* character);
protected:
	//危险生命值百分比
	int deadLine;
	bool isDangerous();
};

