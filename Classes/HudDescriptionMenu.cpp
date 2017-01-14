#include "HudDescriptionMenu.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include "HudLayout.h"
#include "HudLayer.h"
#include "ToolFunction.h"


HudDescriptionMenu::HudDescriptionMenu()
{

}

HudDescriptionMenu::~HudDescriptionMenu()
{

}

void HudDescriptionMenu::init()
{
//	sprite = cocos2d::Sprite::create("HUD/menu.png");
	layout = cocos2d::ui::Layout::create();
	layout->setBackGroundImage("HUD/menu.png");
	layout->setBackGroundImageScale9Enabled(true);
	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

	layout->setSize(
		HudLayout::getInstance()->getDescriptionSize()
	);
	layout->setPosition(HudLayout::getInstance()->getDescriptionPosition());
	layout->setOpacity(180);
	
	HudLayer::getInstance()->addChild(layout);

	title = cocos2d::ui::Text::create(ToolFunction::WStr2UTF8(L"หตร๗:"), "fonts/arialuni.ttf", 20);
	title->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	title->setOpacity(255);
	layout->addChild(title);
	title->setPosition(cocos2d::Vec2(10, 398));
	description=cocos2d::ui::Text::create("","fonts/arialuni.ttf", 16);
	description->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	description->setPosition(cocos2d::Vec2(10, -30));
	description->setOpacity(255);
	description->ignoreContentAdaptWithSize(false);
	description->setContentSize(cocos2d::Size(240,400));
//	description->ignoreContentAdaptWithSize(false);
//	description->setTextAreaSize(cocos2d::Size(150, 400));
	layout->addChild(description);
	hide();
}

void HudDescriptionMenu::show()
{
	layout->setVisible(true);
}

void HudDescriptionMenu::hide()
{
	layout->setVisible(false);
}

void HudDescriptionMenu::setDescription(const std::string& des)
{
	description->setText(des);
}

void HudDescriptionMenu::setDescription(const std::wstring& des)
{
	description->setText(ToolFunction::WStr2UTF8(des));
}
