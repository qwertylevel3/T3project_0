#include "HemophagiaSphere.h"
#include "Character.h"



Sphere::HemophagiaSphere::HemophagiaSphere()
{
	healPer = 0;
}


Sphere::HemophagiaSphere::~HemophagiaSphere()
{
}

void Sphere::HemophagiaSphere::run(Character* a, Character* b, int damage)
{
	double healValue = double(damage)*(double(healPer) / 100.0);
	healValue = healValue < 1 ? 1 : healValue;
	a->sufferHPEffect(int(healValue));
}
