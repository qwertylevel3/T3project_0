#pragma once

#include "Singleton.h"

class ResourceManager:public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();
	void init();
protected:
	void initCharacterRes();
	void initHudRes();
	void initMaskRes();
};

