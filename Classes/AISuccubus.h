#pragma once

#include "AIBase.h"

class AISuccubus:public AIBase
{
public:
	AISuccubus();
	~AISuccubus();
	void update();
	void feedback(Character* character);
	void handleDialogueResult(std::string dialogueName, int resultNumber);
protected:
	bool isFirst;

	//获得周围的enemy
	std::vector<Character* > getEnemyAround();
	//获得player周围的enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//比较两个character相对characterPtr的距离
	bool cmpDistance(Character* a, Character* b);
	
};

