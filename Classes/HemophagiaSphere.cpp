#include "HemophagiaSphere.h"
#include "Character.h"
#include "ToolFunction.h"



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
}

Sphere::SphereBase* Sphere::HemophagiaSphere::makeProtoType()
{
	HemophagiaSphere* sphere = new HemophagiaSphere();
	return sphere;
}

void Sphere::HemophagiaSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	healPer = ToolFunction::string2int(extraMessage[0]);
}
