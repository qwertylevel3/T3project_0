#include "SphereFactory.h"
#include "SphereBase.h"
#include "HemophagiaSphere.h"
#include "DisabilitySphere.h"
#include "MagicphagiaSphere.h"
#include "VenomSphere.h"
#include "ManaBurnSphere.h"
#include "AntiChantSphere.h"
#include "base/ccMacros.h"



Sphere::SphereFactory::SphereFactory()
{
}


Sphere::SphereFactory::~SphereFactory()
{
	std::map<std::string, SphereBase*>::iterator iter = sphereBox.begin();
	while (iter != sphereBox.end())
	{
		delete iter->second;
		iter++;
	}
}

void Sphere::SphereFactory::init()
{
	HemophagiaSphere* hemoSphere = new HemophagiaSphere();
	MagicphagiaSphere* magicphagiaSphere = new MagicphagiaSphere();
	DisabilitySphere* disabilitySphere = new DisabilitySphere();
	VenomSphere* venomSphere = new VenomSphere();
	ManaBurnSphere* manaBurnSphere = new ManaBurnSphere();
	AntiChantSphere* antiChantSphere = new AntiChantSphere();


	sphereBox["HemophagiaSphere"] = hemoSphere;
	sphereBox["DisabilitySphere"] = disabilitySphere;
	sphereBox["MagicphagiaSphere"] = magicphagiaSphere;
	sphereBox["VenomSphere"] = venomSphere;
	sphereBox["ManaBurnSphere"] = manaBurnSphere;
	sphereBox["AntiChantSphere"] = antiChantSphere;
}

Sphere::SphereBase* Sphere::SphereFactory::getSphere(const std::string& sphereID)
{
//	std::string b=ToolFunction::WStr2UTF8(buffName);
	std::vector<std::string> sphereMessage;
	split(sphereID, '_', sphereMessage);

	if (sphereMessage.empty())
	{
		return nullptr;
	}

	SphereBase* sphere = sphereBox[sphereMessage[0]]->createProtoType();
	sphereMessage.erase(sphereMessage.begin());//remove sphere name
	sphere->init(sphereMessage);
	sphere->setID(sphereID);
	return sphere;
}

void Sphere::SphereFactory::split(std::string s, char splitchar, std::vector<std::string>& vec)
{
	if (vec.size() > 0)//保证vec是空的
		vec.clear();
	int length = s.length();
	int start = 0;
	for (int i = 0; i < length; i++)
	{
		if (s[i] == splitchar && i == 0)//第一个就遇到分割符
		{
			start += 1;
		}
		else if (s[i] == splitchar)
		{
			vec.push_back(s.substr(start, i - start));
			start = i + 1;
		}
		else if (i == length - 1)//到达尾部
		{
			vec.push_back(s.substr(start, i + 1 - start));
		}
	}
}
