#pragma once

#include"Singleton.h"
#include"cocos2d.h"
#include<map>
#include"SkillTemp.h"


//discard
class SkillManager:public Singleton<SkillManager>
{
public:
	SkillManager();
	~SkillManager();
	void init();

	SkillTemp* getSkill(std::string skillName);
protected:
	void initSkill();
	std::map<std::string, SkillTemp*> skillBox;
};

