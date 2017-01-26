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
				L"ViewSizeBuff_女神祝福_ATTR_Good_1_40_1"
			)
		);
		character->sufferHPEffect(400);
		character->sufferMPEffect(400);

		HudMessageBox::getInstance()->addMessage(L"你获得了祝福");
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
	else if (dialogueName=="statueTalk"
		&& resultNumber==-3)
	{
		return;
	}
	else if (dialogueName == "pray")
	{
		handlePrayResult(resultNumber);
	}
	else if (dialogueName=="praySkillBook")
	{
		handlePraySkillBook(resultNumber);
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -1)
	{
		//升级力量
		playerCharacterPtr->setStrength(
			playerCharacterPtr->getOriStrength() + 1
		);
		expHandler->useAttrPoint();
		HudMessageBox::getInstance()->addMessage(L"你增加了一点力量");
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -2)
	{
		//升级敏捷
		playerCharacterPtr->setAgility(
			playerCharacterPtr->getOriAgility() + 1
		);
		expHandler->useAttrPoint();
		HudMessageBox::getInstance()->addMessage(L"你增加了一点敏捷");
	}
	else if (dialogueName == "levelUp"
		&& resultNumber == -3)
	{
		//升级智力
		playerCharacterPtr->setIntellect(
			playerCharacterPtr->getOriIntellect() + 1
		);
		expHandler->useAttrPoint();
		HudMessageBox::getInstance()->addMessage(L"你增加了一点智力");
	}
	else if (dialogueName=="levelUp"
		&& resultNumber==-4)
	{
		return;
	}
}

void AIStatue::handlePray()
{
	DialogueSystem::getInstance()->runDialogue("pray", characterPtr);
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
		giveWand();
		break;
	case -3:
		giveArmor();
		break;
	case -4:
		giveAccessory();
		break;
	case -5:
		giveHP();
		break;
	case -6:
		giveMP();
		break;
	case -7:
		DialogueSystem::getInstance()->runDialogue("praySkillBook",characterPtr);
		break;
	default:
		break;
	}
}

void AIStatue::handlePraySkillBook(int resultNumber)
{
	switch (resultNumber)
	{
	case -1:
		giveFireBallBook();
		break;
	case -2:
		giveRandomDamageBook();
		break;
	case -3:
		giveThunderBook();
		break;
	case -4:
		giveHealSelfBook();
		break;
	case -5:
		giveHealCastBook();
		break;
	case -6:
		giveYellowBook();
		break;
	default:
		break;
	}

}

void AIStatue::giveWeapon()
{
	if (Player::getInstance()->getFaithValue()<25)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(25);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;

	if (roll <= 90)
	{
		inventoryID = "sword027";
	}
	else if (roll > 90 && roll <= 95)
	{
		inventoryID = "sword022";
	}
	else
	{
		inventoryID = "sword004";
	}

	playerCharacter->addInventory(inventoryID);
	std::string inventoryCName = InventoryFactory::getInstance()->queryCname(inventoryID);
	HudMessageBox::getInstance()->addMessage(
		ToolFunction::WStr2UTF8(L"你获得了")
		+ inventoryCName
	);
}

void AIStatue::giveWand()
{
	if (Player::getInstance()->getFaithValue()<25)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}
	Player::getInstance()->reduceFaith(25);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;

	if (roll <= 90)
	{
		inventoryID = "sword032";
	}
	else if (roll > 90 && roll <= 95)
	{
		inventoryID = "sword017";
	}
	else
	{
		inventoryID = "sword018";
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
	if (Player::getInstance()->getFaithValue()<25)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(25);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;

	if (roll <= 90)
	{
		inventoryID = "armor011";
	}
	else if (roll > 90 && roll <= 95)
	{
		inventoryID = "armor008";
	}
	else
	{
		inventoryID = "armor015";
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
	if (Player::getInstance()->getFaithValue()<25)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(25);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	std::string inventoryID;

	if (roll <= 90)
	{
		inventoryID = "accessory014";
	}
	else if (roll > 90 && roll <= 95)
	{
		inventoryID = "accessory015";
	}
	else
	{
		inventoryID = "accessory000";
	}

	playerCharacter->addInventory(inventoryID);
	std::string inventoryCName = InventoryFactory::getInstance()->queryCname(inventoryID);
	HudMessageBox::getInstance()->addMessage(
		ToolFunction::WStr2UTF8(L"你获得了")
		+ inventoryCName
	);
}

void AIStatue::giveFireBallBook()
{
	if (Player::getInstance()->getFaithValue()<10)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(10);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("skillBook000");
	HudMessageBox::getInstance()->addMessage(L"你获得了火球术之书");


}

void AIStatue::giveRandomDamageBook()
{
	if (Player::getInstance()->getFaithValue()<15)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(15);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("skillBook001");
	HudMessageBox::getInstance()->addMessage(L"你获得了随机闪电之书");


}

void AIStatue::giveThunderBook()
{
	if (Player::getInstance()->getFaithValue()<20)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(20);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("skillBook002");
	HudMessageBox::getInstance()->addMessage(L"你获得了闪电风暴之书");


}

void AIStatue::giveHealSelfBook()
{
	if (Player::getInstance()->getFaithValue()<15)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(15);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("skillBook004");
	HudMessageBox::getInstance()->addMessage(L"你获得了自愈之书");


}

void AIStatue::giveHealCastBook()
{
	if (Player::getInstance()->getFaithValue()<15)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(15);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("skillBook005");
	HudMessageBox::getInstance()->addMessage(L"你获得了治疗之书");

}

void AIStatue::giveYellowBook()
{
	if (Player::getInstance()->getFaithValue()<40)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(40);

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	playerCharacter->addInventory("scroll003");
	HudMessageBox::getInstance()->addMessage(L"你获得了黄色魔法书");


}

void AIStatue::giveHP()
{
	if (Player::getInstance()->getFaithValue()<5)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}


	Player::getInstance()->reduceFaith(5);
	HudMessageBox::getInstance()->addMessage(L"你失去了5信仰点数");

	Player::getInstance()->getcharacterPtr()->sufferHPEffect(999);
}

void AIStatue::giveMP()
{
	if (Player::getInstance()->getFaithValue()<5)
	{
		DialogueSystem::getInstance()->runDialogue("noFaith");
		return;
	}

	Player::getInstance()->reduceFaith(5);
	HudMessageBox::getInstance()->addMessage(L"你失去了5信仰点数");

	Player::getInstance()->getcharacterPtr()->sufferMPEffect(999);
}