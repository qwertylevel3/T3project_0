#include "VertigoBuff.h"




Buff::VertigoBuff::VertigoBuff()
{
}


Buff::VertigoBuff::~VertigoBuff()
{
}

void Buff::VertigoBuff::apply(Character* target)
{

}

Buff::VertigoBuff* Buff::VertigoBuff::createPrototype()
{
	return new VertigoBuff();
}

void Buff::VertigoBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
