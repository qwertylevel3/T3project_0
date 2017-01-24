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
	int tempSize = attrHandler->getViewSize() + viewSizeOffset;
	tempSize = tempSize < 1 ? 1 : tempSize;
	attrHandler->setViewSizeByBuff(tempSize);
}

Buff::ViewSizeBuff* Buff::ViewSizeBuff::createPrototype()
{
	ViewSizeBuff* newBuff = new ViewSizeBuff();
	return newBuff;
}

std::string Buff::ViewSizeBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"йср╟")
		+ (viewSizeOffset > 0 ? "+" : "")
		+ ToolFunction::int2string(viewSizeOffset);
}

void Buff::ViewSizeBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setViewSizeOffset(ToolFunction::string2int(baseMessage[0]));
}
