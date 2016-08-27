#pragma once

#include "cocos2d.h"
#include "Singleton.h"
#include "LightEdge.h"
#include <vector>
#include "base/ccTypes.h"
class cocos2d::Sprite;

class MaskLayer:public cocos2d::Layer,public Singleton<MaskLayer>
{
public:
	MaskLayer();
	~MaskLayer();
	virtual bool init();
	void update();
protected:
	cocos2d::Sprite* dark;
	cocos2d::Sprite* lightClipe;
	cocos2d::Sprite* light;

	int scanWidth;
	int scanHeight;
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

	//************************************
	// Method:    calculateEdge
	// FullName:  MaskLayer::calculateEdge
	// Access:    protected 
	// Returns:   void
	// Qualifier: 由光源位置计算见光边缘,结果放入edges中
	// Parameter: cocos2d::Point position(光源位置)
	//************************************
	void calculateEdge(cocos2d::Point position);
};

