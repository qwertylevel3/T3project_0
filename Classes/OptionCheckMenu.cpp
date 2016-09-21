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
	choosePrevious();
}

void OptionCheckMenu::handleDown()
{
	HudMenu::handleDown();
	chooseNext();
}

void OptionCheckMenu::handleRight()
{
	HudMenu::handleRight();
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
	HudLayer::getInstance()->addChild(this->getSprite());
	this->setPosition(cocos2d::Point(400, 400));
	this->setWidth(200);

	hide();
}


void OptionCheckMenu::run(Question* question)
{
	curIndex = 0;
	curQuestion = question;
	curQuestion->changeOption(curIndex);
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

void OptionCheckMenu::choosePrevious()
{
	curIndex--;
	curIndex = curIndex < 0 ? 0 : curIndex;
	curQuestion->changeOption(curIndex);
}

void OptionCheckMenu::chooseNext()
{
	curIndex++;
	curIndex = curIndex >= curQuestion->getSize()-1 ? curQuestion->getSize() - 1 : curIndex;
	curQuestion->changeOption(curIndex);
}

void OptionCheckMenu::addOption(const std::string& optionLabel)
{
	HudMenuItem* item = new HudMenuItem(optionLabel);
	this->addItem(item);
}

void OptionCheckMenu::setPosition(cocos2d::Point position)
{
	HudMenu::setPosition(position.x,position.y);
}

void OptionCheckMenu::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		KeyController::getInstance()->switchCtrlToDialog();
		hide();
		DialogueDriver::getInstance()->handleKeyPressed(keyCode);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		choosePrevious();
		this->handleUp();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		chooseNext();
		this->handleDown();
		break;
	}
}

void OptionCheckMenu::initHeight()
{
	int optionCount = curQuestion->getSize();
	int height = optionCount*24+40;
	this->setHeight(height);
}
