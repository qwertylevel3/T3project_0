#include "AISummonWizard.h"
#include "RandomNumber.h"
#include "ToolFunction.h"

AISummonWizard::AISummonWizard()
{
}

AISummonWizard::~AISummonWizard()
{
}

void AISummonWizard::update()
{
	if (!characterPtr)
	{
		return;
	}

	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		if (characterPtr->getChantCount() >= 10
			&& characterPtr->getMP() >= 20)
		{
			//已经吟唱且魔法充足
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(
					L"Summon_召唤slime_20_10_slime"
				)
			);
		}
		else if (RandomNumber::getInstance()->randomBool(0.8)
			&& characterPtr->getMP() >= 20)
		{
			//如果有魔法
			characterPtr->chant();
		}
		else
		{
			this->changeOrientationTo(targetCharacter);	
			{
				if (isInAttackArea(targetCharacter))
				{
					characterPtr->attack();
				}
				else
				{
					flee(targetCharacter);
				}
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AISummonWizard::feedback(Character* character)
{
}
