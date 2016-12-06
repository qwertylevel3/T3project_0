#include "HPRecoverySelf.h"
#include "ToolFunction.h"
#include "Character.h"
#include "HudMessageBox.h"
#include "EffectManager.h"



Skill::HPRecoverySelf::HPRecoverySelf()
{
}


Skill::HPRecoverySelf::~HPRecoverySelf()
{
}

Skill::HPRecoverySelf* Skill::HPRecoverySelf::createPrototype()
{
	return new Skill::HPRecoverySelf();
}

std::string Skill::HPRecoverySelf::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"回复")
		+ ToolFunction::int2string(value) + ToolFunction::WStr2UTF8(L"生命值");
}

void Skill::HPRecoverySelf::run()
{
	caster->sufferHPEffect(value);
	EffectManager::getInstance()->showEffect(
		"HPRecovery",
		caster->getPosition(),
		1.0);
}

void Skill::HPRecoverySelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
