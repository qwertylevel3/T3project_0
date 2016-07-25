#include "SkillManager.h"
#include"Attack.h"


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

Skill * SkillManager::getSkill(std::string skillName)
{
	return skillBox[skillName];
}

void SkillManager::initSkill()
{
}
