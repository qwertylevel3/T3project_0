#include "AIVergil.h"
#include <algorithm>
#include "Dungeon.h"
#include "ToolFunction.h"
#include "Player.h"
#include "Character.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"

using std::placeholders::_1;
using std::placeholders::_2;

AIVergil::AIVergil()
{
	//默认为紧密跟随
	curState = 0;
}

AIVergil::~AIVergil()
{
}

void AIVergil::update()
{
	switch (curState)
	{
	case 0:
		stayCloseAI();
		break;
	case 1:
		freeAI();
		break;
	default:
		break;
	}
}

void AIVergil::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("vergilTalk", this->characterPtr);
}

void AIVergil::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName == "vergilTalk"
		&& resultNumber == -2)
	{
		curState = 0;
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -3)
	{
		curState = 1;
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -4)
	{
		//求奶
		Character* playerCharacter = Player::getInstance()->getcharacterPtr();
		if (characterPtr->getMP() > 20)
		{
			changeOrientationTo(playerCharacter);
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(L"HPRecoveryCast_生命恢复_20_0_40")
			);
			HudMessageBox::getInstance()->addMessage(L"Vergil向你释放了一个治疗法术");
			return;
		}
		else
		{
			DialogueSystem::getInstance()->runDialogue("vergilNoMagic");
		}
	}
}

void AIVergil::lastWords()
{
	DialogueSystem::getInstance()->runDialogue("vergilDie");
	HudMessageBox::getInstance()->addMessage(L"Vergil消失了");
}

void AIVergil::stayCloseAI()
{
	//状态
	//0为player周围没有enemy，跟随
	//1为player周围有enemy，保护player
	static int stateFlag = 0;

	std::vector<Character* > allEnemy = getEnemyAroundPlayer();
	if (allEnemy.size() == 0)
	{
		//安全
		stateFlag = 0;
	}
	else
	{
		stateFlag = 1;
	}

	Character* playerCharacter = Player::getInstance()->getcharacterPtr();
	cocos2d::Point playerCoord = playerCharacter->getMapCoord();

	if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
	{
		//player血量低且vergil有魔法,优先治疗
		if (playerCharacter->getHP() < 50
			&& characterPtr->getMP() > 20)
		{
			changeOrientationTo(playerCharacter);
			characterPtr->runSkill(
				ToolFunction::WStr2UTF8(L"HPRecoveryCast_生命恢复_20_0_40")
			);
			HudMessageBox::getInstance()->addMessage(L"Vergil向你释放了一个治疗法术");
			return;
		}
	}

	if (stateFlag == 0)
	{
		if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
		{
			//如果已经靠近了,查找四周的可攻击enemy
			Character* targetCharacter = searchTargetBFS(Character::Bad, 1);
			if (targetCharacter)
			{
				changeOrientationTo(targetCharacter);
				characterPtr->attack();
			}
			else
			{
				characterPtr->idle();
			}
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
	else
	{
		auto bound_cmp = bind(&AIVergil::cmpDistance, this, _1, _2);
		sort(allEnemy.begin(), allEnemy.end(), bound_cmp);

		Character* enemy = allEnemy[0];

		if (ToolFunction::isNear4(enemy->getMapCoord(),
			characterPtr->getMapCoord()))
		{
			changeOrientationTo(enemy);
			characterPtr->attack();
			return;
		}
		else
		{
			if (isAccessAble(enemy->getMapCoord()))
			{
				seek(enemy);
			}
			else
			{
				seek(playerCharacter);
			}

			return;
		}
	}
}

void AIVergil::freeAI()
{
	int viewSize = characterPtr->getViewSize();

	Character* enemyTarget = searchTargetBFS(Character::Bad);

	if (enemyTarget)
	{
		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 5)
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
		else
		{
			if (isInAttackArea(enemyTarget))
			{
				characterPtr->attack();
			}
			else
			{
				seek(enemyTarget);
			}
		}
	}
	else
	{
		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

		if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
		{
			characterPtr->idle();
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
}

std::vector<Character* > AIVergil::getEnemyAroundPlayer()
{
	std::vector<Character*> allEnemy;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			cocos2d::Point tempCoord = oriCoord;
			tempCoord.x += i;
			tempCoord.y += j;

			Character* target = storey->getCharacter(tempCoord);

			if (target
				&& target->getCharacterType() == Character::Bad)
			{
				allEnemy.push_back(target);
			}
		}
	}
	return allEnemy;
}

bool AIVergil::cmpDistance(Character* a, Character* b)
{
	return ToolFunction::getManhattanDistance(a->getMapCoord(), characterPtr->getMapCoord())
		< ToolFunction::getManhattanDistance(b->getMapCoord(), characterPtr->getMapCoord());
}