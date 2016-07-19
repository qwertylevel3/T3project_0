#include "CharacterModel.h"

USING_NS_CC;


CharacterModel::CharacterModel()
{
}


CharacterModel::~CharacterModel()
{
}

Character * CharacterModel::makeCharacter()
{
	Character* character = new Character();

	CCSprite* sp = CCSprite::createWithSpriteFrameName("Actor1_01.png");

	character->setSprite(sp);

	character->createMoveUpAnimation();
	character->createMoveDownAnimation();
	character->createMoveLeftAnimation();
	character->createMoveRightAnimation();

	return character;
}
