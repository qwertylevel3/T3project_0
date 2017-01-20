#include "InventoryListGenerator.h"
#include "InventoryFactory.h"
#include "RandomNumber.h"

ActorInventoryList::ActorInventoryList()
{
}

ActorInventoryList::~ActorInventoryList()
{
}

std::vector<std::string> ActorInventoryList::generate()
{
	std::vector<std::string > inventoryList;

	for each (InvHandle invHandle in invHandleList)
	{
		int roll = RandomNumber::getInstance()->randomInt(0, 100);

		if (roll < invHandle.pro)
		{
			inventoryList.push_back(invHandle.inventoryID);
		}
	}
	return inventoryList;
}

void ActorInventoryList::addInvHandle(InvHandle invHandle)
{
	invHandleList.push_back(invHandle);
}

//////////////////////////////////////////////////////////////////////////

InventoryListGenerator::InventoryListGenerator()
{
}

InventoryListGenerator::~InventoryListGenerator()
{
}

void InventoryListGenerator::init()
{
}

std::vector<std::string> InventoryListGenerator::getInventoryList(std::string actorName)
{
	if (actorName=="slime")
	{
		return generateSlimeInvList();
	}
	else if (actorName=="snack")
	{
		return generateSnackInvList();
	}
	else if (actorName=="blackSnack")
	{
		return generateBlackSnackInvList();
	}
	else if (actorName=="ghost")
	{
		return generateGhostInvList();
	}
	else if (actorName=="ents")
	{
		return generateEntsInvList();
	}
	else if (actorName=="demon")
	{
		return generateDemonInvList();
	}
	else if (actorName=="destroyWizard" || actorName=="summonWizard")
	{
		return generateWizardInvList();
	}
	else if (actorName=="chest1")
	{
		return generateChest1();
	}
	else if (actorName=="chest2")
	{
		return generateChest2();
	}
	else if (actorName=="chest3")
	{
		return generateChest3();
	}
	else if (actorName=="chest4")
	{
		return generateChest4();
	}
	else if (actorName=="chest5")
	{
		return generateChest5();
	}
	else if (actorName=="chest6")
	{
		return generateChest6();
	}
	else if (actorName=="chest7")
	{
		return generateChest7();
	}
	else if (actorName=="chest8")
	{
		return generateChest8();
	}
	else if (actorName=="chest9")
	{
		return generateChest9();
	}

	else
	{
		std::vector<std::string > temp;
		return temp;
	}
}


std::string InventoryListGenerator::getRandomInv(int level, int pro)
{
	int roll = RandomNumber::getInstance()->randomInt(1, 100);
	if (roll <= pro)
	{
		return InventoryFactory::getInstance()->getRandomInventory(level);
	}
	return "";
}

