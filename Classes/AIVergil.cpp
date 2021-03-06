#include "AIVergil.h"
#include "GameController.h"
#include "RandomNumber.h"
#include "BuffHandler.h"
#include "Supply.h"
#include "Armor.h"
#include "Accessory.h"
#include "NoteTextFactory.h"
#include "HudNoteSystem.h"
#include "InventoryInHand.h"
#include "InventoryFactory.h"
#include "InventoryHandler.h"
#include "HudNoteSystem.h"
#include "HudExchangeInventorySystem.h"
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

	magicLowCount = 0;
	smallTalkCount = 4;
}

AIVergil::~AIVergil()
{
}

void AIVergil::update()
{
	//更新闲聊计数器
	updateSmallTalkCount();

	//更新魔法不足计数器
	updateMagicLowCount();

	//尝试治疗身边的player
	if (healPlayer())
	{
		return;
	}

	//整理物品
	if (tidyInventory())
	{
		return;
	}

	//尝试恢复自己
	if (recovery())
	{
		return;
	}

	//尝试增加自己属性
	if (tryAddAttr())
	{
		return;
	}

	//行动
	switch (curState)
	{
	case 0:
		followAI();
		break;
	case 1:
		waitAI();
		break;
	case 2:
		leadAI();
		break;
	default:
		characterPtr->idle();
		break;
	}
}

void AIVergil::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("vergilTalk", this->characterPtr);
}

void AIVergil::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName == "vergilFirstTalk"
		&& resultNumber == -1)
	{
		HudMessageBox::getInstance()->addMessage(L"你获得了《生存手册》");
	}
	else if (dialogueName == "vergilTalk"
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
		if (characterPtr->getMP() > 40)
		{
			changeOrientationTo(playerCharacter);
			healCast();
			return;
		}
		else
		{
			DialogueSystem::getInstance()->runDialogue("vergilNoMagic");
		}
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -5)
	{
		//给东西
		HudExchangeInventorySystem::getInstance()->exchangeInventory(Player::getInstance()->getcharacterPtr(),
			characterPtr);
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -6)
	{
		//要东西
		HudExchangeInventorySystem::getInstance()->exchangeInventory(characterPtr,
			Player::getInstance()->getcharacterPtr());
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -7)
	{
		//显示当前状态
		showCurState();
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -8)
	{
		//闲聊
		smallTalk();
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -10)
	{
		//尝试给buff
		tryBuffToPlayer();
	}
	else if (dialogueName == "vergilTalk"
		&& resultNumber == -11)
	{
		//引路
		curState = 2;
		//玩家等待Vergil动作
		Player::getInstance()->getcharacterPtr()->idle();
	}
	else if (dialogueName=="vergilTalk"
		&& resultNumber==-12)
	{
		introduceSelf();
	}
	else if (dialogueName == "vergilCastBuff"
		&& resultNumber == -1)
	{
		//给buff
		castBuffToPlayer();
	}
	
}

void AIVergil::lastWords()
{
	DialogueSystem::getInstance()->runDialogue("vergilDie");
	HudMessageBox::getInstance()->addMessage(L"Vergil消失了");
}

void AIVergil::levelUp()
{
	AIBase::levelUp();

	HudMessageBox::getInstance()->addMessage(L"Vergil升级了");
}

bool AIVergil::recovery()
{
	//尝试使用物品回复
	if (characterPtr->getHP() < characterPtr->getMaxHP() / 2)
	{
		if (tryUseHPSupply())
		{
			return true;
		}
	}
	if (characterPtr->getHP() < characterPtr->getMaxHP() / 2
		&& characterPtr->getMP() > 40)
	{
		healSelf();
		return true;
	}
	if (characterPtr->getMP() < characterPtr->getMaxMP() / 2)
	{
		if (tryUseMPSupply())
		{
			return true;
		}
	}

	return false;
}

void AIVergil::followAI()
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
		protectPlayer();
	}
}

