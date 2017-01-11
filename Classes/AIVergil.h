#pragma once

#include "AIBase.h"

class AIVergil :public AIBase
{
public:
	AIVergil();
	~AIVergil();
	void update();
	void feedback(Character* character);
	void handleDialogueResult(std::string dialogueName, int resultNumber);
	void lastWords();
protected:
	//状态:
	//0:紧密跟随
	//1:自由活动
	int curState;

	//紧密跟随的ai
	void stayCloseAI();
	//自由活动的ai
	void freeAI();

	//获得周围的enemy
	std::vector<Character* > getEnemyAround();
	//获得player周围的enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//比较两个character相对characterPtr的距离
	bool cmpDistance(Character* a, Character* b);
	//整理物品
	void tidyInventory();

	void chooseBetterLefthand();
	void chooseBetterRighthand();
	void chooseBetterArmor();
	void chooseBetterAccessory();
	void showCurState();
};
