#include "ToolFunction.h"
#include<sstream>
#include"AStar.h"
#include"Dungeon.h"

using namespace Field;

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

std::string ToolFunction::int2string(int i)
{
	std::stringstream stream;
	stream << i;
	std::string str = stream.str();
	return str;
}

std::wstring ToolFunction::string2wstring(std::string str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

std::string ToolFunction::wstring2string(std::wstring wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
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

bool ToolFunction::isNear4(cocos2d::Point oriCoord, cocos2d::Point targetCoord)
{
	if (oriCoord.x==targetCoord.x &&
		(oriCoord.y==targetCoord.y-1 || oriCoord.y==targetCoord.y+1))
	{
		return true;
	}
	else if (oriCoord.y==targetCoord.y &&
		(oriCoord.x==targetCoord.x-1 || oriCoord.x==targetCoord.x+1))
	{
		return true;
	}
	return false;
}

bool ToolFunction::isNear8(cocos2d::Point oriCoord, cocos2d::Point targetCoord)
{
	for (int i=-1;i<=1;i++)
	{
		cocos2d::Point tempPoint = oriCoord;
		for (int j=-1;j<=1;j++)
		{
			if (i==0 && j==0)
			{
				continue;
			}
			tempPoint.x += i;
			tempPoint.y += j;
			if (targetCoord==tempPoint)
			{
				return true;
			}
		}
	}
	return false;
}

cocos2d::Point ToolFunction::validPlace(Field::Storey* storey,cocos2d::Point ori)
{
	int searchDeep = 1;

	//待优化，bfs
	while (searchDeep < 10)
	{
		for (int i = -searchDeep; i <= searchDeep; i++)
		{
			for (int j = -searchDeep; j <= searchDeep; j++)
			{
				if (i == 0 && j==0)
				{
					continue;
				}
				cocos2d::Point coord = ori;
				coord.x += i;
				coord.y += j;

				//条件
				if (storey->isMoveAble(coord)
					&& storey->getCharacter(coord)==nullptr)
				{
					return coord;
				}

			}
		}

		searchDeep++;
	}
	return ori;
	//CCAssert(searchDeep < 10, "out of search");
}

cocos2d::Point ToolFunction::nextStep(cocos2d::Point src, cocos2d::Point dest)
{
	Storey* storey = Dungeon::getInstance()->getStorey();

	AStar astar(src, dest, storey);
	return astar.nextStep();
}

std::vector<cocos2d::Point> ToolFunction::findPath(cocos2d::Point src, cocos2d::Point dest)
{
	Storey* storey = Dungeon::getInstance()->getStorey();

	AStar astar(src, dest, storey);
	return astar.findPath();
}

std::vector<cocos2d::Point> ToolFunction::findPath(Storey * s, cocos2d::Point src, cocos2d::Point dest)
{
	AStar astar(src, dest, s);
	return astar.findPath();
}