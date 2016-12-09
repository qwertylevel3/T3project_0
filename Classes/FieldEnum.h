#pragma once

namespace Field {

	enum Tile
	{
		Unused = 1,
		Ice = 2,
		Floor = 21,
		Corridor = 21,
		Wall = 110,
		Trap=51,
		ClosedDoor = 21,
		OpenDoor = 21,
		UpStair = 7,
		DownStair = 8
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
