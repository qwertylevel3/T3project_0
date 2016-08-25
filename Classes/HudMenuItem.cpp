#include "HudMenuItem.h"
#include"ToolFunction.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include "cocos2d.h"



HudMenuItem::HudMenuItem(const std::wstring& name)
{
	setName(name);
	label = cocos2d::Label::createWithTTF(ToolFunction::WStr2UTF8(name), "fonts/arialuni.ttf", 24);
	label->retain();
	marginal.x = 10;
	marginal.y = 10;
}


HudMenuItem::~HudMenuItem()
{
	label->release();
}


void HudMenuItem::show()
{
	label->setVisible(true);
}

void HudMenuItem::hide()
{
	label->setVisible(false);
}

void HudMenuItem::setPosition(cocos2d::Point position)
{
	position.x += getWidth()/2;
	position.y -= getHeight()/2;
	label->setPosition(position);
}

void HudMenuItem::setMenu(HudMenu* menu)
{
	relateMenu = menu;
}

cocos2d::Point HudMenuItem::getPosition()
{
	return label->getPosition();
}

int HudMenuItem::getWidth()
{
	return label->getMaxLineWidth();
}

cocos2d::Label* HudMenuItem::getLabel()
{
	return label;
}

int HudMenuItem::getHeight()
{
	return label->getHeight();
}

std::string HudMenuItem::getUTF8name()
{
	return ToolFunction::WStr2UTF8(getName());
}
