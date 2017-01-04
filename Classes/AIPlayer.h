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
};