void AIVergil::waitAI()
{
	Character* playerCharacter = Player::getInstance()->getcharacterPtr();
	cocos2d::Point playerCoord = playerCharacter->getMapCoord();

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

void AIVergil::leadAI()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	cocos2d::Point downCoord = storey->getDownCoord();
	cocos2d::Point startCoord = characterPtr->getMapCoord();

	if (isSafe())
	{
		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 3)
		{
			//距离player太远
			seek(Player::getInstance()->getcharacterPtr());
			HudMessageBox::getInstance()->addMessage(L"Vergil示意你跟上");
		}
		else
		{
			cocos2d::Point nextStep = ToolFunction::nextStep(
				startCoord,
				downCoord
			);
			if (nextStep == startCoord)
			{
				nextStep = ToolFunction::nextStep_v2(
					startCoord,
					downCoord
				);
				if (nextStep == startCoord)
				{
					nextStep = ToolFunction::nextStep_v3(
						startCoord,
						downCoord
					);
					if (nextStep == startCoord)
					{
						characterPtr->speak(L"呃。。。");
						characterPtr->idle();
						HudMessageBox::getInstance()->addMessage(L"Vergil似乎迷路了");
						return;
					}
				}
			}
			if (storey->getCharacter(nextStep))
			{
				HudMessageBox::getInstance()->addMessage(L"Vergil似乎被挡住了");
			}
			goNextStep(startCoord, downCoord, nextStep);
		}
	}
	else
	{
		std::vector<Character* > targets1 = getEnemyInView();
		std::vector<Character* > targets2 = getEnemyInPlayerView();

		std::vector<Character* > targets;
		for (int i = 0; i < targets1.size(); i++)
		{
			targets.push_back(targets1[i]);
		}
		for (int i = 0; i < targets2.size(); i++)
		{
			targets.push_back(targets2[i]);
		}

		if (targets.empty())
		{
			characterPtr->idle();
			HudMessageBox::getInstance()->addMessage(L"Vergil正在犹豫");
			return;
		}

		auto bound_cmp = bind(&AIVergil::cmpDistance, this, _1, _2);
		sort(targets.begin(), targets.end(), bound_cmp);

		Character* targetCharacter = targets[0];

		changeOrientationTo(targetCharacter);
		if (isInAttackArea(targetCharacter))
		{
			characterPtr->attack();
			return;
		}
		else
		{
			seek(targetCharacter);
			return;
		}
	}
}

void AIVergil::protectPlayer()
{
	std::vector<Character* > allEnemy = getEnemyAroundPlayer();
	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	if (allEnemy.empty())
	{
		seek(playerCharacter);
		return;
	}

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

bool AIVergil::healPlayer()
{
	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	if (ToolFunction::isNear4(characterPtr->getMapCoord(),
		playerCharacter->getMapCoord()))
	{
		//player血量低且vergil有魔法,优先治疗
		if (playerCharacter->getHP() < playerCharacter->getMaxHP() / 2
			&& characterPtr->getMP() > 40)
		{
			changeOrientationTo(playerCharacter);
			healCast();
			return true;
		}
	}
	return false;
}

std::vector<Character* > AIVergil::getEnemyAround()
{
	return getTargetAround(characterPtr->getMapCoord(), Character::Bad, 1);
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

std::vector<Character* > AIVergil::getEnemyInView()
{
	return getTargetAround(
		characterPtr->getMapCoord(),
		Character::Bad,
		characterPtr->getViewSize()
	);
}

std::vector<Character* > AIVergil::getEnemyInPlayerView()
{
	Character* playerCharacter = Player::getInstance()->getcharacterPtr();

	return getTargetAround(
		playerCharacter->getMapCoord(),
		Character::Bad,
		playerCharacter->getViewSize()
	);
}

bool AIVergil::isSafe()
{
	if (getEnemyInPlayerView().empty()
		&& getEnemyInView().empty())
	{
		return true;
	}
	return false;
}

bool AIVergil::cmpDistance(Character* a, Character* b)
{
	return ToolFunction::getManhattanDistance(a->getMapCoord(), characterPtr->getMapCoord())
		< ToolFunction::getManhattanDistance(b->getMapCoord(), characterPtr->getMapCoord());
}
bool AIVergil::tidyInventory()
{
	if (chooseBetterLefthand())
	{
		return true;
	}
	//	if (chooseBetterRighthand())
	//	{
	//		return true;
	//	}
	if (chooseBetterArmor())
	{
		return true;
	}
	if (chooseBetterAccessory())
	{
		return true;
	}
	return false;
}

bool AIVergil::tryUseHPSupply()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();
	std::map<std::string, int>::iterator iter = allInventory.begin();

	while (iter != allInventory.end())
	{
		if (InventoryFactory::getInstance()->queryInventoryType(iter->first) == Inventory::Supply)
		{
			Supply* supply = static_cast<Supply*>(InventoryFactory::getInstance()->getInventory(iter->first));
			if (supply->getSupplyType() == Supply::HPSupply)
			{
				characterPtr->removeInventory(iter->first);
				supply->use(characterPtr);
				HudMessageBox::getInstance()->addMessage(L"Vergil尝试着回复了自己的HP");
				flag = true;
			}
			delete supply;

			if (flag)
			{
				break;
			}
		}
		iter++;
	}
	return flag;
}

bool AIVergil::tryUseMPSupply()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();
	std::map<std::string, int>::iterator iter = allInventory.begin();

	while (iter != allInventory.end())
	{
		if (InventoryFactory::getInstance()->queryInventoryType(iter->first) == Inventory::Supply)
		{
			Supply* supply = static_cast<Supply*>(InventoryFactory::getInstance()->getInventory(iter->first));
			if (supply->getSupplyType() == Supply::MPSupply)
			{
				characterPtr->removeInventory(iter->first);
				supply->use(characterPtr);
				HudMessageBox::getInstance()->addMessage(L"Vergil尝试着回复了自己的MP");
				flag = true;
			}
			delete supply;
			if (flag)
			{
				break;
			}
		}
		iter++;
	}
	return flag;
}

