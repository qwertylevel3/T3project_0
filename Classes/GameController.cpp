#include "GameController.h"
#include "ToolFunction.h"
#include "DialogueSystem.h"
#include "NoteTextFactory.h"
#include "InventoryListGenerator.h"
#include "GameSaveManager.h"
#include "HudMessageBox.h"
#include "FriendCreatureManager.h"
#include "RandomNumber.h"
#include "2d/CCAnimation.h"
#include "BuffFactory.h"
#include "SphereFactory.h"
#include "SplashLayer.h"
#include "InventoryFactory.h"
#include "SkillFactory.h"
#include "CharacterFactory.h"
#include "Player.h"
#include "GameActorFactory.h"
#include "BattleSystem.h"
#include "KeyController.h"
#include "RoundSystem.h"
#include "MainLayer.h"
#include "MaskLayer.h"
#include "HeroManager.h"
#include "MyCamera.h"
#include "EffectManager.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::init()
{
	GameSaveManager::getInstance()->load();

	int seed=ToolFunction::getCurTime();

	RandomNumber::getInstance()->setSeed(seed);
	NoteTextFactory::getInstance()->init();
	InventoryListGenerator::getInstance()->init();
	Buff::BuffFactory::getInstance()->init();
	Sphere::SphereFactory::getInstance()->init();
	Skill::SkillFactory::getInstance()->init();
	InventoryFactory::getInstance()->init();
	CharacterFactory::getInstance()->init();
	Player::getInstance()->init();
	GameActorFactory::getInstance()->init();
	BattleSystem::getInstance()->init();
	KeyController::getInstance()->init();
	RoundSystem::getInstance()->init();
	HeroManager::getInstance()->init();
	EffectManager::getInstance()->init();
	FriendCreatureManager::getInstance()->init();

	curLevel = 1;

	firstPlay = true;

	GameSaveManager::getInstance()->increasePlayCount();
	GameSaveManager::getInstance()->save();

	KeyController::getInstance()->setBlock(true);
}

void GameController::startMission()
{
	HudMessageBox::getInstance()->clear();

	MaskLayer::getInstance()->clear();

	MainLayer::getInstance()->clear();
	RoundSystem::getInstance()->clear();

	Field::Dungeon::getInstance()->generate(curLevel);
	//	Field::Dungeon::getInstance()->writeToFile();

	Player::getInstance()->initMission();
	HeroManager::getInstance()->initMission();
	FriendCreatureManager::getInstance()->initMission();

	MainLayer::getInstance()->initMission();
	MaskLayer::getInstance()->initMission();
	RoundSystem::getInstance()->initMission();
	RoundSystem::getInstance()->start();

	MyCamera::getInstance()->setCamera(Player::getInstance()->getcharacterPtr()->getPosition());

	if (firstPlay)
	{
		SplashLayer::getInstance()->startGame(1.5);
		firstPlay = false;
	}
	else if (curLevel==1)
	{
		//todo
		//SplashLayer::getInstance()->fadeOutBlackAndFloorNumber(2);
		SplashLayer::getInstance()->reStartGame(1.5);
	}
	else
	{
		SplashLayer::getInstance()->fadeOutBlackAndFloorNumber(2);
	}


}

void GameController::nextMission()
{
	curLevel++;
	SplashLayer::getInstance()->nextMission(1);
}

int GameController::getCurLevel()
{
	return curLevel;
}

void GameController::startGame()
{
	startMission();
}

void GameController::reStartGame()
{
	Field::Dungeon::getInstance()->clear();

	Player::getInstance()->restart();
	HeroManager::getInstance()->restart();
	FriendCreatureManager::getInstance()->restart();



	curLevel = 1;
	GameSaveManager::getInstance()->increasePlayCount();
	GameSaveManager::getInstance()->save();
	startMission();

}

void GameController::endGame()
{

}

void GameController::saveGame()
{

}

void GameController::runStartDialogue()
{
	KeyController::getInstance()->setBlock(false);

	if (GameSaveManager::getInstance()->getPlayCount()==1)
	{
		Character* vergilCharacter = HeroManager::getInstance()->getHero("vergil");

		//第一次进入游戏
		DialogueSystem::getInstance()->runDialogue("vergilFirstTalk",vergilCharacter);
	}
	else if (GameSaveManager::getInstance()->getDieCount()==1)
	{
		//第一次死亡
		GameSaveManager::getInstance()->increaseDieCount();
		GameSaveManager::getInstance()->save();
		DialogueSystem::getInstance()->runDialogue("firstDie");
	}
	else if (GameSaveManager::getInstance()->getFirstClear()==1)
	{
		//第一次通关重来
		DialogueSystem::getInstance()->runDialogue("firstClear");
		GameSaveManager::getInstance()->increaseFirstClear();
		GameSaveManager::getInstance()->save();
	}
	else
	{
		int roll = RandomNumber::getInstance()->randomInt(1, 4);

		switch (roll)
		{
		case 1:
			DialogueSystem::getInstance()->runDialogue("vergilStartTalk1");
			break;
		case 2:
			DialogueSystem::getInstance()->runDialogue("vergilStartTalk2");
			break;
		case 3:
			DialogueSystem::getInstance()->runDialogue("vergilStartTalk3");
			break;
		case 4:
			DialogueSystem::getInstance()->runDialogue("vergilStartTalk4");
			break;
		default:
			DialogueSystem::getInstance()->runDialogue("vergilStartTalk1");
			break;
		}
	}
}
