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
	static std::string WStr2UTF8(const std::wstring& src);
	//A*寻路，返回下一步要走的位置
	static cocos2d::Point nextStep(
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

