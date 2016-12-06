#include "SphereBase.h"
#include "ToolFunction.h"



Sphere::SphereBase::SphereBase()
{
}


Sphere::SphereBase::~SphereBase()
{
}

void Sphere::SphereBase::init(std::vector<std::string> sphereMessage)
{

	std::vector<std::string> baseMessage;
	std::vector<std::string > extraMessage;

	int i;
	for (i = 0; i < 1; i++)
	{
		baseMessage.push_back(sphereMessage[i]);
	}
	for (; i < sphereMessage.size(); i++)
	{
		extraMessage.push_back(sphereMessage[i]);
	}
	initBaseMessage(baseMessage);
	this->initExtraMessage(extraMessage);
}

std::string Sphere::SphereBase::getDescription()
{
	return ToolFunction::WStr2UTF8(L"Ã»ÓĞÃèÊö");
}

void Sphere::SphereBase::initBaseMessage(std::vector<std::string> baseMessage)
{
	cname = baseMessage[0];
}
