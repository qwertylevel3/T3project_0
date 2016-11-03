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

void Sphere::MagicphagiaSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setHealPer(ToolFunction::string2int(extraMessage[0]));
}
