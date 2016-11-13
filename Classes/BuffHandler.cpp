#include "BuffHandler.h"
#include "BuffBase.h"
#include "CharacterAttrHandler.h"
#include "Character.h"
#include<algorithm>
#include "BuffFactory.h"

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
	if (buff->getTrigType() == BuffBase::OnLoad ||
		buff->getTrigType() == BuffBase::ATTR)
	{
		buff->apply(characterPrt);
	}
	calculateAttr();
}

void Buff::BuffHandler::addBuff(std::string buffID)
{
	Buff::BuffBase* buff = Buff::BuffFactory::getInstance()->getBuff(buffID);
	addBuff(buff);
}

void Buff::BuffHandler::removeBuff(std::string buffID)
{
	std::vector<BuffBase*>::iterator iter = buffBox.begin();
	while (iter != buffBox.end())
	{
		if ((*iter)->getID() == buffID)
		{
			delete *iter;
			buffBox.erase(iter);
			calculateAttr();
			return;
		}
		iter++;
	}
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
}

void  Buff::BuffHandler::onAttack()
{
}

void  Buff::BuffHandler::onInjured()
{
}

void  Buff::BuffHandler::onRoundStart()
{
	calculateAttr();
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getTrigType() == BuffBase::OnRoundStart)
		{
			buff->apply(characterPrt);
		}
	}
}

void  Buff::BuffHandler::onRoundEnd()
{
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getTrigType() == BuffBase::OnRoundEnd)
		{
			buff->apply(characterPrt);
		}
	}
	clearInactiveBuff();
	calculateAttr();
}

void Buff::BuffHandler::clearInactiveBuff()
{
	std::vector<BuffBase* >::iterator iter = buffBox.begin();
	while (iter != buffBox.end())
	{
		if ((*iter)->isActive() == false)
		{
			if ((*iter)->getTrigType() == BuffBase::OnUnload)
			{
				(*iter)->apply(characterPrt);
			}
			delete (*iter);
			iter = buffBox.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void Buff::BuffHandler::calculateAttr()
{
	characterPrt->getAttrHandler()->reset();
	std::sort(buffBox.begin(), buffBox.end(), compareBuffPriority);
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getTrigType() == BuffBase::ATTR)
		{
			buff->apply(characterPrt);
		}
	}
}

bool Buff::BuffHandler::exist(std::string buffID)
{
	for each (Buff::BuffBase* buff in buffBox)
	{
		if (buff->getID() == buffID)
		{
			return true;
		}
	}
	return false;
}