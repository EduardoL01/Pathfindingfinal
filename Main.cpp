#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Maze.h"

class Pathfinder : public olc::PixelGameEngine
{
public:

	Maze maze;
	bool randomize = 0, startup = 0, bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
	bool rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;

	Pathfinder()
	{
		sAppName = "Pathfinder";
	}

public:

	void finishRand()
	{
		Maze::node* current = NULL;
		Maze::node* chosen = NULL;
		
		//push starting node onto rstack and mark as visited only if stack is empty
		if (maze.rStack.empty())
		{
			maze.rStack.push(maze.sNode);
			maze.sNode->visited = true;
		}
		
		//while the stack is not empty
		while (!maze.rStack.empty())
		{
			//pop node from stack and make it current node
			current = maze.rStack.top();

			vector<Maze::node*> unvisit = current->returnAdj();

			if (!unvisit.empty())
			{
				//choose a random unvisited neighbor
				chosen = unvisit[rand() % unvisit.size()];

				if (chosen->tile != 2)
				{
					chosen->tile = 1;
				}
				chosen->visited = 1;
				current->neighbors.push_back(chosen);
				chosen->neighbors.push_back(current);
				maze.rStack.push(chosen);
			}
			else
			{
				maze.rStack.pop();
			}
		}
	}

	bool randomizeDraw(bool init)
	{
		Maze::node* chosen = NULL;
		Maze::node* current = NULL;
		//push starting node onto rstack and mark as visited if we're beginning randomize process
		if (init)
		{
			maze.rStack.push(maze.sNode);
			maze.sNode->visited = true;
		}
		
		//while the stack is not empty
		if (!maze.rStack.empty())
		{
			//pop node from stack and make it current node
			current = maze.rStack.top();

			vector<Maze::node*> unvisit = current->returnAdj();

			if (!unvisit.empty())
			{
				//choose a random unvisited neighbor
				chosen = unvisit[rand() % unvisit.size()];

				//process chosen
				if (chosen->tile != 2)
				{
					chosen->tile = 1;
				}
				
				chosen->visited = 1;
				current->neighbors.push_back(chosen);
				chosen->neighbors.push_back(current);
				maze.rStack.push(chosen);
			}
			else
			{
				maze.rStack.pop();
			}
		}
		else
		{
			return false;
		}

		int x = current->loc.first + 1;
		int y = current->loc.second + 1;
		FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::GREEN));
		if (maze.graph[x - 1][y - 1].returnPaths().first)							//if it has an east connection, draw it
		{
			DrawLine((x * 10) + 9, y * 10, (x * 10) + 9, (y * 10) + 8, olc::WHITE);
		}
		if (maze.graph[x - 1][y - 1].returnPaths().second)							//if it has a south connection, draw it
		{
			DrawLine((x * 10), (y * 10) + 9, (x * 10) + 8, (y * 10) + 9, olc::WHITE);
		}
		return true;
	}

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
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::BLUE));
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
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(255, 128, 0));					//draws an orange pixel
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

	bool OnUserReset()
	{
		this->maze = Maze();
		Maze::node* stackNode = NULL;
		randomize = 0, startup = 0, bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
		rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;
		return true;
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		Maze maze;
		Maze::node* stackNode = NULL;
		randomize = 0, startup = 0, bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
		rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;
		srand(1);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		//this_thread::sleep_for(0.5ms);
		Clear(olc::Pixel(olc::BLACK));
		drawMaze();

		if (GetKey(olc::Key::S).bPressed)
		{
			randomize = true;
			startup = true;
		}
		else if (GetKey(olc::Key::R).bPressed && startup)
		{
			OnUserReset();
		}
		else if (GetKey(olc::Key::NP1).bPressed && startup)
		{
			dfs = true;
		}
		else if (GetKey(olc::Key::NP2).bPressed && startup)
		{
			bfs = true;
		}
		else if (GetKey(olc::Key::NP3).bPressed && startup)
		{
			djs = true;
		}
		else if (GetKey(olc::Key::NP4).bPressed && startup)
		{
			astar = true;
		}
		else if (GetKey(olc::Key::S).bHeld && GetKey(olc::Key::SHIFT).bHeld && rComplete == false && randomize == false)
		{
			rComplete = true;
			finishRand();

		}
		else if (GetKey(olc::Key::ESCAPE).bPressed)
		{
			exit(1);
		}

		if (!rComplete && randomizeDraw(randomize))						
		{
			randomize = false;
		}

		return true;
	}

	bool BFS(bool init)
	{
		if (init)
		{
			Maze::node* current = NULL;
			map<Maze::node*, bool> visited;
			maze.BFSq.push(maze.sNode);
			visited.emplace(maze.sNode, true);
			while (!maze.BFSq.empty())
			{
				current = maze.BFSq.front();									//pop off top node
				maze.BFSq.pop();
				if (current = maze.eNode)										//if the end is reached, exit
				{
					return false;
				}
				for (int i = 0; i < current->adj.size(); i++)					//iterate through its connected neighbors
				{
					if (!visited.count(current->adj[i]))						//if the neighbor is unvisited
					{
						maze.BFSq.push(current->adj[i]);						//enqueue it
					}
				}
			}
		}

		return false;
	}

	bool DFS(bool init)
	{
		if (init)
		{
			Maze::node* current = NULL;
			map<Maze::node*, bool> visited;
			maze.DFSs.push(maze.sNode);
			visited.emplace(maze.sNode, true);
			while (!maze.DFSs.empty())
			{
				current = maze.DFSs.top();										//pop off top node
				maze.DFSs.pop();
				if (current = maze.eNode)										//if the end is reached, exit
				{
					return false;
				}
				for (int i = 0; i < current->adj.size(); i++)					//iterate through its connected neighbors
				{
					if (!visited.count(current->adj[i]))						//if the neighbor is unvisited
					{
						maze.DFSs.push(current->adj[i]);						//enqueue it
					}
				}
			}
		}
		return false;
	}

	bool Djikstra(bool init)
	{
		set<Maze::node*> processed;
		set<Maze::node*> unprocessed;
		map<Maze::node*, int> distances;										//all distances need to be initialized to 0

		map<Maze::node*, Maze::node*> predecessor;
	}
};

int main()
{
	Pathfinder demo;
	if (demo.Construct(512, 480, 10, 10, 1,1,1))
		demo.Start();

	return 0;
}