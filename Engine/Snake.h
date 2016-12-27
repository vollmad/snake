#pragma once
#include "Board.h"
#include "assert.h"
class Snake
{
private:
	class Segment
	{
	private:
		Location loc;
		Color c;
	public:
		void Follow(const Segment &next);
		void Draw(Board &brd) const;
		void InitHead(const Location &hloc);
		void InitBody(Color c);
		void MoveBy(const Location &deltaLoc);
		const Location &getLoc() const;
	};

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int maxSegs = 100;
	Segment segments[maxSegs];
	int nSegs = 1;
public:
	Snake(const Location &loc);
	void MoveBy(const Location &deltaLoc);
	void Grow();
	void Draw(Board & brd) const;
	Location GetNextHeadLoc(const Location &deltaLoc) const;
	bool TileCollision(const Location &body) const;
	bool TilesAvailable(const Location &body) const;
	void resetSegs();
};
