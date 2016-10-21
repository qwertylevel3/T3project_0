#include "BuffHandler.h"



BuffHandler::BuffHandler(Character* c)
{
	characterPrt = c;
}


BuffHandler::~BuffHandler()
{
	for each (BuffBase* buff in buffBox)
	{
		delete buff;
	}
	buffBox.clear();
}

void BuffHandler::addBuff(BuffBase* buff)
{
	buffBox.push_back(buff);
}
