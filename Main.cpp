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
	void drawMaze()
	{
		for (int x = 1; x <= maze.w; x++)												//ScreenWidth(); x++)
		{
			for (int y = 1; y <= maze.h; y++)											//ScreenHeight(); y++)
			{
				switch (maze.graph[x - 1][y - 1].tile)
					{
					default:
						break;
					case 0:
					{
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::BLACK));
						break;
					}
					case 1:
					{
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::WHITE));
						if (maze.graph[x - 1][y - 1].returnPaths().first)							//if it has an east connection, draw it
						{
							DrawLine((x * 10) + 9, y * 10, (x * 10) + 9, (y * 10) + 8, olc::WHITE);
						}
						if (maze.graph[x - 1][y - 1].returnPaths().second)							//if it has a south connection, draw it
						{
							DrawLine((x * 10), (y * 10) + 9, (x * 10) + 8, (y * 10) + 9, olc::WHITE);
						}
						break;
					}
					case 2:
					{
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::BLUE));
						if (maze.graph[x - 1][y - 1].returnPaths().first)							//if it has an east connection, draw it
						{
							DrawLine((x * 10) + 9, y * 10, (x * 10) + 9, (y * 10) + 8, olc::WHITE);
						}
						if (maze.graph[x - 1][y - 1].returnPaths().second)							//if it has a south connection, draw it
						{
							DrawLine((x * 10), (y * 10) + 9, (x * 10) + 8, (y * 10) + 9, olc::WHITE);
						}
						break;
					}
				}


			}

		}
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		Maze maze;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::Pixel(olc::BLACK));		
		drawMaze();

		return true;
	}

};


int main()
{
	Pathfinder demo;
	if (demo.Construct(1024, 960, 10, 10, 1,1,1))
		demo.Start();

	return 0;
}