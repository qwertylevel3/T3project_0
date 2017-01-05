#pragma once


#include "Singleton.h"
#include "XMLConfigure.h"

class GameSaveManager:public XMLConfigure,public Singleton<GameSaveManager>
{
public:
	GameSaveManager();
	~GameSaveManager();
	void init();

	void load();
	void save();
	void output();
protected:
	int testFlag;
};

