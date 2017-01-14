#include "InventoryListGenerator.h"
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
	tinyxml2::XMLDocument doc;
	doc.LoadFile("actorInvList.xml");

	tinyxml2::XMLElement* allListElement = doc.RootElement();
	tinyxml2::XMLElement* inventoryListElement = allListElement->FirstChildElement();

	while (inventoryListElement)
	{
		generateActorInvList(inventoryListElement);

		inventoryListElement = inventoryListElement->NextSiblingElement();
	}
}

std::vector<std::string> InventoryListGenerator::getInventoryList(std::string actorName)
{
	if (allActorInvList.count(actorName) > 0)
	{
		return allActorInvList[actorName].generate();
	}
	else
	{
		std::vector<std::string > temp;
		return temp;
	}
}

void InventoryListGenerator::generateActorInvList(tinyxml2::XMLElement* invListElement)
{
	ActorInventoryList invList;

	tinyxml2::XMLElement* actorNameElement = invListElement->FirstChildElement("actorName");
	std::string actorName = actorNameElement->GetText();

	tinyxml2::XMLElement* listElement = invListElement->FirstChildElement("list");
	tinyxml2::XMLElement* inventoryElement = listElement->FirstChildElement("inventory");

	while (inventoryElement)
	{
		std::string invID = getChildElementStrAttr(inventoryElement, "inventoryID");
		int pro = getChildElementIntAttr(inventoryElement, "pro");

		ActorInventoryList::InvHandle invHandle;
		invHandle.inventoryID = invID;
		invHandle.pro = pro;

		invList.addInvHandle(invHandle);

		inventoryElement = inventoryElement->NextSiblingElement();
	}

	allActorInvList[actorName] = invList;
}