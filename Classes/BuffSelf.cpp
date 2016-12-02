#include "BuffSelf.h"
#include "Character.h"



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
