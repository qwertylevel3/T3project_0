#include "GameController.h"
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

	RandomNumber::getInstance()->setSeed(100);
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
		SplashLayer::getInstance()->showLogo(2);
		firstPlay = false;
	}
	else if (curLevel==1)
	{
		//todo
		SplashLayer::getInstance()->fadeOutBlackAndFloorNumber(2);
		runStartDialogue();
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
	if (GameSaveManager::getInstance()->getPlayCount()==0)
	{
		//第一次进入游戏
		DialogueSystem::getInstance()->runDialogue("vergilFirstTalk");
		GameSaveManager::getInstance()->increasePlayCount();
		GameSaveManager::getInstance()->save();
	}
	else if (GameSaveManager::getInstance()->getDieCount()==1)
	{
		//第一次死亡
		//todo
//		DialogueSystem::getInstance()->runDialogue("vergilFirstTalk");
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
