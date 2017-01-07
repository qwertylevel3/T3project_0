#include "AIPersephone.h"
#include "DialogueSystem.h"
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
	DialogueSystem::getInstance()->runDialogue("talkPersephone");
}

void AIPersephone::lastWords()
{

}
