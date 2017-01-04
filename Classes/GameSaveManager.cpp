#include "GameSaveManager.h"
#include "ToolFunction.h"
#include "HudMessageBox.h"

GameSaveManager::GameSaveManager()
{
}

GameSaveManager::~GameSaveManager()
{
}

void GameSaveManager::init()
{

}

void GameSaveManager::load()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("gamesave.xml");

	tinyxml2::XMLElement* gamesaveElement = doc.RootElement();
	testFlag = this->getChildElementIntAttr(gamesaveElement, "testFlag");
}

void GameSaveManager::save()
{
}

void GameSaveManager::output()
{
	HudMessageBox::getInstance()->addMessage(
		ToolFunction::string2wstring(
			ToolFunction::int2string(testFlag)
		)
	);
}
