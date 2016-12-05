#include "VertigoBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"





Buff::VertigoBuff::VertigoBuff()
{
}


Buff::VertigoBuff::~VertigoBuff()
{
}

void Buff::VertigoBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setActionAbleByBuff(false);
}

Buff::VertigoBuff* Buff::VertigoBuff::createPrototype()
{
	return new VertigoBuff();
}

std::string Buff::VertigoBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"яётн");
}

void Buff::VertigoBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
