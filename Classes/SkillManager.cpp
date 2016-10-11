#include "SkillManager.h"
#include"AttackTemp.h"


USING_NS_CC;

SkillManager::SkillManager()
{
}


SkillManager::~SkillManager()
{
}

void SkillManager::init()
{
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("attack.plist");
	initSkill();
}

SkillTemp * SkillManager::getSkill(std::string skillName)
{
	return skillBox[skillName];
}

void SkillManager::initSkill()
{
}
