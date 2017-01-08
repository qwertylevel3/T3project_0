#pragma once

#include"Inventory.h"

class Accessory:public Inventory
{
public:
	Accessory();
	~Accessory();

	void equipAccessory(Character* character);

	Accessory* clone();
};

