#include "ActiveSkilllSphere.h"
#include "SkillFactory.h"
#include "ToolFunction.h"
#include "RandomNumber.h"
#include "Character.h"

Sphere::ActiveSkilllSphere::ActiveSkilllSphere()
{
}

Sphere::ActiveSkilllSphere::~ActiveSkilllSphere()
{
}

void Sphere::ActiveSkilllSphere::run(Character* a, Character* b, int damage)
{
	int roll = RandomNumber::getInstance()->randomInt(1, 100);

	if (roll <= activePro)
	{
		a->runSkillNoProcess(skillID);
	}
}

Sphere::ActiveSkilllSphere* Sphere::ActiveSkilllSphere::createProtoType()
{
	return new ActiveSkilllSphere();
}

std::string Sphere::ActiveSkilllSphere::getDescription()
{
	std::string skillCname = Skill::SkillFactory::getInstance()->querySkillCname(skillID);

	return ToolFunction::WStr2UTF8(L"法球技能:\n")
		+ ToolFunction::WStr2UTF8(L"每次攻击有")
		+ ToolFunction::int2string(activePro)
		+ ToolFunction::WStr2UTF8(L"%几率触发")
		+ skillCname;
}

void Sphere::ActiveSkilllSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	activePro = ToolFunction::string2int(extraMessage[0]);

	skillID = extraMessage[1];

	for (int i = 2; i < extraMessage.size(); i++)
	{
		skillID += "_" + extraMessage[i];
	}
}