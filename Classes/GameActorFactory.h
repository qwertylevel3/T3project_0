#pragma once

#include"Singleton.h"
#include<string>
#include<map>
#include "XMLConfigure.h"
#include "tinyxml2/tinyxml2.h"

class Character;
class GameActorModel;

class GameActorFactory:public XMLConfigure,public Singleton<GameActorFactory>
{
public:
	GameActorFactory();
	~GameActorFactory();
	void init();
	Character* getActor(const std::string& name);
protected:
	void initModel(tinyxml2::XMLElement* actorElement);

	std::map<std::string, GameActorModel*> actorMap;
};

