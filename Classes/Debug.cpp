#include "Debug.h"



Debug::Debug()
{
	debugFlag = false;
}


Debug::~Debug()
{
}

bool Debug::getDebugFlag()
{
	return false;
//	return debugFlag;
}

void Debug::setDebugFlag(bool f)
{
	debugFlag = f;
}
