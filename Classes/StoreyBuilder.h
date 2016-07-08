#pragma once

#include"Singleton.h"
#include<vector>
#include<random>
#include"Storey.h"
#include"FieldEnum.h"

namespace Field {

	class StoreyBuilder :public Singleton<StoreyBuilder>
	{
	public:
		StoreyBuilder();
		~StoreyBuilder();

		Storey* generate();
		void init();
	private:
		bool createFeature();
		bool createFeature(int x, int y, Direction dir);

		bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
		bool makeCorridor(int x, int y, Direction dir);

		bool placeRect(const Rect& rect, int tile);
		bool placeObject(int tile);



		std::vector<Rect> rooms;
		std::vector<Rect> exits;
		Storey* storey;
	};


}
