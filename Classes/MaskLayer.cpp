#include "MaskLayer.h"
#include "Dungeon.h"
#include "Player.h"
#include "cocos2d.h"
#include "Dungeon.h"
#include "Triangulate.h"
#include "Marco.h"

USING_NS_CC;

bool compare_angle(const MaskLayer::Intersect& t1, const MaskLayer::Intersect& t2)
{
	return t1.angle < t2.angle;
}

//////////////////////////////////////////////////////////////////////////
MaskLayer::MaskLayer()
{
}

MaskLayer::~MaskLayer()
{
	clear();
}

bool MaskLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::Point position = Player::getInstance()->getcharacterPtr()->getPosition();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Vec2(position.x - visibleSize.width / 2,
		position.y - visibleSize.height / 2);

	//	initSegments();

	dark = Sprite::create("dark.png");

	clipper = ClippingNode::create();
	clipper->setInverted(true);
	this->addChild(clipper);

	stencil = DrawNode::create();
	clipper->setStencil(stencil);

	ctx = DrawNode::create();
	this->addChild(ctx);

	clipper->addChild(dark);

	this->scheduleUpdate();

	return true;
}

void MaskLayer::update()
{
	static bool flag = false;
	//////////////////////////////////////////////////////////////////////////

	cocos2d::Point position = Player::getInstance()->getcharacterPtr()->getPosition();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Vec2(position.x - visibleSize.width / 2,
		position.y - visibleSize.height / 2);

	if (playerPosition == position)
	{
		return;
	}
	playerPosition = position;

	stencil->clear();
	ctx->clear();

	Color4F white(1, 1, 1, 1);

	drawPolygon(getSightPolygon(position.x, position.y), white);

	//////////////////////////////////////////////////////////////////////////
	// Draw dots
	ctx->drawDot(position, 2, white);

	for (int i = 0; i < segments.size(); i++)
	{
		Segment& seg = segments[i];
		ctx->drawSegment(seg.a, seg.b, 1, white);
	}

	int a;
}

void MaskLayer::darkOn()
{
	darkSwitch = true;
	this->setVisible(true);
}

void MaskLayer::darkOff()
{
	darkSwitch = false;
	this->setVisible(false);
	dark->setVisible(false);
	clipper->setVisible(false);
}

void MaskLayer::clear()
{
}

void MaskLayer::loadStorey()
{
	clear();

	initSegments();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	Size size = dark->getContentSize();
	float radio = storey->getWidth() * 32 / size.width;
	//	dark->setScale(radio);

	darkOn();
}

void MaskLayer::addSegments(Vec2* segs, int count)
{
	for (int i = 0; i < count; i++)
	{
		Segment s;
		s.a = segs[i];

		if (i == count - 1)
			s.b = segs[0];
		else
			s.b = segs[i + 1];

		segments.push_back(s);
	}
}

void MaskLayer::initSegments()
{
	//	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	//	cocos2d::Size storeySize = cocos2d::Size(storey->getWidth() * 32,
	//		storey->getHeight() * 32);

	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Vec2 origin = cocos2d::Point(0, 0);

	//	float l = origin.x;
	//	float b = origin.y;
	//	float r = origin.x + storeySize.width;
	//	float t = origin.y + storeySize.height;

	//	// border
	//	Vec2 segs[4] = { Vec2(l,b), Vec2(r,b), Vec2(r,t), Vec2(l,t) };
	//	addSegments(segs, 4);

	//	for (int i = 0; i < storeySize.width; i++)
	//	{
	//		for (int j = 0; j < storeySize.height; j++)
	//		{
	//			if (storey->isWall(cocos2d::Point(j, i)))
	//			{
	//				Vec2 wallPosition = storey->getTilePosition(cocos2d::Point(j, i));
	//				float l = wallPosition.x - 16;
	//				float b = wallPosition.y - 16;
	//				float r = wallPosition.x + 16;
	//				float t = wallPosition.y + 16;
	//				Vec2 segs[4] = { Vec2(l,b), Vec2(r,b), Vec2(r,t), Vec2(l,t) };
	//				addSegments(segs, 4);

	//			}
	//		}
	//	}

	getStoreyEdge();
}

