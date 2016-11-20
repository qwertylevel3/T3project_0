#include "GameController.h"
#include "RandomNumber.h"
#include "BuffFactory.h"
#include "SphereFactory.h"
#include "InventoryFactory.h"
#include "CharacterFactory.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "BattleSystem.h"
#include "KeyController.h"
#include "RoundSystem.h"
#include "MainLayer.h"
#include "MaskLayer.h"



GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::init()
{
	initPlist();
	RandomNumber::getInstance()->setSeed(333);
	Buff::BuffFactory::getInstance()->init();
	Sphere::SphereFactory::getInstance()->init();
	InventoryFactory::getInstance()->init();
	CharacterFactory::getInstance()->init();
	Player::getInstance()->init();
	MonsterFactory::getInstance()->init();
	BattleSystem::getInstance()->init();
	KeyController::getInstance()->init();
	RoundSystem::getInstance()->init();
}

void GameController::startMission(int level)
{
	MaskLayer::getInstance()->clear();
	MainLayer::getInstance()->clear();

	Field::Dungeon::getInstance()->generate(1);
//	Dungeon::getInstance()->writeToFile();

	MainLayer::getInstance()->loadStorey();
	MaskLayer::getInstance()->loadStorey();
	RoundSystem::getInstance()->loadStorey();

	RoundSystem::getInstance()->start();
}

void GameController::initPlist()
{

}
