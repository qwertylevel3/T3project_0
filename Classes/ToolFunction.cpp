#include "ToolFunction.h"
#include<sstream>



ToolFunction::ToolFunction()
{
}


ToolFunction::~ToolFunction()
{
}

int ToolFunction::string2int(const std::string & str)
{
	std::stringstream stream(str);
	int temp;
	stream >> temp;
	return temp;
}
