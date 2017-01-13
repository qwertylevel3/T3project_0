#include "AIBlackSnack.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "RandomNumber.h"
#include "BuffHandler.h"

AIBlackSnack::AIBlackSnack()
{
}

AIBlackSnack::~AIBlackSnack()
{
}

void AIBlackSnack::update()
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
			Buff::BuffHandler* targetBuffHandler = targetCharacter->getBuffHandler();
			if (!targetBuffHandler->exist(
				ToolFunction::WStr2UTF8(L"ViewSizeBuff_致盲_ATTR_Bad_1_10_-3")))
			{
				//如果当前目标没有致盲
				//已吟唱
				if (characterPtr->getChantCount() >= 1)
				{
					characterPtr->runSkill(
						ToolFunction::WStr2UTF8(L"BuffCast_致盲_0_0_ViewSizeBuff_致盲_ATTR_Bad_1_10_-3")
					);
					HudMessageBox::getInstance()->addMessage(
						targetCharacter->getName()+
						ToolFunction::WStr2UTF8(L"中了致盲buff")
					);

				}
				else if (RandomNumber::getInstance()->randomBool(0.9))
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

void AIBlackSnack::feedback(Character* character)
{
}