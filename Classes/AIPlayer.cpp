#include "AIPlayer.h"
#include "SplashLayer.h"
#include "GameController.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"



AIPlayer::AIPlayer()
{
}


AIPlayer::~AIPlayer()
{
}

void AIPlayer::update()
{

}

void AIPlayer::lastWords()
{
//	HudMessageBox::getInstance()->addMessage(L"you die...");
	DialogueSystem::getInstance()->runDialogue("playerDie",characterPtr);
}

void AIPlayer::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	GameController::getInstance()->reStartGame();
}

void AIPlayer::levelUp()
{
	HudMessageBox::getInstance()->addMessage(L"ÄãÉı¼¶ÁË");
}

