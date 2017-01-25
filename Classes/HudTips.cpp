#include "HudTips.h"
#include "HudMenuSystem.h"
#include "ToolFunction.h"
#include "HudLayer.h"



HudTips::HudTips()
{
}


HudTips::~HudTips()
{
}

void HudTips::init()
{
	tip1 = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 16);
	tip2 = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 16);

	tip1->setString(ToolFunction::WStr2UTF8(L"[Enter打开菜单]"));
	tip2->setString(ToolFunction::WStr2UTF8(L"[Esc关闭菜单]"));

	tip1->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	tip2->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);

	tip1->setPosition(525, 150);
	tip2->setPosition(525, 150);

	tip2->setVisible(false);

	HudLayer::getInstance()->addChild(tip1);
	HudLayer::getInstance()->addChild(tip2);
}

void HudTips::show()
{
	update();
}

void HudTips::hide()
{
	tip1->setVisible(false);
	tip2->setVisible(false);
}

void HudTips::update()
{
	if (HudMenuSystem::getInstance()->isOpen())
	{
		tip1->setVisible(false);
		tip2->setVisible(true);
	}
	else
	{
		tip1->setVisible(true);
		tip2->setVisible(false);
	}

}
