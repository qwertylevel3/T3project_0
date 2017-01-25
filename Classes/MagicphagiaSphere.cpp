#include "MagicphagiaSphere.h"
#include "Character.h"
#include "ToolFunction.h"
#include "Marco.h"



Sphere::MagicphagiaSphere::MagicphagiaSphere()
{
}


Sphere::MagicphagiaSphere::~MagicphagiaSphere()
{
}

void Sphere::MagicphagiaSphere::run(Character* a, Character* b, int damage)
{
	double healValue = double(damage)*(double(healPer) / 100.0);
	healValue = healValue < 1 ? 1 : healValue;
	a->sufferMPEffect(int(healValue));
#ifdef SHOWMESSAGE
	std::cout << "@Sphere@ Magicphagia:" << healValue << std::endl;
#endif // SHOWMESSAGE
}

Sphere::MagicphagiaSphere* Sphere::MagicphagiaSphere::createProtoType()
{
	return new Sphere::MagicphagiaSphere();
}

std::string Sphere::MagicphagiaSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"魔法汲取:\n")
		+ ToolFunction::WStr2UTF8(L"每次攻击回复:[")
		+ ToolFunction::WStr2UTF8(L"伤害 x ") + ToolFunction::int2string(healPer)
		+ " " + ToolFunction::WStr2UTF8(L"%]魔法值");
}

void Sphere::MagicphagiaSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setHealPer(ToolFunction::string2int(extraMessage[0]));
}
