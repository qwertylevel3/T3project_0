#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Character.h"
#include"Dungeon.h"
#include "Singleton.h"

class MainLayer : public cocos2d::Layer,public Singleton<MainLayer>
{
public:
	//************************************
	// Method:    getWorldPosition
	// FullName:  GameScene::getWorldPosition
	// Access:    public static 
	// Returns:   cocos2d::Point
	// Qualifier: 由本地坐标返回屏幕坐标
	// Parameter: cocos2d::Point position
	//************************************
	cocos2d::Point getWorldPosition(cocos2d::Point position);

    virtual bool init();
	void initMission();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(MainLayer);
	void update(float dt);

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	void focusPlayer();
	void unfocusPlayer();
	void clear();
private:
	bool viewFocus;
};


#endif // __HELLOWORLD_SCENE_H__
