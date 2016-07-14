#pragma once

#include"Skill.h"

class Attack:public Skill
{
public:
	Attack(Character* character);
	~Attack();
	int run();
};

