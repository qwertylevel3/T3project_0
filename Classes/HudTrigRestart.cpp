#include "HudTrigRestart.h"
#include "KeyController.h"
#include "GameController.h"
#include "GameSaveManager.h"



HudTrigRestart::HudTrigRestart()
{
}


HudTrigRestart::~HudTrigRestart()
{
}

void HudTrigRestart::run()
{
	GameSaveManager::getInstance()->save();

	KeyController::getInstance()->switchCtrlToPlayer();

	KeyController::getInstance()->setBlock(true);
	GameController::getInstance()->reStartGame();
}
