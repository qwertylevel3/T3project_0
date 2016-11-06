#include "BuffBase.h"
#include "ToolFunction.h"
#include "base/ccMacros.h"

using namespace Buff;

BuffBase::BuffBase()
{
	cname = ToolFunction::WStr2UTF8(L"Î´ÃüÃûbuff");
	trigType = NeverTrig;
	buffType = Neutarl;
	priority = 9999;
	active = true;
	id = "unknow";
}

BuffBase::~BuffBase()
{
}

void Buff::BuffBase::init(std::vector<std::string> buffMessage)
{
	std::vector<std::string> baseMessage;
	std::vector<std::string > extraMessage;

	int i;
	for (i = 0; i < 5; i++)
	{
		baseMessage.push_back(buffMessage[i]);
	}
	for (; i < buffMessage.size(); i++)
	{
		extraMessage.push_back(buffMessage[i]);
	}
	initBaseMessage(baseMessage);
	this->initExtraMessage(extraMessage);
}

void Buff::BuffBase::updateDuration()
{
	if (duration > 0)
	{
		duration--;
	}
	else if (duration == 0)
	{
		this->setActive(false);
	}
}

void Buff::BuffBase::setActive(bool a)
{
	active = a;
}

bool Buff::BuffBase::isActive()
{
	return active;
}

void Buff::BuffBase::initBaseMessage(std::vector<std::string> baseMessage)
{
	initCname(baseMessage[0]);
	initTrigType(baseMessage[1]);
	initBuffType(baseMessage[2]);
	initPriority(baseMessage[3]);
	initDuration(baseMessage[4]);
}


void Buff::BuffBase::initCname(std::string cnameStr)
{
	cname = cnameStr;
}

void Buff::BuffBase::initTrigType(const std::string& trigTypeStr)
{
	if (trigTypeStr=="ATTR")
	{
		trigType = ATTR;
	}
	else if (trigTypeStr == "OnLoad")
	{
		trigType = OnLoad;
	}
	else if (trigTypeStr == "OnUnload")
	{
		trigType = OnUnload;
	}
	else if (trigTypeStr == "OnRoundStart")
	{
		trigType = OnRoundStart;
	}
}

void Buff::BuffBase::initBuffType(const std::string& buffTypeStr)
{
	if (buffTypeStr == "Good")
	{
		buffType = Good;
	}
	else if (buffTypeStr == "Bad")
	{
		buffType = Bad;
	}
	else if (buffTypeStr == "Neutarl")
	{
		buffType = Neutarl;
	}
	else
	{
		CCAssert(false, "error buff type");
	}
}

void Buff::BuffBase::initPriority(const std::string& priorityStr)
{
	priority = ToolFunction::string2int(priorityStr);
}

void Buff::BuffBase::initDuration(const std::string& durationStr)
{
	duration = ToolFunction::string2int(durationStr);
}
