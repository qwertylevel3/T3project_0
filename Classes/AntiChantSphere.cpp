#include "AntiChantSphere.h"
#include "RandomNumber.h"
#include "Character.h"
#include "ToolFunction.h"

Sphere::AntiChantSphere::AntiChantSphere()
{
}

Sphere::AntiChantSphere::~AntiChantSphere()
{
}

void Sphere::AntiChantSphere::run(Character* a, Character* b, int damage)
{

	int roll = RandomNumber::getInstance()->randomInt(1, 100);

	if (roll <= chantClearPro)
	{
		b->clearChant();
	}
}

Sphere::AntiChantSphere* Sphere::AntiChantSphere::createProtoType()
{
	return  new AntiChantSphere();
}

std::string Sphere::AntiChantSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"反吟唱:\n")
		+ ToolFunction::WStr2UTF8(L"每次攻击有:")
		+ ToolFunction::int2string(chantClearPro)
		+ "%"
		+ ToolFunction::WStr2UTF8(L"几率消除对方吟唱点数");
}

void Sphere::AntiChantSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setChantClearPro(ToolFunction::string2int(extraMessage[0]));
}
