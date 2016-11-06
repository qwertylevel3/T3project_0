#pragma once

#include "Singleton.h"

class GameController:public Singleton<GameController>
{
public:
	GameController();
	~GameController();
	void init();
	void startMission(int level);
};

