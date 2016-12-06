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

std::string Sphere::VenomSphere::getDescription()
{
	return ToolFunction::WStr2UTF8(L"¶¾ÒºÖ®Çò\n")
		+ ToolFunction::WStr2UTF8(L"¹¥»÷¸½¼Ó")
		+ venomDamage + ToolFunction::WStr2UTF8(L"¶¾ÐÔÉËº¦");
}

void Sphere::VenomSphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setVenomDamage(extraMessage[0]);
}
