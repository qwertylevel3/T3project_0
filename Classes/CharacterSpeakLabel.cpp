#include "CharacterSpeakLabel.h"
#include "ToolFunction.h"
#include "Character.h"

void CharacterSpeakLabel::hide(CharacterSpeakLabel* speakLabel)
{
	speakLabel->setVisibleFalse();
}

CharacterSpeakLabel::CharacterSpeakLabel()
{
}

CharacterSpeakLabel::~CharacterSpeakLabel()
{
}

void CharacterSpeakLabel::setCharacter(Character* character)
{
	characterPtr = character;

	bk = cocos2d::ui::Scale9Sprite::create("HUD/sentenceLabel.png");
	messageLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 16);

	messageLabel->setMaxLineWidth(200);

	bk->setCapInsets(cocos2d::Rect(10, 10, 100, 20));
	bk->setScale9Enabled(true);

	characterPtr->getSprite()->addChild(bk);
	characterPtr->getSprite()->addChild(messageLabel);

	cocos2d::Rect bound = messageLabel->getBoundingBox();

	messageLabel->setPosition(cocos2d::Vec2(20, 50));
	//	bk->setScaleX(bound.size.width / bk->getContentSize().width+0.1);
	//	bk->setScaleY(bound.size.height / bk->getContentSize().height+0.1);

		//bk->setScale(5, 2);

	bk->setContentSize(cocos2d::Size(bound.size.width + 10, bound.size.height + 10));
	bk->setPosition(messageLabel->getPosition() - cocos2d::Vec2(0, 3));
	bk->setOpacity(180);

	bk->setVisible(false);
	messageLabel->setVisible(false);
}

void CharacterSpeakLabel::speak(std::wstring sentence)
{
	bk->setVisible(true);
	messageLabel->setVisible(true);
	messageLabel->setString(ToolFunction::WStr2UTF8(sentence));

	cocos2d::Rect bound = messageLabel->getBoundingBox();
	bk->setContentSize(cocos2d::Size(bound.size.width + 10, bound.size.height + 10));
	bk->setPosition(messageLabel->getPosition() - cocos2d::Vec2(0, 3));
	bk->setOpacity(180);

	characterPtr->getSprite()->runAction(
		cocos2d::Sequence::create(
			cocos2d::DelayTime::create(4),
			cocos2d::CallFunc::create(CC_CALLBACK_0(CharacterSpeakLabel::hide, this)),
			NULL
		)
	);
}

void CharacterSpeakLabel::setVisibleFalse()
{
	bk->setVisible(false);
	messageLabel->setVisible(false);
}