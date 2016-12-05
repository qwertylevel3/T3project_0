#pragma once


class Character;


namespace cocos2d
{
	class Sprite;
}

class CharacterBar
{
public:
	CharacterBar();
	~CharacterBar();
	void setCharacter(Character* character);
	void update();
protected:
	Character* characterPtr;
	cocos2d::Sprite* hpBarBk;
	cocos2d::Sprite* mpBarBk;
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* mpBar;
};