std::vector<std::string > InventoryListGenerator::generateSlimeInvList()
{
	std::vector<std::string > invList;

	std::string level1Inv = getRandomInv(1, 80);
	addInv2List(level1Inv, invList);

	std::string level2Inv = getRandomInv(2, 20);
	addInv2List(level2Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateSnackInvList()
{
	std::vector<std::string > invList;

	std::string level1Inv = getRandomInv(1, 20);
	addInv2List(level1Inv, invList);

	std::string level2Inv = getRandomInv(2, 80);
	addInv2List(level2Inv, invList);

	std::string level3Inv = getRandomInv(3, 10);
	addInv2List(level3Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateBlackSnackInvList()
{
	std::vector<std::string > invList;

	std::string level3Inv = getRandomInv(3, 20);
	addInv2List(level3Inv, invList);

	std::string level4Inv = getRandomInv(4, 50);
	addInv2List(level4Inv, invList);

	std::string level5Inv = getRandomInv(5, 20);
	addInv2List(level5Inv, invList);
	return invList;
}


std::vector<std::string > InventoryListGenerator::generateGhostInvList()
{
	std::vector<std::string > invList;

	std::string level3Inv = getRandomInv(3, 20);
	addInv2List(level3Inv, invList);

	std::string level4Inv = getRandomInv(4, 20);
	addInv2List(level4Inv, invList);

	std::string level5Inv = getRandomInv(5, 20);
	addInv2List(level5Inv, invList);
	return invList;
}

std::vector<std::string > InventoryListGenerator::generateDemonInvList()
{
	std::vector<std::string > invList;


	std::string level5Inv = getRandomInv(5, 50);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 50);
	addInv2List(level6Inv, invList);

	std::string level7Inv = getRandomInv(7, 10);
	addInv2List(level7Inv, invList);

	std::string level8Inv = getRandomInv(8, 5);
	addInv2List(level8Inv, invList);


	return invList;
}

std::vector<std::string > InventoryListGenerator::generateWizardInvList()
{
	std::vector<std::string > invList;

	std::string level5Inv = getRandomInv(5, 50);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 50);
	addInv2List(level6Inv, invList);

	std::string level7Inv = getRandomInv(7, 10);
	addInv2List(level7Inv, invList);

	std::string level8Inv = getRandomInv(8, 5);
	addInv2List(level8Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateEntsInvList()
{
	std::vector<std::string > invList;

	std::string level4Inv = getRandomInv(4, 50);
	addInv2List(level4Inv, invList);

	std::string level5Inv = getRandomInv(5, 50);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 50);
	addInv2List(level6Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest1()
{
	std::vector<std::string > invList;

	std::string level1Inv = getRandomInv(1, 100);
	addInv2List(level1Inv, invList);

	std::string level2Inv = getRandomInv(2, 50);
	addInv2List(level2Inv, invList);

	std::string level3Inv = getRandomInv(3, 10);
	addInv2List(level3Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest2()
{
	std::vector<std::string > invList;

	std::string level2Inv1 = getRandomInv(2, 100);
	addInv2List(level2Inv1, invList);

	std::string level2Inv2 = getRandomInv(2, 80);
	addInv2List(level2Inv2, invList);

	std::string level3Inv = getRandomInv(3, 50);
	addInv2List(level3Inv, invList);

	std::string level4Inv = getRandomInv(4, 5);
	addInv2List(level4Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest3()
{
	std::vector<std::string > invList;

	std::string level3Inv1 = getRandomInv(3, 100);
	addInv2List(level3Inv1, invList);

	std::string level3Inv2 = getRandomInv(3, 40);
	addInv2List(level3Inv2, invList);

	std::string level4Inv = getRandomInv(4, 40);
	addInv2List(level4Inv, invList);

	std::string level5Inv = getRandomInv(5, 10);
	addInv2List(level5Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest4()
{
	std::vector<std::string > invList;

	std::string level4Inv1 = getRandomInv(4, 100);
	addInv2List(level4Inv1, invList);

	std::string level5Inv = getRandomInv(5, 40);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 10);
	addInv2List(level6Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest5()
{
	std::vector<std::string > invList;

	std::string level4Inv = getRandomInv(4, 80);
	addInv2List(level4Inv, invList);

	std::string level5Inv = getRandomInv(5, 100);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 40);
	addInv2List(level6Inv, invList);

	std::string level7Inv = getRandomInv(7, 10);
	addInv2List(level7Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest6()
{
	std::vector<std::string > invList;

	std::string level5Inv = getRandomInv(5, 80);
	addInv2List(level5Inv, invList);

	std::string level6Inv = getRandomInv(6, 100);
	addInv2List(level6Inv, invList);

	std::string level7Inv = getRandomInv(7, 8);
	addInv2List(level7Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest7()
{
	std::vector<std::string > invList;

	std::string level6Inv1 = getRandomInv(6, 100);
	addInv2List(level6Inv1, invList);

	std::string level6Inv2 = getRandomInv(6, 30);
	addInv2List(level6Inv2, invList);
	
	std::string level7Inv = getRandomInv(7, 30);
	addInv2List(level7Inv, invList);

	std::string level8Inv = getRandomInv(8, 2);
	addInv2List(level8Inv, invList);

	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest8()
{
	std::vector<std::string > invList;

	std::string level7Inv = getRandomInv(7, 100);
	addInv2List(level7Inv, invList);

	std::string level8Inv = getRandomInv(8, 10);
	addInv2List(level8Inv, invList);


	return invList;
}

std::vector<std::string > InventoryListGenerator::generateChest9()
{
	std::vector<std::string > invList;

	std::string level7Inv = getRandomInv(7, 100);
	addInv2List(level7Inv, invList);

	std::string level8Inv = getRandomInv(8, 15);
	addInv2List(level8Inv, invList);

	std::string level9Inv = getRandomInv(9, 1);
	addInv2List(level9Inv, invList);

	return invList;
}

void InventoryListGenerator::addInv2List(std::string invName, std::vector<std::string >& invList)
{
	if (invName != "")
	{
		invList.push_back(invName);
	}
}
