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
	void levelUp();
protected:


	//状态:
	//0:紧密跟随
	//1:站着不动
	int curState;

	//行动
	void followAI();

	//等待
	void waitAI();

	

	//获得周围的enemy
	std::vector<Character* > getEnemyAround();
	//获得player周围的enemy
	std::vector<Character* > getEnemyAroundPlayer();

	//比较两个character相对characterPtr的距离
	bool cmpDistance(Character* a, Character* b);
	//整理物品,如果装备某件物品，返回true
	bool tidyInventory();

	//如果成功回复，返回true
	bool tryUseHPSupply();
	bool tryUseMPSupply();

	bool chooseBetterLefthand();
	bool chooseBetterRighthand();
	bool chooseBetterArmor();
	bool chooseBetterAccessory();
	void showCurState();
	//闲聊
	void smallTalk();
	void tryBuffToPlayer();
	void castBuffToPlayer();
	void healCast();
	void healSelf();
};
