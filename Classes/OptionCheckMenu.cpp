#include "OptionCheckMenu.h"
#include "HudMenu.h"
#include "HudMenuItem.h"
#include "HudLayer.h"
#include "Question.h"
#include "KeyController.h"
#include "DialogueDriver.h"
#include "HudCursor.h"



OptionCheckMenu::OptionCheckMenu()
{
}


OptionCheckMenu::~OptionCheckMenu()
{
}

void OptionCheckMenu::handleUp()
{
	HudMenu::handleUp();
	curQuestion->changeOption(itemIndex);
}

void OptionCheckMenu::handleDown()
{
	HudMenu::handleDown();
	curQuestion->changeOption(itemIndex);
}

void OptionCheckMenu::handleRight()
{
	HudMenu::handleRight();
	KeyController::getInstance()->switchCtrlToDialog();
	hide();
	DialogueDriver::getInstance()->handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_ENTER);
}

void OptionCheckMenu::handleEnter()
{
	HudMenu::handleEnter();
	KeyController::getInstance()->switchCtrlToDialog();
	hide();
	DialogueDriver::getInstance()->handleKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_ENTER);
}

void OptionCheckMenu::show()
{
	HudMenu::show();
	HudCursor::getInstance()->show();
}

void OptionCheckMenu::hide()
{
	HudMenu::hide();
	HudCursor::getInstance()->hide();
}

void OptionCheckMenu::init()
{
	curQuestion = nullptr;
	this->setPosition(300, 400);
	this->setWidth(200);

	hide();
}


void OptionCheckMenu::run(Question* question)
{
	itemIndex = 0;

	curQuestion = question;
	curQuestion->changeOption(itemIndex);
	clear();
	initHeight();
	for each (std::string option in question->getAllOption())
	{
		addOption(option);
	}

	KeyController::getInstance()->switchCtrlToOption();
	HudCursor::getInstance()->setCurMenu(this);

	show();
}

void OptionCheckMenu::addOption(const std::string& optionLabel)
{
	HudMenuItem* item = new HudMenuItem(optionLabel);
	this->addItem(item);
}

void OptionCheckMenu::initHeight()
{
	int optionCount = curQuestion->getSize();
	int height = optionCount*30+10;

	height = height > 200 ? 200 : height;
	
	this->setHeight(height);
}
