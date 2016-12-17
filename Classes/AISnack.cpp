#include "AISnack.h"
#include "RandomNumber.h"
#include "ToolFunction.h"

AISnack::AISnack()
{
}

AISnack::~AISnack()
{
}

void AISnack::update()
{
	if (!characterPtr)
	{
		return;
	}
	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		if (!isInAttackArea(targetCharacter))
		{
			seek(targetCharacter);
		}
		else
		{
			//ÒÑÒ÷³ª
			if (characterPtr->getChantCount() >= 1)
			{
				characterPtr->runSkill(
					ToolFunction::WStr2UTF8(L"BuffCast_¶¾Òº_0_0_HPBuff_¶¾Òº_OnRoundStart_Bad_10_5_-2")
				);
			}
			else if (RandomNumber::getInstance()->randomBool(0.5))
			{
				if (characterPtr->getChantCount() == 0)
				{
					characterPtr->chant();
				}
				else
				{
					characterPtr->attack();
				}
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

void AISnack::feedback(Character* character)
{
}