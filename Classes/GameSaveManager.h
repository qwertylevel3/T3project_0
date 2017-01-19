#pragma once

#include "Singleton.h"
#include "XMLConfigure.h"

class GameSaveManager :public XMLConfigure, public Singleton<GameSaveManager>
{
public:
	GameSaveManager();
	~GameSaveManager();
	void init();

	void load();
	void save();

	int getPlayCount();
	int getDieCount();
	int getVergilDieCount();
	int getPersephoneDieCount();
	int getClearGameCount();

	void increasePlayCount();
	void increaseDieCount();
	void increaseVergilDieCount();
	void increasePersephoneDieCount();
	void increaseClearGameCount();
protected:
	void saveValue(
		tinyxml2::XMLDocument * pDoc,
		tinyxml2::XMLElement* parent,
		std::string elementName,
		int value);

	int playCount;
	int dieCount;
	int vergilDieCount;
	int persephoneDieCount;
	int clearGameCount;
};
