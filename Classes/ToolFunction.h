#pragma once

#include<string>

class ToolFunction
{
public:
	ToolFunction();
	~ToolFunction();
	static int string2int(const std::string& str);
	static std::string WStr2UTF8(const std::wstring& src);
};

