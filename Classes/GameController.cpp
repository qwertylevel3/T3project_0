#include "GameController.h"
#include "RandomNumber.h"
#include "BuffFactory.h"
#include "SphereFactory.h"
#include "InventoryFactory.h"
#include "SkillFactory.h"
#include "CharacterFactory.h"
#include "Player.h"
#include "MonsterFactory.h"
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
	initPlist();
	RandomNumber::getInstance()->setSeed(100);
	Buff::BuffFactory::getInstance()->init();
	Sphere::SphereFactory::getInstance()->init();
	Skill::SkillFactory::getInstance()->init();
	InventoryFactory::getInstance()->init();
	CharacterFactory::getInstance()->init();
	Player::getInstance()->init();
	MonsterFactory::getInstance()->init();
	BattleSystem::getInstance()->init();
	KeyController::getInstance()->init();
	RoundSystem::getInstance()->init();
	HeroManager::getInstance()->init();
	EffectManager::getInstance()->init();
}

void GameController::startMission(int level)
{
	MaskLayer::getInstance()->clear();
	MainLayer::getInstance()->clear();

	Field::Dungeon::getInstance()->generate(1);
//	Dungeon::getInstance()->writeToFile();

	MainLayer::getInstance()->loadStorey();
	Player::getInstance()->initMission();
	HeroManager::getInstance()->initMission();


	MaskLayer::getInstance()->loadStorey();
	RoundSystem::getInstance()->loadStorey();
	RoundSystem::getInstance()->start();

	MyCamera::getInstance()->setCamera(Player::getInstance()->getcharacterPtr()->getPosition());
}

void GameController::initPlist()
{
	
}
