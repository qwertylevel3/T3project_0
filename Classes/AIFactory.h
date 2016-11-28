#pragma once

#include "Singleton.h"
#include <string>

class AIBase;

class AIFactory:public Singleton<AIFactory>
{
public:
	AIFactory();
	~AIFactory();
	AIBase* getAI(const std::string& AIName);
};

