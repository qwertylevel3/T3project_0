#include "HudNoteSystem.h"
#include "NoteTextFactory.h"
#include "KeyController.h"
#include "ToolFunction.h"
#include "HudLayer.h"
#include "HudLayout.h"

HudNoteSystem::HudNoteSystem()
{
}

HudNoteSystem::~HudNoteSystem()
{
}

void HudNoteSystem::init()
{
	layout = cocos2d::ui::Layout::create();
	layout->setBackGroundImage("HUD/menu.png");
	layout->setBackGroundImageScale9Enabled(true);
	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

	layout->setSize(cocos2d::Size(300,400));
	layout->setOpacity(180);
	layout->setPosition(cocos2d::Vec2(200, 500));

	HudLayer::getInstance()->addChild(layout);

	text = cocos2d::ui::Text::create("", "fonts/arialuni.ttf", 20);
	text->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	text->setPosition(cocos2d::Vec2(10, -30));
	text->setOpacity(255);
	text->ignoreContentAdaptWithSize(false);
	text->setContentSize(cocos2d::Size(270, 400));
	//	description->ignoreContentAdaptWithSize(false);
	//	description->setTextAreaSize(cocos2d::Size(150, 400));
	layout->addChild(text);
	hide();
}

void HudNoteSystem::openNote(std::string noteID)
{
	NoteText noteText = NoteTextFactory::getInstance()->getNoteText(noteID);

	setText(noteText.getPage(0));


	this->show();
	KeyController::getInstance()->switchCtrlToNote();
}

void HudNoteSystem::nextPage()
{

}

void HudNoteSystem::hide()
{
	layout->setVisible(false);
}

void HudNoteSystem::show()
{
	layout->setVisible(true);
}

void HudNoteSystem::setText(std::string str)
{
	text->setText(str);
}

void HudNoteSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (keyCode==cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		this->hide();
		KeyController::getInstance()->switchCtrlToPlayer();
	}
}
