#include "InventoryBuffHandler.h"



InventoryBuffHandler::InventoryBuffHandler()
{
}


InventoryBuffHandler::~InventoryBuffHandler()
{
}

void InventoryBuffHandler::addBuff(std::string buffID)
{
	buffIDBox.push_back(buffID);
}

std::vector<std::string>& InventoryBuffHandler::getBuffIDBox()
{
	return buffIDBox;
}
