#pragma once

class Character;

class ExpHandler
{
public:
	//升级经验值需求
	static const int expRequire[27];

	static const int skillExpAdd;
public:
	ExpHandler(Character* character);
	~ExpHandler();
	bool isLevelUp();
	void addExp(const int e);
	void useAttrPoint();
	int getCurLevel();
	int getCurExp();
	int getCurAttrPoint();


protected:
	void levelUp();


	Character* characterPtr;
	 
	int exp;
	int level;
	//属性点
	int attrPoint;
};

