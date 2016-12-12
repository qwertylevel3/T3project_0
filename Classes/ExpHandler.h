#pragma once

class Character;

class ExpHandler
{
public:
	enum expType
	{
		Str=0,
		Agi=1,
		Int=2
	};

	//升级经验值需求
	static const int expRequire[27];

	static const int atkExpAdd[3];
	static const int evadeExpAdd[3];
	static const int criticalExpAdd[3];
	static const int blockExpAdd[3];
	static const int comboExpAdd[3];
	static const int sphereExpAdd[3];
	static const int skillExpAdd[3];
public:
	ExpHandler(Character* character);
	~ExpHandler();
	void addExp(const int e[3]);

	int getCurStrLevel();
	int getCurAgiLevel();
	int getCurIntLevel();

	int getCurStrExp();
	int getCurAgiExp();
	int getCurIntExp();

protected:
	void levelStrUp();
	void levelAgiUp();
	void levelIntUp();
	bool isStrLevelUp();
	bool isAgiLevelUp();
	bool isIntLevelUp();

	Character* characterPtr;

	//0:str	1:agi 2:int
	int exp[3];
	int level[3];
};

