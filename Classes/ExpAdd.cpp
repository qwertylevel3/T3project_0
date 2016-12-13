#include "ExpAdd.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::ExpAdd::ExpAdd()
{
}


Skill::ExpAdd::~ExpAdd()
{
}

Skill::ExpAdd* Skill::ExpAdd::createPrototype()
{
	return new Skill::ExpAdd();
}

void Skill::ExpAdd::run()
{
	caster->addExp(value);
}

void Skill::ExpAdd::initExtraMessage(std::vector<std::string> extraMessage)
{
	value[0] = ToolFunction::string2int(extraMessage[0]);
	value[1] = ToolFunction::string2int(extraMessage[1]);
	value[2] = ToolFunction::string2int(extraMessage[2]);
}

std::string Skill::ExpAdd::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n") +
		ToolFunction::WStr2UTF8(L"增加力量经验")+
		ToolFunction::int2string(value[0])+"\n"+
		ToolFunction::WStr2UTF8(L"增加敏捷经验")+
		ToolFunction::int2string(value[1])+"\n"+
		ToolFunction::WStr2UTF8(L"增加智力经验")+
		ToolFunction::int2string(value[2])+"\n";
}
