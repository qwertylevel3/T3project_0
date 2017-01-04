#pragma once


#include <vector>

#include "XMLConfigure.h"
#include "Singleton.h"

class Character;

class HeroManager:public XMLConfigure,public Singleton<HeroManager>
{
public:
	HeroManager();
	~HeroManager();
	void init();
	void initMission();
	void restart();

protected:
	void clear();
	void initHero(const std::string& fileName);
	std::vector<Character*> heroBox;
};

