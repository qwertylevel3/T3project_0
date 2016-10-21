#include "BuffHandler.h"
#include "BuffBase.h"
#include "CharacterAttrHandler.h"
#include "Character.h"

using namespace Buff;

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

void Buff::BuffHandler::onBuffLoad()
{
	characterPrt->getAttrHandler()->reset();
	for each (BuffBase* buff in buffBox)
	{
		if (buff->getType() == BuffBase::OnLoad)
		{
			buff->apply(characterPrt);
		}
	}
}

void Buff::BuffHandler::onBuffUnload()
{
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