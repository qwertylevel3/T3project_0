#include "HudBuffMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "BuffHandler.h"
#include "BuffBase.h"
#include "HudDescriptionMenu.h"
#include "ToolFunction.h"



HudBuffMenu::HudBuffMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}


HudBuffMenu::~HudBuffMenu()
{
}

void HudBuffMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudBuffMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}

void HudBuffMenu::update()
{
	clear();
	//////////////////////////////////////////////////////////////////////////
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Buff::BuffHandler* buffHandler = characterPrt->getBuffHandler();

	std::vector<Buff::BuffBase* > buffBox = buffHandler->getBuffBoxRef();

	for each (Buff::BuffBase* buff in buffBox)
	{
		HudMenuItem* menuItem = new HudMenuItem(buff->getCname());
		this->addItem(menuItem);
	}

	//////////////////////////////////////////////////////////////////////////
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
}


void HudBuffMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);
	HudDescriptionMenu::getInstance()->setDescription(
		ToolFunction::WStr2UTF8(L"放大镜理发师的看法很快就地方哈开始附加哈萨克防火防盗卡萨放大放大师傅打石榴夫妇")
	);
}

void HudBuffMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
