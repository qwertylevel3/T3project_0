#include "MenuSystem.h"
#include "MainMenu.h"



MenuSystem::MenuSystem()
{
}


MenuSystem::~MenuSystem()
{
}

void MenuSystem::init()
{
	MainMenu::getInstance()->init();
}

void MenuSystem::show()
{

}

void MenuSystem::hide()
{

}
