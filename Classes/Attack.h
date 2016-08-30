#pragma once

#include"Skill.h"
#include<vector>
#include <set>

class Attack:public Skill
{
public:
	Attack(Character* character);
	~Attack();
	int run();
	std::set<Character* > getAllTargetCharacter();
protected:
	void showEffect();
};

