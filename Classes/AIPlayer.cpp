#include "AIPlayer.h"
#include "HudMessageBox.h"



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
	HudMessageBox::getInstance()->addMessage(L"you die...");
}
