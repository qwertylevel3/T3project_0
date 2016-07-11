#pragma once

#include<vector>
#include<tinyxml2\tinyxml2.h>
#include"cocos2d.h"


namespace Field {

	class Storey
	{
	public:
		Storey(int w, int h);
		~Storey();
		int getTile(int x, int y);
		void setTile(int x, int y, int tile);

		int getHeight();
		int getWidth();
		void writeToFile(std::string floor);
		std::string getFileContent();
		tinyxml2::XMLDocument* getPDoc();
	protected:
		int height;
		int width;
		CC_SYNTHESIZE(cocos2d::Point, upPosition, UpPosition);
		CC_SYNTHESIZE(cocos2d::Point, downPosition, DownPosition);
		std::string picturePath;
		std::vector<int> tiles;
	};

}

