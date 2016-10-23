#pragma once

#include <string>


struct CharacterAttr
{
	CharacterAttr();

	//base attr
	int strength;
	int intellect;
	int agility;
	int luck;
	int viewSize;
	int maxHP;
	int maxMP;

	//battle attr
	//calculate from AGI,STR,INT
	int evadePoint;//闪避值
	int accuracyPoint;//命中率
	int criticalPro;//暴击概率
	int criticalPoint;//暴击附加值
	int criticalPer;//暴击倍率
	int blockPro;//格挡值几率
	int blockPoint;//格挡点数
	int comboPro;//连击概率
	int weight;//负重

	void calculateBattleAttr();
};
