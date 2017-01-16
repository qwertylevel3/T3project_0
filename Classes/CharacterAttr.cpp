#include "CharacterAttr.h"

CharacterAttr::CharacterAttr()
{
	physicalImmune = false;
	magicImmune = false;

	moveAble = true;
	attackAble=true;
	chantAble=true;
	skillAble=true;
	actionAble=true;

	strength = 0;
	intellect = 0;
	agility = 0;
	luck = 0;
	viewSize = 1;
	maxHP = 0;
	maxMP = 0;

	evadePoint = 0;//闪避值
	accuracyPoint = 0;//命中率
	criticalPro = 0;//暴击概率
	criticalPoint = 0;//暴击附加值
	criticalPer = 0;//暴击倍率
	blockPro = 0;//格挡值几率
	blockPoint = 0;//格挡点数
	comboPro = 0;//连击概率
	weight = 0;//负重

}

void CharacterAttr::calculateBattleAttr()
{
	evadePoint = agility;

	accuracyPoint = agility + 70;

	criticalPro = agility*1;
	criticalPro = criticalPro > 90 ? 90 : criticalPro;

	criticalPer = strength + 100;

	criticalPoint = strength*0.6;

	blockPro = agility*0.2;
	blockPro = blockPro > 90 ? 90 : blockPro;

	blockPoint = strength*0.2 + 5;

	comboPro = agility;
	comboPro = comboPro > 90 ? 90 : comboPro;

	weight = strength * 2;
}
