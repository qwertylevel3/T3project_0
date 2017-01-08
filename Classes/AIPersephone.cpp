#include "AIPersephone.h"
#include "ToolFunction.h"
#include "DialogueSystem.h"
#include "GameController.h"
#include "Player.h"



AIPersephone::AIPersephone()
{
	talkFlag = 0;
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

	if (talkFlag==0
		&& ToolFunction::isNear8(characterPtr->getMapCoord(),
			Player::getInstance()->getcharacterPtr()->getMapCoord()))
	{
		DialogueSystem::getInstance()->runDialogue("talkPersephone");
		talkFlag = 1;
	}

	characterPtr->idle();
}


void AIPersephone::feedback(Character* character)
{

}

void AIPersephone::lastWords()
{

}
