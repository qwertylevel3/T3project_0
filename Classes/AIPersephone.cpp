#include "AIPersephone.h"



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
