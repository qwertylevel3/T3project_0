#pragma once

#include "Singleton.h"

class BattleTest:public Singleton<BattleTest>
{
public:
	BattleTest();
	~BattleTest();
	void init();
	void run();
};

