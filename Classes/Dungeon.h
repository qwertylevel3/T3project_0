#pragma once

#include"Storey.h"

namespace Field {

	class Dungeon
	{
	public:
		Dungeon();
		~Dungeon();
	protected:
		std::vector<Storey*> storeys;
	};

}

