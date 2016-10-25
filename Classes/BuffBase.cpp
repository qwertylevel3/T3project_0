#include "BuffBase.h"


using namespace Buff;

BuffBase::BuffBase()
{
	priority = 99;
	active = true;
}


BuffBase::~BuffBase()
{
}



void Buff::BuffBase::updateDuration()
{
	if (duration>0)
	{
		duration--;
	} 
	else if(duration==0)
	{
		this->setActive(false);
	}
}

void Buff::BuffBase::setActive(bool a)
{
	active = a;
}

bool Buff::BuffBase::isActive()
{
	return active;
}
