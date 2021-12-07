#include <vector>
#include "Help.h"
#include "GetFigures.h"

std::vector<Position> get_tetromino(unsigned char shape, unsigned char x, unsigned char y)
{
	
	std::vector<Position> tetromino(4);

	switch (shape)
	{
	case 0:
	{
		tetromino[0] = { 1, -1 };
		tetromino[1] = { 0, -1 };
		tetromino[2] = { -1, -1 };
		tetromino[3] = { -2, -1 };

		break;
	}
	case 1:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 1, 0 };
		tetromino[2] = { -1, -1 };
		tetromino[3] = { -1, 0 };

		break;
	}
	case 2:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 1, 0 };
		tetromino[2] = { 1, -1 };
		tetromino[3] = { -1, 0 };

		break;
	}
	case 3:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 0, -1 };
		tetromino[2] = { -1, -1 };
		tetromino[3] = { -1, 0 };

		break;
	}
	case 4:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 1, -1 };
		tetromino[2] = { 0, -1 };
		tetromino[3] = { -1, 0 };

		break;
	}
	case 5:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 1, 0 };
		tetromino[2] = { 0, -1 };
		tetromino[3] = { -1, 0 };

		break;
	}
	case 6:
	{
		tetromino[0] = { 0, 0 };
		tetromino[1] = { 1, 0 };
		tetromino[2] = { 0, -1 };
		tetromino[3] = { -1, -1 };
	}
	}

	
	for (Position& mino : tetromino)
	{
		mino.x +=x;
		mino.y +=y;
	}	
	return tetromino;
}