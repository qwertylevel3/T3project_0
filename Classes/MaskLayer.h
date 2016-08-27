#pragma once

#include "cocos2d.h"
#include "Singleton.h"
#include "LightEdge.h"
#include <vector>
#include "base/ccTypes.h"

class MaskLayer:public cocos2d::Layer,public Singleton<MaskLayer>
{
public:
	MaskLayer();
	~MaskLayer();
	virtual bool init();
	void update();
protected:
	std::vector<LightEdge> edges;

	//************************************
	// Method:    getTilePosition
	// FullName:  MaskLayer::getTilePosition
	// Access:    protected 
	// Returns:   cocos2d::Point
	// Qualifier: 由tile坐标获得在屏幕上的position
	// Parameter: cocos2d::Point coord
	//************************************
	cocos2d::Point getTilePosition(cocos2d::Point coord);
};

