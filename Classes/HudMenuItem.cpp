#include "HudMenuItem.h"
#include"ToolFunction.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include "cocos2d.h"
#include "HudMenu.h"
#include "HudTrigger.h"


HudMenuItem::HudMenuItem(const std::string& name)
{
	label = cocos2d::Label::createWithTTF(name, "fonts/arialuni.ttf", 24);
	label->setAlignment(cocos2d::TextHAlignment::CENTER);
	label->enableShadow();
	label->retain();
	marginal.x = 10;
	marginal.y = 10;
	trigger = nullptr;
}


HudMenuItem::~HudMenuItem()
{
	label->release();
}


void HudMenuItem::active()
{
	if (trigger)
	{
		trigger->run();
	}
}

void HudMenuItem::setTrigger(HudTrigger* t)
{
	trigger = t;
	t->setMenuItem(this);
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

cocos2d::Point HudMenuItem::getPosition()
{
	return label->getPosition();
}

int HudMenuItem::getWidth()
{
	return label->getMaxLineWidth();
}

void HudMenuItem::setWidth(int w)
{
	label->setWidth(w);
	label->setMaxLineWidth(w);
}

void HudMenuItem::setHeight(int h)
{
	label->setHeight(h);
}

void HudMenuItem::setAliginment(cocos2d::TextHAlignment alignment)
{
	label->setHorizontalAlignment(alignment);
}

cocos2d::Label* HudMenuItem::getLabel()
{
	return label;
}

int HudMenuItem::getHeight()
{
	return label->getHeight();
}

