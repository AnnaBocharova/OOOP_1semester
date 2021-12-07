#include <vector>
#include "Help.h"
#include "Kick.h"

std::vector<Position> get_wall_kick_data(bool shape, unsigned char rotation, unsigned char next_rotation)
{
	

	if (!shape)
	{
		switch (rotation)
		{
		case 0:
		case 2:
		{
			switch (next_rotation)
			{
			case 1:
			{
				return { {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
			}
			case 3:
			{
				return { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} };
			}
			}
		}
		case 1:
		{
			return { {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2} };
		}
		case 3:
		{
			return { {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
		}
		}

		return { {0, 0} };
	}
	else
	{
		switch (rotation)
		{
		case 0:
		{
			switch (next_rotation)
			{
			case 1:
			{
				return { {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2} };
			}
			case 3:
			{
				return { {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1} };
			}
			}
		}
		case 1:
		{
			switch (next_rotation)
			{
			case 0:
			{
				return { {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2} };
			}
			case 2:
			{
				return { {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1} };
			}
			}
		}
		case 2:
		{
			switch (next_rotation)
			{
			case 1:
			{
				return { {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1} };
			}
			case 3:
			{
				return { {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2} };
			}
			}
		}
		case 3:
		{
			switch (next_rotation)
			{
			case 0:
			{
				return { {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1} };
			}
			case 2:
			{
				return { {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2} };
			}
			}
		}
		}

		return { {0, 0} };
	}
}