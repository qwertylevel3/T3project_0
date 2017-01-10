#include "HudTrigReadNote.h"
#include "Note.h"
#include "InventoryFactory.h"
#include "Player.h"
#include "HudNoteSystem.h"
#include "HudInventoryMenu.h"
#include "HudMenuItem.h"
#include "HudMenu.h"



HudTrigReadNote::HudTrigReadNote()
{
}


HudTrigReadNote::~HudTrigReadNote()
{
}

void HudTrigReadNote::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();


	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);

	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);
	std::string noteID = static_cast<Note*>(inventory)->getTextID();
	delete inventory;

	HudNoteSystem::getInstance()->openNote(noteID);

	menuItem->getParentMenu()->closeMenu();
}
