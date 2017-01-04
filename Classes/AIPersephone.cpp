#include "AIPersephone.h"
#include "GameController.h"



AIPersephone::AIPersephone()
{
}


AIPersephone::~AIPersephone()
{
}

void AIPersephone::update()
{
	if (!characterPtr)
	{
		return;
	}
	characterPtr->idle();
}


void AIPersephone::feedback(Character* character)
{
	characterPtr->speak(L"......");
}

void AIPersephone::lastWords()
{
	GameController::getInstance()->init();
	GameController::getInstance()->startMission();
}
