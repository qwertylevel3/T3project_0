#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "HudLayer.h"


HudMessageBox::HudMessageBox()
{
}


HudMessageBox::~HudMessageBox()
{
}

void HudMessageBox::init()
{
	maxMessageNumber = 8;
	bk = cocos2d::Sprite::create("HUD/messageBox.png");
	HudLayer::getInstance()->addChild(bk);
	bk->setPosition(650, 82);
}

void HudMessageBox::update()
{

}

void HudMessageBox::show()
{
	for each (cocos2d::Label* label in messageBox)
	{
		label->setVisible(true);
	}
	bk->setVisible(true);
}

void HudMessageBox::hide()
{
	bk->setVisible(false);

}

void HudMessageBox::addMessage(std::wstring message)
{
	cocos2d::Label* messageLabel = cocos2d::Label::createWithTTF(ToolFunction::WStr2UTF8(message), "fonts/arialuni.ttf", 16);
	messageLabel->setMaxLineWidth(280);
	messageLabel->setWidth(280);
	messageLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);

	if (messageBox.size()==maxMessageNumber)
	{
		cocos2d::Label* lastLabel = messageBox.front();
		messageBox.erase(messageBox.begin());
		lastLabel->removeFromParent();
	}
	
	messageBox.push_back(messageLabel);
//	HudLayer::getInstance()->addChild(messageLabel);
	bk->addChild(messageLabel);

	formatMessageBox();
}

void HudMessageBox::formatMessageBox()
{
	int count = 0;
	cocos2d::Point oriPosition(0,0);
	for each (cocos2d::Label* label in messageBox)
	{
		label->setPosition(oriPosition.x+label->getMaxLineWidth()/2+6
			, oriPosition.y + 155-count *20 );
		count++;
	}
}
