#include "AIDestroyWizard.h"
#include "ToolFunction.h"
#include "RandomNumber.h"



AIDestroyWizard::AIDestroyWizard()
{
}


AIDestroyWizard::~AIDestroyWizard()
{
}

void AIDestroyWizard::update()
{
	//TODO




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
					ToolFunction::WStr2UTF8(L"FireBall_Ä§·¨¼ý_0_1_10_4")
				);
			}
			else if (RandomNumber::getInstance()->randomBool(0.8))
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

void AIDestroyWizard::feedback(Character* character)
{

}
