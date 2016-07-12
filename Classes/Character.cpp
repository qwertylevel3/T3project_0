#include "Character.h"

USING_NS_CC;

Character * Character::create(const std::string & filename)
{
	Character *character = new Character();
	if (character && character->initWithFile(filename))
	{
		character->autorelease();
		return character;
	}
	CC_SAFE_DELETE(character);
	return NULL;
}

Character::Character()
{
}


Character::~Character()
{
}
