#include "Block.h"

Block::Block()
{
	G = H = F = 0;
	pos = { 0,0 };
}

Block::Block(int g, int h, int f, POINT p, Status t)
{
	G = g;
	H = h;
	F = f;
	
	pos = p;
	st = t;

}
