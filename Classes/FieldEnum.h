#pragma once

namespace Field {

	enum Tile
	{
		Unused = 1,
		Ice = 5,
		Floor = 2,
		Corridor = 6,
		Wall = 3,
		Trap=4,
		ClosedDoor = 7,
		OpenDoor = 8,
		UpStair = 9,
		DownStair = 10
	};
	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

	struct Rect
	{
		int x, y;
		int width, height;
	};

}
