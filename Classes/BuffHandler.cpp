#include "BuffHandler.h"
#include "BuffBase.h"
#include "CharacterAttrHandler.h"
#include "Character.h"
#include<algorithm>

using namespace Buff;

bool compareBuffPriority(const BuffBase* s1, const BuffBase* s2)
{
	return s1->getPriority() < s2->getPriority(); //从小到大排序
}

Buff::BuffHandler::BuffHandler(Character* c)
{
	characterPrt = c;
}

Buff::BuffHandler::~BuffHandler()
{
	for each (BuffBase* buff in buffBox)
	{
		delete buff;
	}
	buffBox.clear();
}

void Buff::BuffHandler::addBuff(BuffBase* buff)
{
	buffBox.push_back(buff);
	onBuffLoad();
}

std::vector<Buff::BuffBase*>& Buff::BuffHandler::getBuffBoxRef()
{
	return buffBox;
}

void Buff::BuffHandler::update()
{
	for each (BuffBase* buff in buffBox)
	{
		buff->updateDuration();
	}
	bool flag = false;
	std::vector<BuffBase* >::iterator iter = buffBox.begin();
	while (iter != buffBox.end())
	{
		if ((*iter)->isActive() == false)
		{
			delete (*iter);
			iter=buffBox.erase(iter);
			flag = true;
		}
		else
		{
			iter++;
		}
	}
	if (flag)
	{
		onBuffUnload();
	}
}

void Buff::BuffHandler::onBuffLoad()
{
	characterPrt->getAttrHandler()->reset();
	std::sort(buffBox.begin(), buffBox.end(),compareBuffPriority);
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getTrigType() == BuffBase::OnLoad)
		{
			buff->apply(characterPrt);
		}
	}
}

void Buff::BuffHandler::onBuffUnload()
{
	characterPrt->getAttrHandler()->reset();
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getTrigType() == BuffBase::OnUnload)
		{
			buff->apply(characterPrt);
		}
	}
}

void  Buff::BuffHandler::onAttack()
{
}

void  Buff::BuffHandler::onInjured()
{
}

void  Buff::BuffHandler::onRoundStart()
{
}

void  Buff::BuffHandler::onRoundOver()
{
}