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

		Storey* generate(int level);
		void init();
	private:
		bool createFeature();
		bool createFeature(int x, int y, Direction dir);

		bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
		bool makeCorridor(int x, int y, Direction dir);

		bool placeRect(const Rect& rect, int tile);
		bool placeObject(int tile);
		void placeGameActor(int x, int y, Character* character);
		void placeGameActorLevel1(const Rect& rect);
		void placeGameActorLevel2(const Rect& rect);
		void placeGameActorAllRoom(int level);



		std::vector<Rect> rooms;
		std::vector<Rect> exits;
		Storey* storey;

	};


}
