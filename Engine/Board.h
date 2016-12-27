#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
class Board 
{
public:
	Board(Graphics &gfx);
	void DrawCell(const Location &loc, Color c);
	int getGridWid() const;
	int getGridHgt() const;
	bool isBoardCollision(const Location &loc)const;
	void drawBoarder();
private:
	static constexpr int dimension = 20, wid = 32, hgt = 24, x = 70, y = 50, bwid = 4, bpad = 2,cpad = 1;;
	static constexpr Color bcolor = Colors::Blue;
	Graphics &gfx;
};