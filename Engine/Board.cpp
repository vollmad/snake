#include "Board.h"

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < wid);
	assert(loc.y >= 0);
	assert(loc.y < hgt);
	const int offx = x + bwid + bpad;
	const int offy = y + bwid + bpad;
	gfx.DrawRectDim(loc.x* dimension+offx+cpad, loc.y*dimension+offy+cpad, dimension-cpad*2,dimension - cpad * 2, c);
}

int Board::getGridWid() const
{
	return wid;
}

int Board::getGridHgt() const
{
	return hgt;
}

bool Board::isBoardCollision(const Location & loc)const
{
	return loc.x >= 0 && loc.x < wid && loc.y >= 0 && loc.y < hgt;
}

void Board::drawBoarder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (bwid + bpad) * 2+ hgt*dimension;
	const int right = left + (bwid + bpad) * 2 + wid*dimension;
	//top
	gfx.DrawRect(left, top, right, top + bwid, bcolor);
	//left
	gfx.DrawRect(left, top + bwid, left + bwid, bottom - bwid, bcolor);
	//right
	gfx.DrawRect(right - bwid, top + bwid, right, bottom - bwid, bcolor);
	//bottom
	gfx.DrawRect(left, bottom - bwid,right, bottom, bcolor);
}
