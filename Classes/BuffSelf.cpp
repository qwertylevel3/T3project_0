#include "BuffSelf.h"
#include "Character.h"
#include "ToolFunction.h"
#include "BuffFactory.h"
#include "BuffBase.h"



Skill::BuffSelf::BuffSelf()
{
}


Skill::BuffSelf::~BuffSelf()
{
}

Skill::BuffSelf* Skill::BuffSelf::createPrototype()
{
	return new BuffSelf();
}

std::string Skill::BuffSelf::getExtraDescription()
{
	std::string description;
	description+=ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"对自己施加buff:");

	Buff::BuffBase* buff = Buff::BuffFactory::getInstance()->getBuff(buffID);
	description += buff->getDescription();
	delete buff;
	return description;
}

void Skill::BuffSelf::run()
{
	caster->addBuff(buffID);
}

void Skill::BuffSelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	buffID = extraMessage[0];

	for (int i=1;i<extraMessage.size();i++)
	{
		buffID += "_" + extraMessage[i];
	}
}
