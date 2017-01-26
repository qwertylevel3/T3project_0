#include "AIShrine.h"
#include "Player.h"

AIShrine::AIShrine()
{
	light = false;
}

AIShrine::~AIShrine()
{
}

void AIShrine::update()
{
	if (!light && isPlayerNear())
	{
		characterPtr->speak(L"按E点亮");
		characterPtr->idle();
	}
	else
	{
		characterPtr->idle();
	}
}

void AIShrine::feedback(Character* character)
{
	if (!light)
	{
		characterPtr->setViewSize(4);
		light = true;
		//设置为点亮的sprite
		characterPtr->setOrientationUp();
		Player::getInstance()->addFaith(1);
		characterPtr->hideSpeakLabel();
	}
}