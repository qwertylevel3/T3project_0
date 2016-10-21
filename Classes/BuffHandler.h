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
	std::vector<BuffBase*>& getBuffBoxRef();
protected:
	std::vector<BuffBase*> buffBox;
	Character* characterPrt;
};

