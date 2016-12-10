#include "AStar.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include"FieldEnum.h"
using namespace std;
AStar::AStar()
{
}

AStar::~AStar()
{
	_log.close();
	//避免内存泄露，释放分配的内存
	for (unsigned int i = 0; i < malloc_space.size(); ++i)
		delete(malloc_space[i]);
}

AStar::AStar(cocos2d::Point start, cocos2d::Point end, Field::Storey * s)
{
	storey = s;
	startPoint = start;
	endPoint = end;
}

std::vector<cocos2d::Point> AStar::findPath()
{
	//g表示从起点到自己的代价，h表示从自己到终点的代价
	//把起始点放入到开启列表中
	AStarPoint *start_point = new AStarPoint();
	malloc_space.push_back(start_point);
	start_point->x = startPoint.x;
	start_point->y = startPoint.y;
	start_point->g = 0;
	start_point->h = _get_distance(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	start_point->f = start_point->h + start_point->g;
	start_point->parent = NULL;//起始点的父节点为空
	start_point->self = start_point;//自己的地址

	opened_list.push_back(*start_point);//把起始点放进开启列表中

	while (0 != opened_list.size())
	{
		opened_list.sort();//把开启列表中的数据排序

		list<AStarPoint>::iterator first = opened_list.begin();
		AStarPoint first_point = *first;//获取列表中的第一个数据

		closed_list.push_back(first_point);//把这个数据放入关闭列表中
		opened_list.erase(first);//删除这个元素

		if (first_point.x == endPoint.x && first_point.y == endPoint.y)//如果当前的数据是终点，则结束
			break;
		//把当前点的领域内的点全部放入开启列表中
		int top_left_x = first_point.x == 0 ? 0 : first_point.x - 1;
		int top_left_y = first_point.y == 0 ? 0 : first_point.y - 1;
		int bottom_right_x = first_point.x >= storey->getWidth() - 1 ? first_point.x : first_point.x + 1;
		int bottom_right_y = first_point.y >= storey->getHeight() - 1 ? first_point.y : first_point.y + 1;

		for (int i = top_left_x; i <= bottom_right_x; ++i)
		{
			for (int j = top_left_y; j <= bottom_right_y; ++j)
			{
				//斜方向丢弃
				if (i != first_point.x && j != first_point.y)
				{
					continue;
				}
				if (i != first_point.x || j != first_point.y)
				{
					//非障碍物
					if (storey->isMoveAble(cocos2d::Point(i, j))
						|| cocos2d::Point(i,j)==endPoint)
//					if(storey->isMoveAble(storey->getTile(i,j)))
					{
						AStarPoint point;
						point.x = i;
						point.y = j;

						list<AStarPoint>::iterator iter = find(opened_list.begin(), opened_list.end(), point);
						if (iter != opened_list.end())
						{
							//已经在开启列表中
							AStarPoint pp = *iter;
							int d1 = _get_distance(first_point.x, first_point.y,
								startPoint.x, startPoint.y);
							int d2 = _get_distance(first_point.x, first_point.y, i, j);
							if (d1 + d2 < pp.g)
							{
								pp.parent = first_point.self;
								pp.g = d1 + d2;
							}
							continue;
						}

						iter = find(closed_list.begin(), closed_list.end(), point);
						if (iter != closed_list.end())
						{
							//已经在关闭列表中
							AStarPoint pp = *iter;
							int d1 = _get_distance(first_point.x, first_point.y,
								startPoint.x, startPoint.y);
							int d2 = _get_distance(first_point.x, first_point.y, i, j);
							if (d1 + d2 < pp.g)
							{
								pp.parent = first_point.self;
								pp.g = d1 + d2;
							}
							continue;
						}

						//既不在开启列表中也不在关闭列表中
						AStarPoint *p = new AStarPoint();
						p->x = i;
						p->y = j;
						p->h = _get_distance(i, j, endPoint.x, endPoint.y);
						p->g = _get_distance(startPoint.x, startPoint.y, i, j);
						p->f = p->g + p->h;
						p->parent = first_point.self;
						p->self = p;
						//放入到 开启列表 中去
						opened_list.push_back(*p);

						malloc_space.push_back(p);
					}
				}
			}
		}
	}

	std::vector<cocos2d::Point> result;
	std::vector<cocos2d::Point> temp;
	list<AStarPoint>::const_iterator iter = --closed_list.end();
	AStarPoint p = *iter;
	while (p.parent != NULL)
	{
		cocos2d::Point position;
		position.x = p.x;
		position.y = p.y;
		temp.push_back(position);
		p = *(p.parent);
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result.push_back(temp[i]);
	}
	return result;
}

cocos2d::Point AStar::nextStep()
{
	std::vector<cocos2d::Point> path = findPath();
	return path[0];
}

/*
* 计算两个点之前的距离，采用的是曼哈顿距离
* distance = |start.x-end.x| + |start.y-end.y|
*/
int AStar::_get_distance(int start_x, int start_y, int end_x, int end_y)
{
	return abs(end_x - start_x) + abs(end_y - start_y);
}

bool AStar::_is_shorter(const AStarPoint &point1, const AStarPoint &point2)
{
	return point1.f < point2.f;
}

void AStar::_print(const list<AStarPoint> &point)
{
	list<AStarPoint>::const_iterator i = point.begin();
	while (i != point.end())
	{
		_log << *i;
		++i;
	}
	_log << endl;
}