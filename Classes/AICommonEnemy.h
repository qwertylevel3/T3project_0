#pragma once
#include "AIBase.h"

class AICommonEnemy :public AIBase
{
public:
	AICommonEnemy();
	virtual ~AICommonEnemy();
	virtual void update();
protected:
	//危险生命值百分比
	int deadLine;
	void seek(Character* character);
	void flee(Character* character);
	bool isDangerous();
};

