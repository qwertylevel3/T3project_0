#include "ManaBurnSphere.h"
#include "Character.h"
#include "ToolFunction.h"



Sphere::ManaBurnSphere::ManaBurnSphere()
{
}


Sphere::ManaBurnSphere::~ManaBurnSphere()
{
}

void Sphere::ManaBurnSphere::run(Character* a, Character* b, int damage)
{
	double mpDamageValue = -double(damage)*(double(mpDamagePer) / 100.0);
	a->sufferMPEffect(int(mpDamageValue));
}

Sphere::ManaBurnSphere* Sphere::ManaBurnSphere::createProtoType()
{
	return new ManaBurnSphere();
}

void Sphere::ManaBurnSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setMpDamagePer(ToolFunction::string2int(extraMessage[0]));
}
