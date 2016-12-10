#include "AIStatue.h"
#include "BuffFactory.h"
#include "ToolFunction.h"

AIStatue::AIStatue()
{
	count = 1;
}

AIStatue::~AIStatue()
{
}

void AIStatue::feedback(Character* character)
{
	if (count)
	{
		characterPtr->speak(L"叮咚");

		character->addBuff(
			ToolFunction::WStr2UTF8(
				L"ViewSizeBuff_女神祝福_ATTR_Good_1_20_3"
			)
		);
		character->sufferHPEffect(100);
		character->sufferMPEffect(100);
		count--;
	}
	else
	{
		characterPtr->speak(L"神像感觉身体被掏空");
	}
}