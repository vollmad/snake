/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snake({2,2}),
	goal(rng,brd,snake)
{//num num num
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::reset(int dir)
{
	snakeVelocity = 20;
	snakeMoveCounter = 0;
	snkSpeedUpCnt = 0;
	snake.resetSegs();
	if (dir ==1)
		dLc = { -1, 0 };
	if (dir ==2)
		dLc = { +1, 0 };
	if (dir==3)
		dLc = { 0, +1 };
	if (dir==4)
		dLc = { 0, -1 };
	
}

void Game::UpdateModel()
{
	if (gameInProgress)
	{
		if (!gameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				dLc = { 1, 0 };
				lastDirect = 1;
			}
				
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				dLc = { -1, 0 };
				lastDirect = 2;
			}
				
			if (wnd.kbd.KeyIsPressed(VK_UP)) 
			{
				dLc = { 0, -1 };
				lastDirect = 3;
			}
				
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				dLc = { 0, 1 };
				lastDirect = 4;
			}
				
			snakeMoveCounter++;

			if (snakeMoveCounter >= snakeVelocity)
			{
				snakeMoveCounter = 0;
				const Location next = snake.GetNextHeadLoc(dLc);
				if (!brd.isBoardCollision(next) ||
					snake.TileCollision(next))
					gameOver = true;
				else
				{
					const bool eaten = next == goal.GetLoc();
					if (eaten)
					{
						snake.Grow();
					}
					snake.MoveBy(dLc);
					if (eaten)
					{
						goal.Respawn(rng, brd, snake);
					}
				}

			}
			snkSpeedUpCnt++;

			if (snkSpeedUpCnt >= snkSpeedPeriod)
			{
				snkSpeedUpCnt = 0;
				snakeVelocity = std::max(snakeVelocity -1, snakePeriodMin);
			}
		}
	}
	else gameInProgress = wnd.kbd.KeyIsPressed(VK_RETURN);
}
	
void Game::ComposeFrame()
{
	if (gameInProgress)
	{
		snake.Draw(brd);
		goal.Draw(brd);
		if (gameOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameInProgress = true;
			gameOver = false;
			
			reset(lastDirect);
		}
		brd.drawBoarder();
	}
	else SpriteCodex::DrawTitle(290, 200, gfx);
}
