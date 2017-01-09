#pragma once

#include "AIBase.h"

//¸¨Öúplayer¿ØÖÆ
class AIPlayer:public AIBase
{
public:
	AIPlayer();
	~AIPlayer();
	void update();
	void lastWords();
	void handleDialogueResult(std::string dialogueName, int resultNumber);
	void levelUp();
};

