#pragma once

#include<vector>
#include<tinyxml2\tinyxml2.h>


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
		tinyxml2::XMLDocument* getPDoc();
	protected:
		int height;
		int width;
		std::string picturePath;
		std::vector<int> tiles;
	};

}

