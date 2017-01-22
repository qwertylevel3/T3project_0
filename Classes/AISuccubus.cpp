#include "AISuccubus.h"
#include "Dungeon.h"
#include "ToolFunction.h"
#include "Player.h"
#include "DialogueSystem.h"
#include "Player.h"
#include "HudMessageBox.h"

using std::placeholders::_1;
using std::placeholders::_2;

AISuccubus::AISuccubus()
{
	isFirst = true;
}

AISuccubus::~AISuccubus()
{
}

void AISuccubus::update()
{
	if (isFirst)
	{
		DialogueSystem::getInstance()->runDialogue("succubusSummon");

		isFirst = false;
	}

	if (characterPtr->getHP()<characterPtr->getMaxHP()/2)
	{
		healSelf();
	}

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

	if (stateFlag == 0)
	{
		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();
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
		auto bound_cmp = bind(&AISuccubus::cmpDistance, this, _1, _2);
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
				std::vector<Character*> enemyAround = getEnemyAround();
				if (!enemyAround.empty())
				{
					changeOrientationTo(enemyAround[0]);
					characterPtr->attack();
				}
				else
				{
					seek(playerCharacter);
				}
			}
			return;
		}
	}
}

void AISuccubus::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("succubusTalk", this->characterPtr);
}

void AISuccubus::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	healSelf();
}

void AISuccubus::healSelf()
{
		Character* playerCharacter = Player::getInstance()->getcharacterPtr();
		playerCharacter->sufferHPEffect(-30);
		playerCharacter->sufferMPEffect(-30);

		characterPtr->sufferHPEffect(100);
		characterPtr->sufferMPEffect(100);

		HudMessageBox::getInstance()->addMessage(L"succubus使用了灵魂榨取");
		HudMessageBox::getInstance()->addMessage(L"你感觉身体被掏空");
}

std::vector<Character* > AISuccubus::getEnemyAround()
{
	std::vector<Character*> allEnemy;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = characterPtr->getMapCoord();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 && j != 0)
			{
				continue;
			}

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

std::vector<Character* > AISuccubus::getEnemyAroundPlayer()
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

bool AISuccubus::cmpDistance(Character* a, Character* b)
{
	return ToolFunction::getManhattanDistance(a->getMapCoord(), characterPtr->getMapCoord())
		< ToolFunction::getManhattanDistance(b->getMapCoord(), characterPtr->getMapCoord());
}