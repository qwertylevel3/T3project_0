#pragma once

#include"Storey.h"

namespace Field {

	class Dungeon
	{
	public:
		Dungeon();
		~Dungeon();

		int getFloorNum();
		void addStorey(Storey* storey);
		Storey* getStorey(int floor);
		void writeToFile();
	protected:
		std::vector<Storey*> storeys;
	};

}

