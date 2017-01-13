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
		if (characterPtr->getChantCount() >= 20
			&& characterPtr->getMP() >= 60)
		{
			//已经吟唱且魔法充足
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(
					L"Summon_召唤slime_60_10_slime"
				)
			);
		}
		else if (RandomNumber::getInstance()->randomBool(0.4)
			&& characterPtr->getMP() >= 60)
		{
			//如果有魔法
			characterPtr->chant();
		}
		else
		{
			if (!flee(targetCharacter))
			{
				this->changeOrientationTo(targetCharacter);
				if (isInAttackArea(targetCharacter))
				{
					characterPtr->attack();
				}
				else
				{
					characterPtr->idle();
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