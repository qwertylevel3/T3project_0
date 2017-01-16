#include "AIStatue.h"
#include "InventoryFactory.h"
#include "HudMessageBox.h"
#include "RandomNumber.h"
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
	DialogueSystem::getInstance()->runDialogue("statueTalk", this->characterPtr);
}

void AIStatue::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	Character * playerCharacterPtr = Player::getInstance()->getcharacterPtr();
	ExpHandler* expHandler = playerCharacterPtr->getExphandler();

	if (dialogueName == "statueTalk"
		&& resultNumber == -1)
	{
		handlePray();
	}
	else if (dialogueName == "statueTalk"
		&& resultNumber == -2)
	{
		handleLevelUp();
	}
	else if (dialogueName == "pray")
	{
		handlePrayResult(resultNumber);
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -1)
	{
		//升级力量
		playerCharacterPtr->setStrength(
			playerCharacterPtr->getOriStrength() + 1
		);
		expHandler->useAttrPoint();
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -2)
	{
		//升级敏捷
		playerCharacterPtr->setAgility(
			playerCharacterPtr->getOriAgility() + 1
		);
		expHandler->useAttrPoint();
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -3)
	{
		//升级智力
		playerCharacterPtr->setIntellect(
			playerCharacterPtr->getOriIntellect() + 1
		);
		expHandler->useAttrPoint();
	}
}

void AIStatue::handlePray()
{
	//祈祷
	if (Player::getInstance()->getFaithValue() < 10)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith", characterPtr);
	}
	else
	{
		DialogueSystem::getInstance()->runDialogue("pray", characterPtr);
	}
}

void AIStatue::handleLevelUp()
{
	ExpHandler* expHandler = Player::getInstance()->getcharacterPtr()->getExphandler();

	if (expHandler->getCurAttrPoint() > 0)
	{
		DialogueSystem::getInstance()->runDialogue("levelUp", this->characterPtr);
	}
	else
	{
		DialogueSystem::getInstance()->runDialogue("noAttrPoint", this->characterPtr);
	}
}

void AIStatue::handlePrayResult(int resultNumber)
{
	switch (resultNumber)
	{
	case -1:
		giveWeapon();
		break;
	case -2:
		giveArmor();
		break;
	case -3:
		giveAccessory();
		break;
	case -4:
		giveInventory();
		break;
	case -5:
		giveHP();
		break;
	case -6:
		giveMP();
		break;
	default:
		break;
	}
}

void AIStatue::giveWeapon()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;


	if (roll<=1)
	{
		inventoryID = "sword004";
	}
	else if (roll>1 && roll<=5)
	{
		inventoryID = "sword014";
	}
	else if (roll>5 && roll<=9)
	{
		inventoryID = "sword015";
	}
	else if (roll>9 && roll <=30)
	{
		inventoryID = "sword003";
	}
	else if (roll>30 && roll<=60)
	{
		inventoryID = "sword002";
	}
	else if (roll>60 && roll<=80)
	{
		inventoryID = "sword001";
	}
	else
	{
		inventoryID = "sword007";
	}
	playerCharacter->addInventory(inventoryID);
	std::string inventoryCName = InventoryFactory::getInstance()->queryCname(inventoryID);
	HudMessageBox::getInstance()->addMessage(
		ToolFunction::WStr2UTF8(L"你获得了")
		+ inventoryCName
	);
}

void AIStatue::giveArmor()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;


	if (roll<=1)
	{
		inventoryID = "sword004";
	}
	else if (roll>1 && roll<=5)
	{
		inventoryID = "sword014";
	}
	else if (roll>5 && roll<=9)
	{
		inventoryID = "sword015";
	}
	else if (roll>9 && roll <=30)
	{
		inventoryID = "sword003";
	}
	else if (roll>30 && roll<=60)
	{
		inventoryID = "sword002";
	}
	else if (roll>60 && roll<=80)
	{
		inventoryID = "sword001";
	}
	else
	{
		inventoryID = "sword007";
	}
	playerCharacter->addInventory(inventoryID);
	std::string inventoryCName = InventoryFactory::getInstance()->queryCname(inventoryID);
	HudMessageBox::getInstance()->addMessage(
		ToolFunction::WStr2UTF8(L"你获得了")
		+ inventoryCName
	);


}

void AIStatue::giveAccessory()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");


}

void AIStatue::giveInventory()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");


}

void AIStatue::giveHP()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");


}

void AIStatue::giveMP()
{
	Player::getInstance()->reduceFaith(10);
	HudMessageBox::getInstance()->addMessage(L"你失去了10信仰点数");


}