bool AIVergil::tryAddAttr()
{
	if (isSafe())
	{
		bool flag = false;
		InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
		std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();
		std::map<std::string, int>::iterator iter = allInventory.begin();

		while (iter != allInventory.end())
		{
			if (InventoryFactory::getInstance()->queryInventoryType(iter->first) == Inventory::Supply)
			{
				Supply* supply = static_cast<Supply*>(InventoryFactory::getInstance()->getInventory(iter->first));
				if (supply->getSupplyType() == Supply::AttrSupply)
				{
					characterPtr->removeInventory(iter->first);
					supply->use(characterPtr);
					HudMessageBox::getInstance()->addMessage(L"Vergil尝试着阅读一些属性书");
					flag = true;
				}
				delete supply;

				if (flag)
				{
					break;
				}
			}
			iter++;
		}
		return flag;
	}
	return false;
}

bool AIVergil::chooseBetterLefthand()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curLeftHandLevel = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getLevel() : 0;
	std::string curLeftHandName = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getName() : "NULL";

	int maxLevel = curLeftHandLevel;
	std::string maxInventory = curLeftHandName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::OneHandWeapon && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curLeftHandName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipLeftHand(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil换了一件更好的武器");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterRighthand()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curRightHandLevel = characterPtr->getRightHand() ? characterPtr->getRightHand()->getLevel() : 0;
	std::string curRightHandName = characterPtr->getRightHand() ? characterPtr->getRightHand()->getName() : "NULL";

	int maxLevel = curRightHandLevel;
	std::string maxInventory = curRightHandName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::OneHandWeapon && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curRightHandName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipRightHand(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil更换了一件右手武器");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterArmor()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curArmorLevel = characterPtr->getArmor() ? characterPtr->getArmor()->getLevel() : 0;
	std::string curArmorName = characterPtr->getArmor() ? characterPtr->getArmor()->getName() : "NULL";

	int maxLevel = curArmorLevel;
	std::string maxInventory = curArmorName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::Armor && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curArmorName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipArmor(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil更换了一件护甲");
		return true;
	}
	return false;
}

bool AIVergil::chooseBetterAccessory()
{
	bool flag = false;
	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	std::map<std::string, int> allInventory = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = allInventory.begin();

	int curAccessoryLevel = characterPtr->getAccessory() ? characterPtr->getAccessory()->getLevel() : 0;
	std::string curAccessoryName = characterPtr->getAccessory() ? characterPtr->getAccessory()->getName() : "NULL";

	int maxLevel = curAccessoryLevel;
	std::string maxInventory = curAccessoryName;

	while (iter != allInventory.end())
	{
		Inventory::Type invType = InventoryFactory::getInstance()->queryInventoryType(iter->first);
		int invLevel = InventoryFactory::getInstance()->queryInventoryLevel(iter->first);

		if (invType == Inventory::Accessory && invLevel > maxLevel)
		{
			maxLevel = invLevel;
			maxInventory = iter->first;
		}

		iter++;
	}
	if (maxInventory != curAccessoryName)
	{
		characterPtr->removeInventory(maxInventory);
		Inventory* inventory = InventoryFactory::getInstance()->getInventory(maxInventory);
		characterPtr->equipAccessory(inventory);
		HudMessageBox::getInstance()->addMessage(L"Vergil更换了一件附件");
		return true;
	}
	return false;
}

void AIVergil::showCurState()
{
	NoteText note;

	std::string  characterLevel = ToolFunction::int2string(characterPtr->getLevel());
	std::string characterHP = ToolFunction::int2string(characterPtr->getHP()) + "/" +
		ToolFunction::int2string(characterPtr->getMaxHP());
	std::string characterMP = ToolFunction::int2string(characterPtr->getMP()) + "/" +
		ToolFunction::int2string(characterPtr->getMaxMP());

	std::string characterInt = ToolFunction::int2string(characterPtr->getIntellect());
	std::string characterStr = ToolFunction::int2string(characterPtr->getStrength());
	std::string characterAgi = ToolFunction::int2string(characterPtr->getAgility());

	std::string leftHandName = characterPtr->getLeftHand() ? characterPtr->getLeftHand()->getCname() : "NULL";
	std::string rightHandName = characterPtr->getRightHand() ? characterPtr->getRightHand()->getCname() : "NULL";;
	std::string armorName = characterPtr->getArmor() ? characterPtr->getArmor()->getCname() : "NULL";;
	std::string accessoryName = characterPtr->getAccessory() ? characterPtr->getAccessory()->getCname() : "NULL";

	note.addPage(
		"Vergil\n" +
		ToolFunction::WStr2UTF8(L"当前等级:") + characterLevel + "\n" +
		ToolFunction::WStr2UTF8(L"HP:") + characterHP + "\n" +
		ToolFunction::WStr2UTF8(L"MP:") + characterMP + "\n" +
		ToolFunction::WStr2UTF8(L"力量:") + characterStr + "\n" +
		ToolFunction::WStr2UTF8(L"敏捷:") + characterAgi + "\n" +
		ToolFunction::WStr2UTF8(L"智力:") + characterInt + "\n" +
		ToolFunction::WStr2UTF8(L"左手:") + leftHandName + "\n" +
		ToolFunction::WStr2UTF8(L"右手:") + rightHandName + "\n" +
		ToolFunction::WStr2UTF8(L"护甲:") + armorName + "\n" +
		ToolFunction::WStr2UTF8(L"附件:") + accessoryName + "\n"
	);

	HudNoteSystem::getInstance()->openNote(note);
}

void AIVergil::smallTalk()
{
	if (!isSafe())
	{
		DialogueSystem::getInstance()->runDialogue("vergilNotSafe");
		return;
	}

	if (smallTalkCount < 4)
	{
		DialogueSystem::getInstance()->runDialogue("vergilNoSmallTalk");
		return;
	}
	else
	{
		int roll = RandomNumber::getInstance()->randomInt(1, 13);

		std::string tipsName = "vergilTips" + ToolFunction::int2string(roll);

		DialogueSystem::getInstance()->runDialogue(tipsName);

		smallTalkCount = 0;
	}
}

void AIVergil::introduceSelf()
{
	DialogueSystem::getInstance()->runDialogue("vergilIntroduce");
}

void AIVergil::tryBuffToPlayer()
{
	Buff::BuffHandler* targetBuffHandler = Player::getInstance()->getcharacterPtr()->getBuffHandler();

	if (targetBuffHandler->exist(
		ToolFunction::WStr2UTF8(L"ChantBuff_Vergil的吟唱祝福_OnRoundStart_Good_10_20_100"))
		)
	{
		DialogueSystem::getInstance()->runDialogue("vergilNoBuff");
	}
	else if (characterPtr->getMP() < 20)
	{
		DialogueSystem::getInstance()->runDialogue("vergilNoMagic");
	}
	else
	{
		DialogueSystem::getInstance()->runDialogue("vergilCastBuff", characterPtr);
	}
}

void AIVergil::castBuffToPlayer()
{
	changeOrientationTo(Player::getInstance()->getcharacterPtr());
	characterPtr->runSkill(
		ToolFunction::WStr2UTF8(L"BuffCast_吟唱祝福_20_0_ChantBuff_Vergil的吟唱祝福_OnRoundStart_Good_10_20_100")
	);
	HudMessageBox::getInstance()->addMessage(L"Vergil释放了吟唱祝福");
}

void AIVergil::healCast()
{
	characterPtr->runSkill(
		ToolFunction::WStr2UTF8(L"HPCastAccordInt_生命恢复_40_0_100")
	);
	characterPtr->addExp(50);
	HudMessageBox::getInstance()->addMessage(L"Vergil向你释放了一个治疗法术");
}

void AIVergil::healSelf()
{
	characterPtr->runSkill(
		ToolFunction::WStr2UTF8(L"HPSelfAccordInt_生命恢复_40_0_100")
	);
	characterPtr->addExp(50);
	HudMessageBox::getInstance()->addMessage(L"Vergil向自己释放了一个治疗法术");
}

void AIVergil::updateSmallTalkCount()
{
	smallTalkCount++;

	if (smallTalkCount >= 4)
	{
		smallTalkCount = 4;
	}
}

void AIVergil::updateMagicLowCount()
{
	magicLowCount++;

	if (magicLowCount>=20)
	{
		magicLowCount = 20;

		if (characterPtr->getMP()<40)
		{
			characterPtr->speak(L"快没魔法了");
			magicLowCount = 0;
		}
	}
}
