#include "RoundCounter.h"



RoundCounter::RoundCounter()
{
	roundCount = 0;
	senderLable=cocos2d::Label::createWithTTF("0", "fonts/arial.ttf", 24);
}


RoundCounter::~RoundCounter()
{
}

void RoundCounter::nextRound()
{
	roundCount++;
}

void RoundCounter::updateSender()
{
	senderLable->setString(getMessage());
}

std::string RoundCounter::getMessage()
{
	std::stringstream ss;
	std::string str;
	ss << RoundCounter::getInstance()->getRoundCount();
	ss >> str;
	return str;
}
