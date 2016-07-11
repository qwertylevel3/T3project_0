#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::TMXTiledMap *tileMap;
	cocos2d::Sprite* player;
};

#endif // __HELLOWORLD_SCENE_H__
