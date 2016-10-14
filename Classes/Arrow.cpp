#include "Arrow.h"



Arrow::Arrow()
{
}


Arrow::~Arrow()
{
}

Arrow* Arrow::clone()
{
	Arrow* arrow = new Arrow();
	Inventory::copyData(arrow);
	arrow->setDamage(damage);
	return arrow;
}
