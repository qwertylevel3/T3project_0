#include "BuffFactory.h"
#include "BuffBase.h"
#include "HPBuff.h"



Buff::BuffFactory::BuffFactory()
{
}

Buff::BuffFactory::~BuffFactory()
{
	std::map<std::string, BuffBase*>::iterator iter = buffPrototypeBox.begin();
	while (iter != buffPrototypeBox.end())
	{
		delete iter->second;
		iter++;
	}
}

void Buff::BuffFactory::init()
{
	HPBuff* hpBuffPrototype = new HPBuff();
	buffPrototypeBox["HPBuff"] = hpBuffPrototype;
}

Buff::BuffBase* Buff::BuffFactory::getBuff(std::string b)
{
	std::vector<std::string> buffMessage;
	split(b, '_', buffMessage);

	if (b.empty())
	{
		return nullptr;
	}

	BuffBase* buff = getBuffPrototype(buffMessage[0]);
	buffMessage.erase(buffMessage.begin());//remove buff name
	buff->init(buffMessage);
	buff->setID(b);
	return buff;
}

Buff::BuffBase* Buff::BuffFactory::getBuffPrototype(const std::string& buffName)
{
	return buffPrototypeBox[buffName];
}

void Buff::BuffFactory::split(std::string s, char splitchar, std::vector<std::string>& vec)
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
