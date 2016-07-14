#include "Attack.h"

#include"Dungeon.h"

Attack::Attack(Character* character)
	:Skill(character)
{
}


Attack::~Attack()
{
}

int Attack::run()
{
	Field::Dungeon* dungeon = caster->getDungeon();
	cocos2d::Point curCoord = caster->getMapCoord();
	cocos2d::Point castCoord = curCoord;
	castCoord.x++;

	return 0;
}
