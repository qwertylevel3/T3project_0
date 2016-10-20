#pragma once


#include <string>


struct CharacterAttr
{
	enum CharacterType
	{
		Good, Neutral, Bad
	};

	int strength;
	int intellect;
	int agility;
	int luck;
	CharacterType characterType;
	int viewSize;
	int maxHP;
	int maxMP;

	int evadePro;//闪避值
	int accuracyPro;//命中率
	int criticalPro;//暴击概率
	int criticalPoint;//暴击附加值
	int blockPro;//格挡值几率
	int blockPoint;//格挡点数
	int comboPro;//连击概率

	bool moveAble;
	bool attackAble;
	bool castAble;
	bool phyImmu;
	bool magicImmu;
};

