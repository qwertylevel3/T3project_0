#pragma once

#include"Singleton.h"

class Debug:public Singleton<Debug>
{
public:
	Debug();
	~Debug();
	bool getDebugFlag();
	void setDebugFlag(bool f);
private:
	bool debugFlag;
};
