#include "CharacterAttr.h"

CharacterAttr::CharacterAttr()
{
	strength = 1;
	intellect = 1;
	agility = 1;
	luck = 0;
	characterType = Neutral;
	viewSize = 5;
	maxHP = 10;
	maxMP = 10;

	evadePro = 0;//闪避值
	accuracyPro = 10;//命中率
	criticalPro = 0;//暴击概率
	criticalPoint = 0;//暴击附加值
	blockPro = 0;//格挡值几率
	blockPoint = 0;//格挡点数
	comboPro = 0;//连击概率

	moveAble = true;
	attackAble = true;
	castAble = true;
	phyImmu = false;
	magicImmu = false;
}