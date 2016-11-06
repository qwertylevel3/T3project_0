#include "Illuminant.h"
#include "cocos2d.h"
#include "MaskLayer.h"



Illuminant::Illuminant(Character* c)
{
	character = c;

//	lightClipe = cocos2d::Sprite::create("light.png");
//	light = cocos2d::Sprite::create("light.png");
//	clipeNode = cocos2d::ClippingNode::create();

//	lightClipe->setScale(1.5);
//	light->setScale(1.5);
//	clipeNode->setInverted(true);
//	this->addChild(clipeNode);

//	//先涂黑，再把有light的地方挖出来
//	clipeNode->addChild(dark);
//	clipeNode->setStencil(lightClipe);

}


Illuminant::~Illuminant()
{
}

void Illuminant::update()
{

}
