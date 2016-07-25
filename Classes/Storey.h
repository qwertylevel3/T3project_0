#pragma once

#include<vector>
#include<tinyxml2\tinyxml2.h>
#include"cocos2d.h"

class Character;


namespace Field {

	class Storey
	{
	public:
		Storey(int w, int h);
		~Storey();
		int getTile(int x, int y);
		int getTile(cocos2d::Point position);
		void setTile(int x, int y, int tile);

		Character* getCharacter(int x, int y);
		Character* getCharacter(cocos2d::Point position);
		void setCharacter(int x, int y, Character* character);

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
		std::vector<Character*> characterMap;
	};
}

