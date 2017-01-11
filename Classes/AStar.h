#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include"base\ccUtils.h"
#include"Storey.h"
using namespace std;


class AStar
{
public:
	struct AStarPoint
	{
		int x;
		int y;
		int f;//f=g+h
		int g;//从起点到自己的代价
		int h;//从自己到终点的代价
		struct AStarPoint *parent;//指向父亲的指针
		struct AStarPoint *self;//记录自己的地址

						   //重载等号操作符
		bool operator==(const AStarPoint &point)
		{
			return this->x == point.x &&
				this->y == point.y;
		}

		//重载<操作符
		bool operator<(const AStarPoint &point)
		{
			return this->f < point.f;
		}

		friend ostream& operator<<(ostream &os, const AStarPoint &point)
		{
			os << "Point(x=" << point.x << ",y=" << point.y << ",f=" << point.f
				<< ",g=" << point.g << ",h=" << point.g
				<< ",parent=" << point.parent << ",self="
				<< point.self << ")" << endl;
			return os;
		}
	};

	struct Coordinate
	{
		int x;
		int y;
	};

	AStar();
	~AStar();
	AStar(cocos2d::Point start, cocos2d::Point end,
		Field::Storey* s);
	std::vector<cocos2d::Point> findPath();
	std::vector<cocos2d::Point> findPath_v2();
	std::vector<cocos2d::Point> findPath_v3();
	cocos2d::Point nextStep();
	cocos2d::Point nextStep_v2();
	cocos2d::Point nextStep_v3();
private:
	list<AStarPoint> opened_list;//开启列表
	list<AStarPoint> closed_list;//关闭列表

	Field::Storey* storey;
	cocos2d::Point startPoint;
	cocos2d::Point endPoint;

	vector<AStarPoint*> malloc_space;//存储new出来的空间

	ofstream _log;

	//计算两个点之间的距离,采用的是曼哈顿距离
	int _get_distance(int start_x, int start_y, int end_x, int end_y);

	bool _is_shorter(const AStarPoint &point1, const AStarPoint &point2);//比较两个Point的大小，用在排序中

	void _print(const list<AStarPoint> &point);
};
