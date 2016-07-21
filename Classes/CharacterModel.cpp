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

	CCSprite* sp = CCSprite::createWithSpriteFrameName(firstFrameName);

	character->setSprite(sp);

	//character->createMoveUpAnimation();
	//character->createMoveDownAnimation();
	//character->createMoveLeftAnimation();
	//character->createMoveRightAnimation();

	character->setMoveUpAnimation(moveUpAnimation);
	character->setMoveDownAnimation(moveDownAnimation);
	character->setMoveLeftAnimation(moveLeftAnimation);
	character->setMoveRightAnimation(moveRightAnimation);

	return character;
}

cocos2d::Animation* CharacterModel::createAnimation(const std::vector<std::string>& frameList)
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	for (int i = 0; i < frameList.size(); i++)
	{
		std::string str = frameList[i];
		SpriteFrame *fname = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		sfme.pushBack(fname);
	}
	return CCAnimation::createWithSpriteFrames(sfme, 0.1f);
	//animation->retain();
}

void CharacterModel::createMoveUpAnimation(const std::vector<std::string>& frameList)
{
	moveUpAnimation=createAnimation(frameList);
	moveUpAnimation->retain();
}

void CharacterModel::createMoveDownAnimation(const std::vector<std::string>& frameList)
{
	moveDownAnimation=createAnimation(frameList);
	moveDownAnimation->retain();
}

void CharacterModel::createMoveLeftAnimation(const std::vector<std::string>& frameList)
{
	moveLeftAnimation=createAnimation(frameList);
	moveLeftAnimation->retain();

}

void CharacterModel::createMoveRightAnimation(const std::vector<std::string>& frameList)
{
	moveRightAnimation=createAnimation(frameList);
	moveRightAnimation->retain();

}
