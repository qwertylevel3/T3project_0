#pragma once

#include"Singleton.h"
#include"cocos2d.h"
#include<map>
#include"Skill.h"


//discard
class SkillManager:public Singleton<SkillManager>
{
public:
	SkillManager();
	~SkillManager();
	void init();

	Skill* getSkill(std::string skillName);
protected:
	void initSkill();
	std::map<std::string, Skill*> skillBox;
};

