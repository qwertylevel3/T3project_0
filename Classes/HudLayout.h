#pragma once

#include "Singleton.h"
#include "base/ccTypes.h"
#include "base/ccMacros.h"
#include "XMLConfigure.h"

class HudLayout:public XMLConfigure,public Singleton<HudLayout>
{
public:
	HudLayout();
	~HudLayout();
	void init();
protected:
	CC_SYNTHESIZE(cocos2d::Size, mainMenuSize, mainMenuSize);
	CC_SYNTHESIZE(cocos2d::Point, mainMenuPosition, MainMenuPosition);

	CC_SYNTHESIZE(cocos2d::Size, mediumMenuSize, MediumMenuSize);
	CC_SYNTHESIZE(cocos2d::Point, mediumMenuPosition, MediumMenuPosition);

	CC_SYNTHESIZE(cocos2d::Size, leafMenuSize, LeafMenuSize);
	CC_SYNTHESIZE(cocos2d::Point, leafMenuPosition, LeafMenuPosition);

	CC_SYNTHESIZE(cocos2d::Size, barSize, BarSize);
	CC_SYNTHESIZE(cocos2d::Point, hpBarPosition, HpBarPosition);
	CC_SYNTHESIZE(cocos2d::Point, mpBarPosition, MpBarPosition);

	CC_SYNTHESIZE(cocos2d::Size, descriptionSize, DescriptionSize);
	CC_SYNTHESIZE(cocos2d::Point, descriptionPosition, DescriptionPosition);

	CC_SYNTHESIZE(cocos2d::Size, playerStateSize, PlayerStateSize);
	CC_SYNTHESIZE(cocos2d::Point, playerStatePosition, PlayerStatePosition);
};

