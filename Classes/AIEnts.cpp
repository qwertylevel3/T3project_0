#include "AIEnts.h"

AIEnts::AIEnts()
{
}

AIEnts::~AIEnts()
{
}

void AIEnts::update()
{
	if (!characterPtr)
	{
		return;
	}
	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		
		if (isInAttackArea(targetCharacter))
		{
			characterPtr->attack();
		}
		else
		{
			changeOrientationTo(targetCharacter);
			characterPtr->idle();
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AIEnts::feedback(Character* character)
{
	characterPtr->speak(L"I..am ... ent..s");
}