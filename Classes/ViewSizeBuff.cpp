#include "ViewSizeBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::ViewSizeBuff::ViewSizeBuff()
{
}


Buff::ViewSizeBuff::~ViewSizeBuff()
{
}

void Buff::ViewSizeBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setViewSizeByBuff(attrHandler->getViewSize() + viewSizeOffset);
}

Buff::ViewSizeBuff* Buff::ViewSizeBuff::createPrototype()
{
	ViewSizeBuff* newBuff = new ViewSizeBuff();
	return newBuff;
}

void Buff::ViewSizeBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setViewSizeOffset(ToolFunction::string2int(baseMessage[0]));
}
