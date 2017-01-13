#pragma once

#include "AIBase.h"

class AICommonFriend:public AIBase
{
public:
	AICommonFriend();
	~AICommonFriend();
	void update();
protected:
	//比较两个character相对characterPtr的距离
	bool cmpDistance(Character* a, Character* b);
	//获得周围的enemy
	std::vector<Character* > getEnemyAround();
	//获得player周围的enemy
	std::vector<Character* > getEnemyAroundPlayer();


};

