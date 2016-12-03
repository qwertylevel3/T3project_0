#include "MainMenu.h"
#include "MenuLayer.h"
#include "ui/UIButton.h"
#include "MainLayer.h"
#include "Player.h"
#include "ToolFunction.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::init()
{
	cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();

	layout->setBackGroundImage("menu/mainMenuBK.png");
	layout->setBackGroundImageScale9Enabled(true);
	layout->setSize(cocos2d::Size(150, 450));
	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	layout->setPosition(cocos2d::Vec2(0, 600));

	listView = cocos2d::ui::ListView::create();

	listView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	listView->setBounceEnabled(true);
	listView->setContentSize(cocos2d::Size(130, 450));
	listView->setScrollBarPositionFromCorner(cocos2d::Vec2(7, 7));
	listView->setItemsMargin(10.0f);
	listView->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	listView->setPosition(cocos2d::Vec2(20, 430));
	listView->setOpacity(180);

	MenuLayer::getInstance()->addChild(layout);
	layout->addChild(listView);

	static const cocos2d::Size BUTTON_SIZE(110, 30);

	auto buffButton = cocos2d::ui::Button::create("menu/menuItemBK.png", "menu/menuItemBK.png");
	buffButton->setScale9Enabled(true);
	buffButton->setSize(BUTTON_SIZE);
	buffButton->setContentSize(BUTTON_SIZE);
	buffButton->setTitleFontSize(24);
	buffButton->setTitleText("buff");
	listView->pushBackCustomItem(buffButton);

	auto skillButton = cocos2d::ui::Button::create("menu/menuItemBK.png", "menu/menuItemBK.png");
	skillButton->setScale9Enabled(true);
	skillButton->setSize(BUTTON_SIZE);
	skillButton->setContentSize(BUTTON_SIZE);
	skillButton->setTitleFontSize(24);
	skillButton->setTitleText("skill");
	listView->pushBackCustomItem(skillButton);

	auto inventoryButton = cocos2d::ui::Button::create("menu/menuItemBK.png", "menu/menuItemBK.png");
	inventoryButton->setScale9Enabled(true);
	inventoryButton->setSize(BUTTON_SIZE);
	inventoryButton->setContentSize(BUTTON_SIZE);
	inventoryButton->setTitleFontSize(24);
	inventoryButton->setTitleText(ToolFunction::WStr2UTF8(L"物品"));
	listView->pushBackCustomItem(inventoryButton);

	auto equipmentButton = cocos2d::ui::Button::create("menu/menuItemBK.png", "menu/menuItemBK.png");
	equipmentButton->setScale9Enabled(true);
	equipmentButton->setSize(BUTTON_SIZE);
	equipmentButton->setContentSize(BUTTON_SIZE);
	equipmentButton->setTitleFontSize(24);
	equipmentButton->setTitleText(ToolFunction::WStr2UTF8(L"装备"));
	listView->pushBackCustomItem(equipmentButton);

	auto groundButton = cocos2d::ui::Button::create("menu/menuItemBK.png", "menu/menuItemBK.png");
	groundButton->setScale9Enabled(true);
	groundButton->setSize(BUTTON_SIZE);
	groundButton->setContentSize(BUTTON_SIZE);
	groundButton->setTitleFontSize(24);
	groundButton->setTitleText(ToolFunction::WStr2UTF8(L"地面"));
	listView->pushBackCustomItem(groundButton);
}

void MainMenu::show()
{
}

void MainMenu::hide()
{
}