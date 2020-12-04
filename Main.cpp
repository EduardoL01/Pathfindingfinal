#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Maze.h"

class Pathfinder : public olc::PixelGameEngine
{
public:

	Maze maze;

	Pathfinder()
	{
		sAppName = "Pathfinder";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		Maze maze;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::Pixel(olc::GREY));

		for (int x = 0; x <	maze.w; x++)												//ScreenWidth(); x++)
			for (int y = 0; y <	maze.h; y++)											//ScreenHeight(); y++)
			{
				switch (maze.graph[x][y].tile)
				{
				default:
					break;
				case 0:
					FillRect(x * 10, y* 10, 8, 8, olc::Pixel(olc::GREY));
					//Draw(x, y, olc::Pixel(olc::BLACK));
					break;
				case 1:
					FillRect(x * 10, y * 10, 8, 8, olc::Pixel(olc::WHITE));
					//Draw(x, y, olc::Pixel(olc::WHITE));
					break;
				case 2:
					FillRect(x * 10, y * 10, 8, 8, olc::Pixel(olc::BLUE));
					//Draw(x, y, olc::Pixel(olc::BLUE));
					break;
				}
				

			}

		;

		return true;
	}
};


int main()
{
	Pathfinder demo;
	if (demo.Construct(512, 480, 4, 4))
		demo.Start();

	return 0;
}