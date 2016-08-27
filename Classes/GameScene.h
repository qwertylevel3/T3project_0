#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Character.h"
#include"Dungeon.h"
#include "Singleton.h"

class GameScene : public cocos2d::Layer,public Singleton<GameScene>
{
public:

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);

 	void addCharacter(Character* character);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void update(float dt);

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	void switchControlToPlayer();
	void switchControlToHud();
	void loadStorey();
private:
	bool isControlPlayer;
};


#endif // __HELLOWORLD_SCENE_H__
