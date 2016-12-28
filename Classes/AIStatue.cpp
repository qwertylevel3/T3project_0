#include "AIStatue.h"
#include "BuffFactory.h"
#include "ToolFunction.h"
#include "Player.h"
#include "DialogueSystem.h"
#include "ExpHandler.h"

AIStatue::AIStatue()
{
	count = 1;
}

AIStatue::~AIStatue()
{
}

void AIStatue::feedback(Character* character)
{
	if (count)
	{
		characterPtr->speak(L"叮咚");

		character->addBuff(
			ToolFunction::WStr2UTF8(
				L"ViewSizeBuff_女神祝福_ATTR_Good_1_20_3"
			)
		);
		character->sufferHPEffect(100);
		character->sufferMPEffect(100);
		count--;
	}
	Character * playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	ExpHandler* expHandler = playerCharacterPtr->getExphandler();
	if (expHandler->getCurAttrPoint()>0)
	{
		DialogueSystem::getInstance()->runDialogue("levelUp", this->characterPtr);
	}
	else
	{
		characterPtr->speak(L"没有属性点");
	}
}

void AIStatue::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	Character * playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	ExpHandler* expHandler = playerCharacterPtr->getExphandler();

	if (resultNumber == -1)
	{
		playerCharacterPtr->setStrength(
			playerCharacterPtr->getOriStrength() + 1
		);
		expHandler->useAttrPoint();
	}
	else if (resultNumber == -2)
	{
		playerCharacterPtr->setAgility(
			playerCharacterPtr->getOriAgility() + 1
		);
		expHandler->useAttrPoint();
	}
	else
	{
		playerCharacterPtr->setIntellect(
			playerCharacterPtr->getOriIntellect() + 1
		);
		expHandler->useAttrPoint();
	}
}