// Find intersection of RAY & SEGMENT
bool MaskLayer::getIntersection(const Segment& ray, const Segment& segment, Intersect& out) {
	// RAY in parametric: Point + Delta*T1
	float r_px = ray.a.x;
	float r_py = ray.a.y;
	float r_dx = ray.b.x - ray.a.x;
	float r_dy = ray.b.y - ray.a.y;

	// SEGMENT in parametric: Point + Delta*T2
	float s_px = segment.a.x;
	float s_py = segment.a.y;
	float s_dx = segment.b.x - segment.a.x;
	float s_dy = segment.b.y - segment.a.y;

	// Are they parallel? If so, no intersect
	float r_mag = sqrt(r_dx*r_dx + r_dy*r_dy);
	float s_mag = sqrt(s_dx*s_dx + s_dy*s_dy);
	if (r_dx / r_mag == s_dx / s_mag && r_dy / r_mag == s_dy / s_mag) {
		// Unit vectors are the same.
		return false;
	}

	// SOLVE FOR T1 & T2
	// r_px+r_dx*T1 = s_px+s_dx*T2 && r_py+r_dy*T1 = s_py+s_dy*T2
	// ==> T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy
	// ==> s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx
	// ==> T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)
	float T2 = (r_dx*(s_py - r_py) + r_dy*(r_px - s_px)) / (s_dx*r_dy - s_dy*r_dx);
	float T1 = (s_px + s_dx*T2 - r_px) / r_dx;

	// Must be within parametic whatevers for RAY/SEGMENT
	if (T1 < 0) return false;
	if (T2 < 0 || T2>1) return false;

	// Return the POINT OF INTERSECTION
	out = { r_px + r_dx*T1, r_py + r_dy*T1, T1 };
	return true;
}
MaskLayer::MyPolygon MaskLayer::getSightPolygon(float sightX, float sightY)
{
	// Get all unique points
	std::vector<Vec2> points;
	for (Segment& s : segments)
	{
		bool findA = false;
		bool findB = false;

		for (Vec2& p : points)
		{
			if (p.x == s.a.x && p.y == s.a.y)
				findA = true;
			if (p.x == s.b.x && p.y == s.b.y)
				findB = true;
		}

		if (!findA)
			points.push_back(s.a);
		if (!findB)
			points.push_back(s.b);
	}

	// Get all angles
	std::vector<float> uniqueAngles;
	for (int j = 0; j < points.size(); j++) {
		Vec2 uniquePoint = points[j];
		float angle = atan2(uniquePoint.y - sightY, uniquePoint.x - sightX);

		uniqueAngles.push_back(angle - 0.0001);
		uniqueAngles.push_back(angle);
		uniqueAngles.push_back(angle + 0.0001);
	}

	// RAYS IN ALL DIRECTIONS
	MyPolygon intersects;
	for (int j = 0; j < uniqueAngles.size(); j++) {
		float angle = uniqueAngles[j];

		// Calculate dx & dy from angle
		float dx = cos(angle);
		float dy = sin(angle);

		// Ray from center of screen to mouse
		Segment ray = {
			Vec2(sightX, sightY),
			Vec2(sightX + dx, sightY + dy)
		};

		// Find CLOSEST intersection
		bool first = true;
		Intersect closestIntersect;
		for (int i = 0; i < segments.size(); i++) {
			Intersect intersect;
			if (!getIntersection(ray, segments[i], intersect))
				continue;
			if (first || intersect.param < closestIntersect.param) {
				closestIntersect = intersect;
				first = false;
			}
		}

		// Intersect angle
		if (first) continue;
		closestIntersect.angle = angle;

		// Add to list of intersects
		intersects.push_back(closestIntersect);
	}

	sort(intersects.begin(), intersects.end(), compare_angle);

	// Polygon is intersects, in order of angle
	return intersects;
}

void MaskLayer::drawPolygon(MyPolygon& polygon, Color4F fillStyle)
{
	if (polygon.size() == 0)
		return;

	Vector2dVector vecs;
	for (Intersect& i : polygon)
	{
		vecs.push_back(Vector2d(i.x, i.y));
		//		        ctx->drawDot(Vec2(i.x, i.y), 2, Color4F(0,0,0,1));
	}

	Vector2dVector result;
	Triangulate::Process(vecs, result);

	int tcount = result.size() / 3;
	for (int i = 0; i < tcount; i++)
	{
		Vec2 v[3];
		v[0] = Vec2(result[i * 3 + 0].GetX(), result[i * 3 + 0].GetY());
		v[1] = Vec2(result[i * 3 + 1].GetX(), result[i * 3 + 1].GetY());
		v[2] = Vec2(result[i * 3 + 2].GetX(), result[i * 3 + 2].GetY());
		stencil->drawTriangle(v[0], v[1], v[2], fillStyle);

		//        stencil->drawPolygon(v, 3, fillStyle);
	}
}

void MaskLayer::getStoreyEdge()
{
	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	cocos2d::Point startPoint = storey->getDownCoord();
	memset(temp, 0, sizeof(temp));

	getStoreyEdge(startPoint.x, startPoint.y);
}

void MaskLayer::getStoreyEdge(int x, int y)
{
	temp[x][y] = 1;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();

	cocos2d::Point oriCoord = cocos2d::Point(x, y);
	cocos2d::Point oriPosition = storey->getTilePosition(cocos2d::Point(x, y));

	cocos2d::Point tiles[4];

	for (int i = 0; i < 4; i++)
	{
		tiles[i] = oriCoord;
	}
	tiles[0].x++;
	tiles[1].y++;
	tiles[2].x--;
	tiles[3].y--;

	for (int i = 0; i < 4; i++)
	{
		if (storey->isFloor(tiles[i])
			&& temp[int(tiles[i].x)][int(tiles[i].y)] == 0)
		{
			getStoreyEdge(tiles[i].x, tiles[i].y);
		}
		else if (storey->isWall(tiles[i]))
		{
			Segment edge;
			switch (i)
			{
			case 0:
				edge.a = Vec2(oriPosition.x + 16, oriPosition.y + 16);
				edge.b = Vec2(oriPosition.x + 16, oriPosition.y - 16);
				edge.type = Segment::V;
				break;
			case 1:
				edge.a = Vec2(oriPosition.x - 16, oriPosition.y - 16);
				edge.b = Vec2(oriPosition.x + 16, oriPosition.y - 16);
				edge.type = Segment::H;
				break;
			case 2:
				edge.a = Vec2(oriPosition.x - 16, oriPosition.y - 16);
				edge.b = Vec2(oriPosition.x - 16, oriPosition.y + 16);
				edge.type = Segment::V;
				break;
			case 3:
				edge.a = Vec2(oriPosition.x + 16, oriPosition.y + 16);
				edge.b = Vec2(oriPosition.x - 16, oriPosition.y + 16);
				edge.type = Segment::H;
				break;
			default:
				break;
			}
			segments.push_back(edge);
		}
	}
}
