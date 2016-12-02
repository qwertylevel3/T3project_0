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
