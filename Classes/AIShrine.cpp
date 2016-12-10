#include "AIShrine.h"



AIShrine::AIShrine()
{
}


AIShrine::~AIShrine()
{
}

void AIShrine::feedback(Character* character)
{
	characterPtr->speak(L"这里是星塔，请提交您的信仰");
}
