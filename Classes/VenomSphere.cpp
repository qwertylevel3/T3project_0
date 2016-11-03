#include "VenomSphere.h"
#include "Character.h"
#include "BuffFactory.h"
#include "ToolFunction.h"
#include "Marco.h"


Sphere::VenomSphere::VenomSphere()
{
}


Sphere::VenomSphere::~VenomSphere()
{
}

void Sphere::VenomSphere::run(Character* a, Character* b, int damage)
{
	std::wstring damageWStr = ToolFunction::string2wstring(venomDamage);

	std::wstring buffName = L"HPBuff_ÖÐ¶¾_OnRoundStart_Bad_10_2_" + damageWStr;
	b->addBuff(ToolFunction::WStr2UTF8(buffName));
#ifdef SHOWMESSAGE
	std::cout << "@Sphere@ disability"<< std::endl;
#endif // SHOWMESSAGE
}

Sphere::VenomSphere* Sphere::VenomSphere::createProtoType()
{
	return new VenomSphere();
}

void Sphere::VenomSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setVenomDamage(extraMessage[0]);
}
