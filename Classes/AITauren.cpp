#include "AITauren.h"
#include "ToolFunction.h"
#include "RandomNumber.h"



AITauren::AITauren()
{
}


AITauren::~AITauren()
{
}

void AITauren::update()
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
			if (RandomNumber::getInstance()->randomBool(0.8))
			{
				characterPtr->runSkill(
					ToolFunction::WStr2UTF8(L"Repel_»÷ÍË_0_0_1_10")
				);
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

void AITauren::feedback(Character* character)
{

}
