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

std::string ToolFunction::WStr2UTF8(const std::wstring & src)
{
	std::string dest;

	for (size_t i = 0; i < src.size(); i++) {

		wchar_t w = src[i];

		if (w <= 0x7f)

			dest.push_back((char)w);

		else if (w <= 0x7ff) {

			dest.push_back(0xc0 | ((w >> 6) & 0x1f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else if (w <= 0xffff) {

			dest.push_back(0xe0 | ((w >> 12) & 0x0f));

			dest.push_back(0x80 | ((w >> 6) & 0x3f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff) {

			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation

			dest.push_back(0x80 | ((w >> 12) & 0x3f));

			dest.push_back(0x80 | ((w >> 6) & 0x3f));

			dest.push_back(0x80 | (w & 0x3f));

		}

		else

			dest.push_back('?');

	}
	return dest;
}
