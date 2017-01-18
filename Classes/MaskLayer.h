#pragma once

#include "Singleton.h"
#include <vector>
#include "base/ccTypes.h"
#include "2d/CCLayer.h"
#include "2d/CCRenderTexture.h"


class Character;
class Illuminant;
class IlluminantFixed;
class IlluminantForCharacter;

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
	void initMission();
	void addLightForCharacter(Character* character);
	void addLightFixed(int size,cocos2d::Point coord,int dt);
protected:
	void addLight(Illuminant* light);
	std::vector<Illuminant* > lightBox;
	cocos2d::RenderTexture* mask;
};
