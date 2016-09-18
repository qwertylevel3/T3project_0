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
	void seek(Character* target);
	void flee(Character* target);
	bool isDangerous();
	bool isInAttackArea(Character* target);
};

