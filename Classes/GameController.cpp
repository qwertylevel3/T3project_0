#include "GameController.h"
#include "NoteTextFactory.h"
#include "InventoryListGenerator.h"
#include "GameSaveManager.h"
#include "HudMessageBox.h"
#include "SummonCreatureManager.h"
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
	SummonCreatureManager::getInstance()->init();

	curLevel = 1;
}

void GameController::startMission()
{
	MaskLayer::getInstance()->clear();

	MainLayer::getInstance()->clear();
	RoundSystem::getInstance()->clear();

	Field::Dungeon::getInstance()->generate(curLevel);
//		Field::Dungeon::getInstance()->writeToFile();

	Player::getInstance()->initMission();
	HeroManager::getInstance()->initMission();
	SummonCreatureManager::getInstance()->initMission();

	MainLayer::getInstance()->initMission();
	MaskLayer::getInstance()->initMission();
	RoundSystem::getInstance()->initMission();
	RoundSystem::getInstance()->start();

	MyCamera::getInstance()->setCamera(Player::getInstance()->getcharacterPtr()->getPosition());

	if (curLevel == 1)
	{
		SplashLayer::getInstance()->showLogo(2);
	}
	else
	{
		SplashLayer::getInstance()->fadeOutBlack(2);
	}

}

void GameController::nextMission()
{
	curLevel++;
	SplashLayer::getInstance()->fadeInBlack(1);
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
	SummonCreatureManager::getInstance()->restart();


	curLevel = 1;
	startMission();
}

void GameController::endGame()
{

}

void GameController::saveGame()
{

}
