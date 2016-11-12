#pragma once

#include "Singleton.h"
#include "LightEdge.h"
#include <vector>
#include "base/ccTypes.h"
#include "2d/CCLayer.h"
#include "2d/CCRenderTexture.h"


class Illuminant;

class MaskLayer :public cocos2d::Layer, public Singleton<MaskLayer>
{
public:
	MaskLayer();
	~MaskLayer();
	virtual bool init();
	void update(float dt);
	void darkOn();
	void darkOff();
	void clear();
	void loadStorey();
protected:
	void addLight(Illuminant* light);
	std::vector<Illuminant* > lightBox;
	cocos2d::RenderTexture* mask;
};
