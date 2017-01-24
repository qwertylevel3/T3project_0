#pragma once

#include "Singleton.h"
#include "XMLConfigure.h"
#include <vector>
#include <map>

class ActorInventoryList
{
public:
	struct InvHandle
	{
		std::string inventoryID;
		int pro;
	};
	ActorInventoryList();
	~ActorInventoryList();

	std::vector<std::string> generate();
	void addInvHandle(InvHandle invHandle);
protected:
	std::vector<InvHandle> invHandleList;
};

class InventoryListGenerator:public XMLConfigure,public Singleton<InventoryListGenerator>
{
public:
	InventoryListGenerator();
	~InventoryListGenerator();
	void init();

	//根据actorName分配特定的inventoryList<inventory id>
	std::vector<std::string> getInventoryList(std::string actorName);
protected:
	//pro概率出现随机level物品
	std::string getRandomInv(int level, int pro);
	std::string getRandomNote();

	void addInv2List(std::string invName,std::vector<std::string >& invList);

	std::vector<std::string > generateSlimeInvList();
	std::vector<std::string > generateSnackInvList();
	std::vector<std::string > generateBlackSnackInvList();
	std::vector<std::string > generateGhostInvList();
	std::vector<std::string > generateDemonInvList();
	std::vector<std::string > generateWizardInvList();
	std::vector<std::string > generateEntsInvList();

	std::vector<std::string > generateChest1();
	std::vector<std::string > generateChest2();
	std::vector<std::string > generateChest3();
	std::vector<std::string > generateChest4();
	std::vector<std::string > generateChest5();
	std::vector<std::string > generateChest6();
	std::vector<std::string > generateChest7();
	std::vector<std::string > generateChest8();
	std::vector<std::string > generateChest9();
};
