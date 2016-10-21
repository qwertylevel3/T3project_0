#pragma once


#include <vector>

class BuffBase;
class Character;

class BuffHandler
{
public:
	BuffHandler(Character* c);
	~BuffHandler();
	void addBuff(BuffBase* buff);
protected:
	std::vector<BuffBase*> buffBox;
	Character* characterPrt;
};

