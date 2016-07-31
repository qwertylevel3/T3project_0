#pragma once


#include<string>
#include"cocos2d.h"

class HudSender
{
public:
	HudSender();
	virtual ~HudSender();

	virtual void updateSender()=0;
	virtual std::string getMessage()=0;
protected:
	CC_SYNTHESIZE(cocos2d::Label*, senderLable, SenderLable);
};

