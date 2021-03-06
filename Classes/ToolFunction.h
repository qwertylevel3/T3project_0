#pragma once

#include<string>
#include"base\ccUtils.h"
#include<vector>
#include"Storey.h"

class ToolFunction
{
public:
	ToolFunction();
	~ToolFunction();
	static int string2int(const std::string& str);
	static std::string int2string(int i);
	static std::wstring string2wstring(std::string str);
	static std::string wstring2string(std::wstring wstr);
	static std::string WStr2UTF8(const std::wstring& src);

	
	//是否十字位相邻
	static bool isNear4(cocos2d::Point oriCoord,cocos2d::Point targetCoord);
	//是否相邻
	static bool isNear8(cocos2d::Point oriCoord,cocos2d::Point targetCoord);

	static long getCurTime();


	//计算两点之间的麦哈顿距离
	static int getManhattanDistance(cocos2d::Point coord1, cocos2d::Point coord2);




	//找到原点附近有效的点(无character),如果查找失败返回ori
	static cocos2d::Point findValidPlace(
		Field::Storey* storey,
		cocos2d::Point ori
	);

	static cocos2d::Point findValidPlaceWithoutTrap(
		Field::Storey* storey,
		cocos2d::Point ori
	);

	//A*寻路，返回下一步要走的位置，严格可到达
	static cocos2d::Point nextStep(
		cocos2d::Point src,
		cocos2d::Point dest
	);
	//A*寻路，返回下一步要走的位置，非严格可到达(中间忽略阻碍的队友)
	static cocos2d::Point nextStep_v2(
		cocos2d::Point src,
		cocos2d::Point dest
	);
	//A*寻路，返回下一步要走的位置，非严格可到达(中间忽略阻碍的character)
	static cocos2d::Point nextStep_v3(
		cocos2d::Point src,
		cocos2d::Point dest
	);



	static std::vector<cocos2d::Point> findPath(
		cocos2d::Point src,
		cocos2d::Point dest
	);
	static std::vector<cocos2d::Point> findPath(
		Field::Storey* s,
		cocos2d::Point src,
		cocos2d::Point dest
	);
};

