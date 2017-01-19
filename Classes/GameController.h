#pragma once

#include "Singleton.h"

class GameController:public Singleton<GameController>
{
public:
	GameController();
	~GameController();
	void init();
	void startMission();
	void nextMission();
	int getCurLevel();
	void startGame();
	void reStartGame();
	void endGame();
	void saveGame();
protected:
	int curLevel;
	bool firstPlay;
};

