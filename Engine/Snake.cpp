#include "Snake.h"

Snake::Snake(const Location & loc)
{
	constexpr int nbodyColors = 4;
	constexpr Color bodyColors[nbodyColors] = { { 10,100,32 },{10,130,48},{18,160,48},{10,130,48} };
	for (int i = 0; i < maxSegs; i++)
	{
		segments[i].InitBody(bodyColors[i % nbodyColors]);
	}
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & deltaLoc)
{
	for (int i = nSegs - 1; i > 0; i--)
		segments[i].Follow(segments[i - 1]);
	segments[0].MoveBy(deltaLoc);
}

void Snake::Grow()
{
	if (nSegs < maxSegs)
	{
		nSegs++;
	}
		
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegs; i++)
		segments[i].Draw(brd);
}

Location Snake::GetNextHeadLoc(const Location & deltaLoc) const
{
	Location l(segments[0].getLoc());
	l.Add(deltaLoc);
	return l;
}

bool Snake::TileCollision(const Location &body) const
{
	for (int i= 0; i < nSegs-1; i++)
		if(segments[i].getLoc() == body)
			return true;
	return false;
}

bool Snake::TilesAvailable(const Location &body)const
{
	for (int i = 0; i < nSegs; i++)
		if (segments[i].getLoc() == body)
			return true;
	return false;
}

void Snake::resetSegs()
{
	nSegs = 1;
}

void Snake::Segment::Follow(const Segment &next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::InitHead(const Location &hloc)
{
	loc = hloc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color cin)
{
	c = cin;
}

void Snake::Segment::MoveBy(const Location &deltaLoc)
{
	assert(abs(deltaLoc.x) + abs(deltaLoc.y) == 1);
	loc.Add(deltaLoc);
}

const Location &Snake::Segment::getLoc() const
{
	return loc;
}
