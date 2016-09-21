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

void OptionCheckMenu::init()
{
	curQuestion = nullptr;
	dialog = new HudMenu(cocos2d::Rect(0, 0, 200, 20));
	HudLayer::getInstance()->addChild(dialog->getSprite());
	dialog->setPosition(400, 400);

	hide();
}

void OptionCheckMenu::show()
{
	HudCursor::getInstance()->show();
	dialog->show();
}

void OptionCheckMenu::hide()
{
	HudCursor::getInstance()->hide();
	dialog->hide();
}

void OptionCheckMenu::clear()
{
	dialog->clear();
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
	HudCursor::getInstance()->setCurMenu(dialog);

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
	dialog->addItem(item);
}

void OptionCheckMenu::setPosition(cocos2d::Point position)
{
	dialog->setPosition(position.x, position.y);
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
		dialog->handleUp();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		chooseNext();
		dialog->handleDown();
		break;
	}
}

void OptionCheckMenu::initHeight()
{
	int optionCount = curQuestion->getSize();
	int height = optionCount*24+40;
	dialog->setHeight(height);
}
