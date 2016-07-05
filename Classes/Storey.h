#pragma once

#include<vector>

namespace Field {

class Storey
{
public:
	Storey(int w,int h);
	~Storey();
	int getTile(int x,int y);
	void setTile(int x,int y,int tile);

	int getHeight();

	int getWidth();
protected:
	int height;
	int width;
	std::vector<int> tiles;
};

}

