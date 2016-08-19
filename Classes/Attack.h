#pragma once

#include"Skill.h"
#include<vector>

class Attack:public Skill
{
public:
	Attack(Character* character);
	~Attack();
	int run();
protected:
	void showEffect();
};

