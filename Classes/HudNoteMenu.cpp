#include "HudNoteMenu.h"
#include "HudDescriptionMenu.h"
#include "HudTrigReadNote.h"
#include "HudTrigDrop.h"
#include "HudTrigThrow.h"
#include "HudMenu.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudLayout.h"



HudNoteMenu::HudNoteMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* readMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"ÔÄ¶Á"));
	HudTrigReadNote* readTrig = new HudTrigReadNote();
	readMenuItem->setTrigger(readTrig);
	this->addItem(readMenuItem);


	HudMenuItem* dropMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"¶ªÆú"));
	HudTrigDrop* dropTrig = new HudTrigDrop();
	dropMenuItem->setTrigger(dropTrig);
	this->addItem(dropMenuItem);


//	HudMenuItem* throwMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Í¶ÖÀ"));
//	HudTrigThrow* throwTrig = new HudTrigThrow();
//	throwMenuItem->setTrigger(throwTrig);
//	this->addItem(throwMenuItem);

	hide();
}


HudNoteMenu::~HudNoteMenu()
{
}

void HudNoteMenu::show()
{
	HudMenu::show();

	HudDescriptionMenu::getInstance()->hide();
}

