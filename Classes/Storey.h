#pragma once

#include<tinyxml2\tinyxml2.h>
#include"cocos2d.h"
#include <list>

class Character;


namespace Field {

	class Storey
	{
	public:
		Storey(int w, int h);
		~Storey();
		cocos2d::Point getTilePosition(cocos2d::Point coord);
		int getTile(int x, int y);
		int getTile(cocos2d::Point coord);
		void setTile(int x, int y, int tile);

		Character* getCharacter(int x, int y);
		Character* getCharacter(cocos2d::Point position);
		std::list<Character* >& getAllCharacter();
		void characterMoveUp(Character* character);
		void characterMoveDown(Character* character);
		void characterMoveLeft(Character* character);
		void characterMoveRight(Character* character);
		void setCharacter(int x, int y, Character* character);
		void removeCharacter(int x, int y);
		void removeCharacter(Character* character);
		void characterMove(cocos2d::Point oriPosition, cocos2d::Point tarPosition);

		bool isMoveAble(cocos2d::Point position);

		int getHeight();
		int getWidth();
		void writeToFile(std::string floor);
		std::string getFileContent();
		tinyxml2::XMLDocument* getPDoc();
		cocos2d::TMXTiledMap *getTileMap();
		std::vector<Character*>& getCharacterMap();
	protected:
		int height;
		int width;
		CC_SYNTHESIZE(cocos2d::Point, upCoord, UpCoord);
		CC_SYNTHESIZE(cocos2d::Point, downCoord, DownCoord);
		std::string picturePath;
		//逻辑地图
		std::vector<int> tiles;
		//所有角色位置地图
		std::vector<Character*> characterMap;
		//所有角色列表
		std::list<Character*> characterList;
		//用于显示
		cocos2d::TMXTiledMap *tileMap;
	};
}

