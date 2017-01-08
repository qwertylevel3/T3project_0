#include "HemophagiaSphere.h"
#include "Character.h"
#include "ToolFunction.h"
#include "Marco.h"



Sphere::HemophagiaSphere::HemophagiaSphere()
{
	healPer = 0;
}


Sphere::HemophagiaSphere::~HemophagiaSphere()
{
}

void Sphere::HemophagiaSphere::run(Character* a, Character* b, int damage)
{
	double healValue = double(damage)*(double(healPer) / 100.0);
	healValue = healValue < 1 ? 1 : healValue;
	a->sufferHPEffect(int(healValue));
#ifdef SHOWMESSAGE
	std::cout << "@Sphere@ hemo HP:" << healValue << std::endl;
#endif // SHOWMESSAGE
}

Sphere::HemophagiaSphere* Sphere::HemophagiaSphere::createProtoType()
{
	return new HemophagiaSphere();
}

std::string Sphere::HemophagiaSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"吸血法球:\n")
		+ ToolFunction::WStr2UTF8(L"每次攻击回复:")
		+ ToolFunction::WStr2UTF8(L"伤害x") + ToolFunction::int2string(healPer)
		+ "% " + ToolFunction::WStr2UTF8(L"生命值");
}

void Sphere::HemophagiaSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	healPer = ToolFunction::string2int(extraMessage[0]);
}
