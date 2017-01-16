#include "AIDestroyWizard.h"
#include "HudMessageBox.h"
#include "Dungeon.h"
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
	if (!characterPtr)
	{
		return;
	}
	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);

	if (targetCharacter)
	{
//		std::string chantStr = ToolFunction::int2string(characterPtr->getChantCount());
//		HudMessageBox::getInstance()->addMessage(chantStr);

		this->changeOrientationTo(targetCharacter);

		if (isInAttackArea(targetCharacter))
		{
			//ÒÑÒ÷³ªÇÒÄ§·¨³ä×ã
			if (characterPtr->getChantCount() >= 20
				&& characterPtr->getMP() >= 40)
			{
				characterPtr->runSkill(
					ToolFunction::WStr2UTF8(L"RandomDirectDamage_À×»÷_40_20_100_5_0")
				);
			}
			else if (characterPtr->getMP() >= 40 &&
				RandomNumber::getInstance()->randomBool(0.8))
			{
				//Ä§·¨Öµ³ä×ã
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
		else if (isInMagicArea(4))
		{
			//ÒÑÒ÷³ªÇÒÄ§·¨³ä×ã
			if (characterPtr->getChantCount() >= 20
				&& characterPtr->getMP() >= 40)
			{
				characterPtr->runSkill(
					ToolFunction::WStr2UTF8(L"RandomDirectDamage_À×»÷_40_20_100_5_0")
				);
			}
			else if (characterPtr->getMP() >= 40 &&
				RandomNumber::getInstance()->randomBool(0.8))
			{
				//Ä§·¨Öµ³ä×ã
				if (characterPtr->getChantCount() == 0)
				{
					characterPtr->chant();
				}
				else
				{
					//characterPtr->idle();
					wander();
				}
			}
			else
			{
				wander();
			}
		}
		else
		{
			if (!flee(targetCharacter))
			{
				wander();
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

bool AIDestroyWizard::isInMagicArea(int distance)
{
	cocos2d::Vec2 offset;

	switch (characterPtr->getOrientation())
	{
	case Character::UP:
		offset.x = 0;
		offset.y = -1;
		break;
	case Character::DOWN:
		offset.x = 0;
		offset.y = 1;
		break;
	case Character::LEFT:
		offset.x = -1;
		offset.y = 0;
		break;
	case Character::RIGHT:
		offset.x = 1;
		offset.y = 0;
		break;
	default:
		break;
	}

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	cocos2d::Point oriCoord = characterPtr->getMapCoord();
	cocos2d::Point targetCoord = oriCoord;

	for (int i = 0; i < distance; i++)
	{
		targetCoord += offset;

		if (storey->getCharacter(targetCoord)
			&& storey->getCharacter(targetCoord)->getCharacterType() == Character::Good)
		{
			return true;
		}
	}
	return false;
}