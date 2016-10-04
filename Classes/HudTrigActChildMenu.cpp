#include "HudTrigActChildMenu.h"
#include "HudMenuItem.h"
#include "HudCursor.h"
#include "HudMenu.h"



HudTrigActChildMenu::HudTrigActChildMenu()
{
	relateMenu = nullptr;
}


HudTrigActChildMenu::HudTrigActChildMenu(HudMenu* relateMenu)
{
	setRelateMenu(relateMenu);
}

HudTrigActChildMenu::~HudTrigActChildMenu()
{
	delete relateMenu;
}

void HudTrigActChildMenu::run()
{
	
	if (relateMenu)
	{
		relateMenu->update();
		relateMenu->show();
		HudCursor::getInstance()->setCurMenu(relateMenu);
	}
}
