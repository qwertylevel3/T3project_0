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
	std::map<std::string, ActorInventoryList> allActorInvList;
	void generateActorInvList(tinyxml2::XMLElement* invListElement);
};
