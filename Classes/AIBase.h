#pragma once

class Character;

class AIBase
{
public:
	AIBase();
	virtual ~AIBase();
	virtual void update();
	void setCharacter(Character* character);
	Character* searchTargetBFS();
protected:
	Character* characterPtr;
};

