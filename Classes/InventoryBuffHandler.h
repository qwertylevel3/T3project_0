#pragma once

#include <string>
#include <vector>

class InventoryBuffHandler
{
public:
	InventoryBuffHandler();
	~InventoryBuffHandler();
	void addBuff(std::string buffID);
	std::vector<std::string>& getBuffIDBox();
protected:
	std::vector<std::string> buffIDBox;
};

