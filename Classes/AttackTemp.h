#pragma once

#include"SkillTemp.h"
#include<vector>
#include <set>

class AttackTemp:public SkillTemp
{
public:
	AttackTemp(Character* character);
	~AttackTemp();
	int run();
	std::set<Character* > getAllTargetCharacter();
protected:
	void showEffect();
};

