#include "Storey.h"
#include"FieldEnum.h"

using namespace Field;

Storey::Storey(int w,int h)
{

	for (int i = 0; i < w*h; i++)
	{
		tiles.push_back(Unused);
	}
	width = w;
	height = h;
}


Storey::~Storey()
{
}

int Storey::getTile(int x,int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return Unused;
		exit(-1);
	}
	return tiles[x + y * width];
}

void Storey::setTile(int x, int y,int tile)
{
	tiles[x + y * width] = tile;
}

int Storey::getHeight()
{
	return height;
}


int Storey::getWidth()
{
	return width;
}


