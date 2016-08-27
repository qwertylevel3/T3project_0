#pragma once

#include "base/ccTypes.h"

struct LightEdge
{
	LightEdge();
	cocos2d::Point p1;
	cocos2d::Point p2;
	int prev;
	int next;
	int distance;
};

