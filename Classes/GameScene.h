#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Character.h"
#include"Dungeon.h"

class GameScene : public cocos2d::Layer
{
	enum ControlMode
	{
		MoveMode,
		StandMode,
		AttackMode
	};
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);

 	void addCharacter(Character* character);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void update(float dt);
private:
	Field::Dungeon* dungeon;
};


#endif // __HELLOWORLD_SCENE_H__
