#include "BuffFactory.h"
#include "BuffBase.h"
#include "HPBuff.h"
#include "MPBuff.h"
#include "BaseAttrBuff.h"
#include "MaxHPBuff.h"
#include "MaxMPBuff.h"
#include "LuckBuff.h"
#include "ViewSizeBuff.h"
#include "EvadeBuff.h"
#include "AccuracyBuff.h"
#include "CriticalProBuff.h"
#include "CriticalPointBuff.h"
#include "CriticalPerBuff.h"
#include "BlockProBuff.h"
#include "BlockPointBuff.h"
#include "ComboBuff.h"
#include "WeightBuff.h"
#include "ToolFunction.h"



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
	MPBuff* mpBuffPrototype = new MPBuff();
	BaseAttrBuff* attrBuffPrototype = new BaseAttrBuff();
	MaxHPBuff* maxHPBuffPrototype = new MaxHPBuff();
	MaxMPBuff* maxMPBuffPrototype = new MaxMPBuff();
	LuckBuff* luckBuffPrototype = new LuckBuff();
	ViewSizeBuff* viewBuffPrototype = new ViewSizeBuff();
	EvadeBuff* evadeBuffPrototype = new EvadeBuff();
	AccuracyBuff* accuracyBuffPrototype = new AccuracyBuff();
	CriticalProBuff* criticalProBuffPrototype = new CriticalProBuff();
	CriticalPointBuff* criticalPointBuffPrototype = new CriticalPointBuff();
	CriticalPerBuff* criticalPerBuffPrototype = new CriticalPerBuff();
	BlockProBuff* blockProBuffPrototype = new BlockProBuff();
	BlockPointBuff* blockPointBuffPrototype = new BlockPointBuff();
	ComboBuff* comboBuffPrototype = new ComboBuff();
	WeightBuff* weightBuffPrototype = new WeightBuff();

	buffPrototypeBox["HPBuff"] = hpBuffPrototype;
	buffPrototypeBox["MPBuff"] = mpBuffPrototype;
	buffPrototypeBox["BaseAttrBuff"] = attrBuffPrototype;
	buffPrototypeBox["MaxHPBuff"] = maxHPBuffPrototype;
	buffPrototypeBox["MaxMPBuff"] = maxMPBuffPrototype;
	buffPrototypeBox["LuckBuff"] = luckBuffPrototype;
	buffPrototypeBox["ViewSizeBuff"] = viewBuffPrototype;
	buffPrototypeBox["EvadeBuff"] = evadeBuffPrototype;
	buffPrototypeBox["AccuracyBuff"] = accuracyBuffPrototype;
	buffPrototypeBox["CriticalProBuff"] = criticalProBuffPrototype;
	buffPrototypeBox["CriticalPointBuff"] = criticalPointBuffPrototype;
	buffPrototypeBox["CriticalPerBuff"] = criticalPerBuffPrototype;
	buffPrototypeBox["BlockProBuff"] = blockProBuffPrototype;
	buffPrototypeBox["BlockPointBuff"] = blockPointBuffPrototype;
	buffPrototypeBox["ComboBuff"] = comboBuffPrototype;
	buffPrototypeBox["WeightBuff"] = weightBuffPrototype;
}

Buff::BuffBase* Buff::BuffFactory::getBuff(std::string b)
{
//	std::string b=ToolFunction::WStr2UTF8(buffName);
	std::vector<std::string> buffMessage;
	split(b, '_', buffMessage);

	if (buffMessage.empty())
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
	return buffPrototypeBox[buffName]->createPrototype();
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
