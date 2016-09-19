#include "OptionCheckDialog.h"
#include "HudMenu.h"
#include "HudMenuItem.h"
#include "HudLayer.h"
#include "Question.h"
#include "KeyController.h"
#include "DialogueDriver.h"
#include "HudCursor.h"



OptionCheckDialog::OptionCheckDialog()
{
}


OptionCheckDialog::~OptionCheckDialog()
{
}

void OptionCheckDialog::init()
{
	curQuestion = nullptr;
	dialog = new HudMenu(cocos2d::Rect(0, 0, 200, 20));
	HudLayer::getInstance()->addChild(dialog->getSprite());
	dialog->setPosition(400, 400);

	hide();
}

void OptionCheckDialog::show()
{
	HudCursor::getInstance()->show();
	dialog->show();
}

void OptionCheckDialog::hide()
{
	HudCursor::getInstance()->hide();
	dialog->hide();
}

void OptionCheckDialog::clear()
{
	dialog->clear();
}

void OptionCheckDialog::run(Question* question)
{
	curIndex = 0;
	curQuestion = question;
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

void OptionCheckDialog::choosePrevious()
{
	curIndex--;
	curIndex = curIndex < 0 ? 0 : curIndex;
	curQuestion->changeOption(curIndex);

}

void OptionCheckDialog::chooseNext()
{
	curIndex++;
	curIndex = curIndex >= curQuestion->getSize()-1 ? curQuestion->getSize() - 1 : curIndex;
	curQuestion->changeOption(curIndex);
}

void OptionCheckDialog::addOption(const std::string& optionLabel)
{
	HudMenuItem* item = new HudMenuItem(optionLabel);
	dialog->addItem(item);
}

void OptionCheckDialog::setPosition(cocos2d::Point position)
{
	dialog->setPosition(position.x, position.y);
}

void OptionCheckDialog::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
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

void OptionCheckDialog::initHeight()
{
	int optionCount = curQuestion->getSize();
	int height = optionCount*24+40;
	dialog->setHeight(height);
}
