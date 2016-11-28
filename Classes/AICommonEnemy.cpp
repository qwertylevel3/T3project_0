#include "AICommonEnemy.h"
#include "Character.h"
#include "ToolFunction.h"
#include "Player.h"



AICommonEnemy::AICommonEnemy()
{
	deadLine = 20;
}

AICommonEnemy::~AICommonEnemy()
{
}

void AICommonEnemy::update()
{
	if (!characterPtr)
	{
		return;
	}
	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		if (isDangerous())
		{
			flee(targetCharacter);
		}
		else
		{
			if (!isInAttackArea(targetCharacter))
			{
				seek(targetCharacter);
			}
			else
			{
				characterPtr->attack();
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}
bool AICommonEnemy::isDangerous()
{
	double HP = characterPtr->getHP();
	double maxHP = characterPtr->getMaxHP();
	if (HP * 100 / maxHP < deadLine)
	{
		return true;
	}
	return false;
}
