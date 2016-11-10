#pragma once

#include "cocos2d.h"
#include "Singleton.h"
#include "LightEdge.h"
#include <vector>
#include "base/ccTypes.h"


class Illuminant;

class MaskLayer :public cocos2d::Layer, public Singleton<MaskLayer>
{
public:
	struct Intersect
	{
		float x;
		float y;
		float param;
		float angle;
	};

	struct Segment
	{
		//水平线段，垂直线段
		enum Type
		{
			H,V
		};
		cocos2d::Vec2 a;
		cocos2d::Vec2 b;
		Type type;
	};

	struct MyPolygon : std::vector<Intersect>
	{
		cocos2d::Color4F color;
	};

	MaskLayer();
	~MaskLayer();
	virtual bool init();
	void update();
	void darkOn();
	void darkOff();
	void clear();
	void loadStorey();

protected:
	void addSegments(cocos2d::Vec2* segs, int count);
	void initSegments();
	void getStoreyEdge();
	void getStoreyEdge(int x, int y);
	void mergeEdge();
	bool getIntersection(const Segment& ray, const Segment& segment, Intersect& out);
	MyPolygon getSightPolygon(float sightX, float sightY);
	void drawPolygon(MyPolygon& polygon, cocos2d::Color4F fillStyle);
	bool darkSwitch;

	cocos2d::ClippingNode* clipper;
	cocos2d::DrawNode* stencil;
	cocos2d::Sprite* dark;

	cocos2d::DrawNode* ctx;

	cocos2d::Point playerPosition;

	std::vector<Segment> segments;
	int temp[100][100];
};
