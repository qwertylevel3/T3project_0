#include "DisabilitySphere.h"
#include "Character.h"
#include "BuffFactory.h"
#include "ToolFunction.h"
#include "Marco.h"
#include "BuffHandler.h"
#include "BuffBase.h"



Sphere::DisabilitySphere::DisabilitySphere()
{
}


Sphere::DisabilitySphere::~DisabilitySphere()
{
}

void Sphere::DisabilitySphere::run(Character* a, Character* b, int damage)
{
	std::wstring strWStr = ToolFunction::string2wstring(strOffset);
	std::wstring agiWStr = ToolFunction::string2wstring(agiOffset);
	std::wstring intWStr = ToolFunction::string2wstring(intOffset);

	std::wstring buffName = L"BaseAttrBuff_²Ð·Ï_ATTR_Bad_2_2_"+strWStr+L"_"+agiWStr+L"_"+intWStr;
	b->addBuff(ToolFunction::WStr2UTF8(buffName));
#ifdef SHOWMESSAGE
	std::cout << "@Sphere@ disability"<< std::endl;
#endif // SHOWMESSAGE
}

Sphere::DisabilitySphere* Sphere::DisabilitySphere::createProtoType()
{
	return new DisabilitySphere();
}

void Sphere::DisabilitySphere::initExtraMessage(std::vector<std::string> extraMessage)
{
	setStrOffset(extraMessage[0]);
	setAgiOffset(extraMessage[1]);
	setIntOffset(extraMessage[2]);
}
