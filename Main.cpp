#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Maze.h"

class Pathfinder : public olc::PixelGameEngine
{
public:

	Maze maze;
	bool randomize = 0, startup = 0, bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
	bool rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;
	bool bfsRun, dfsRun, astarRun = 0;

	Pathfinder()
	{
		sAppName = "Pathfinder";
	}

public:

	bool Djikstra(bool init)
	{
		set<Maze::node*> processed;
		set<Maze::node*> unprocessed;
		map<Maze::node*, int> distances;										//all distances need to be initialized to 0

		map<Maze::node*, Maze::node*> predecessor;
	}

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

	bool DFS(bool init)
	{
		Maze::node* current = NULL;
		if (init)
		{
			maze.DFSs.push(maze.sNode);
			maze.visitedDFS[maze.sNode] = true;
			dfsRun = true;
		}

		if (!maze.DFSs.empty())
		{
			current = maze.DFSs.top();										//pop off top node
			maze.DFSs.pop();

			if (current == maze.eNode)										//if the end is reached, exit
			{
				std::cout << "end node reaached" << std::endl;
				while (!maze.DFSs.empty())
				{
					//current = maze.DFSs.top();
					//current->tile = 3;
					maze.DFSs.pop();
				}
				return false;
			}

			if (!maze.visitedDFS[current])
			{
				maze.visitedDFS[current] = true;
			}

			for (int i = 0; i < current->neighbors.size(); i++)					//iterate through its connected neighbors
			{
				if (!maze.visitedDFS[current->neighbors[i]])						//if the neighbor is unvisited
				{
					maze.visitedDFS[current->neighbors[i]] = true;				//set node to visited
					current->neighbors[i]->parent = current;					//set parent

					int x = current->neighbors[i]->loc.first + 1;
					int y = current->neighbors[i]->loc.second + 1;
					current->neighbors[i]->tile = 2;
					FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::GREEN));

					maze.DFSs.push(current->neighbors[i]);						//enqueue it
				}
			}
		}
		else
		{
			//dfsComplete = true;
			if (maze.eNode->parent != NULL)
			{
				Maze::node* temp = maze.eNode->parent;
				int l = 0;
				int k = 0;
				while (temp->parent != NULL)
				{

					int j = 0;
					for (int i = 0; i < temp->neighbors.size(); i++)
					{
						if (maze.visitedDFS[temp->neighbors[i]])
						{
							j++;
						}

					}
					if (j == temp->neighbors.size())
					{
						temp->tile = 4;
						if (k % 8 == 0)
						{
							l += 3;
						}

						temp->R = 255 - l;
						temp->G = 0;
						temp->B = 0 + l;

					}
					temp = temp->parent;
					k++;
				}
				dfsComplete = true;
			}
			maze.sNode->tile = 3;
			maze.eNode->tile = 3;
			dfsRun = false;
			return false;
		}

	}

	bool BFS(bool init)
	{
		Maze::node* current = NULL;
		if (init)
		{
			bfsRun = true;
			maze.BFSq.push(maze.sNode);
			maze.visitedBFS[maze.sNode] = true;

		}
		if (!maze.BFSq.empty())
		{
			current = maze.BFSq.front();									//pop off top node
			maze.BFSq.pop();
			if (current == maze.eNode)										//if the end is reached, exit
			{
				while (!maze.BFSq.empty())
				{
					//current = maze.BFSq.front();
					//current->tile = 3;
					maze.BFSq.pop();
				}
				return false;
			}

			if (!maze.visitedBFS[current])
			{
				maze.visitedBFS[current] = true;
			}

			for (int i = 0; i < current->neighbors.size(); i++)					//iterate through its connected neighbors
			{
				if (!maze.visitedBFS[current->neighbors[i]])						//if the neighbor is unvisited
				{
					maze.visitedBFS[current->neighbors[i]] = true;
					current->neighbors[i]->parent = current;

					int x = current->neighbors[i]->loc.first + 1;
					int y = current->neighbors[i]->loc.second + 1;
					current->neighbors[i]->tile = 2;
					FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::GREEN));

					maze.BFSq.push(current->neighbors[i]);						//enqueue it
				}
			}
		}
		else
		{
			if (maze.eNode->parent != NULL)
			{
				Maze::node* temp = maze.eNode->parent;
				int l = 0;
				int k = 0;

				while (temp->parent != NULL)
				{

					int j = 0;
					for (int i = 0; i < temp->neighbors.size(); i++)
					{
						if (maze.visitedBFS[temp->neighbors[i]])
						{
							j++;
						}

					}
					if (j == temp->neighbors.size())
					{
						temp->tile = 4;
						if (k % 8 == 0)
						{
							l += 3;
						}

						temp->R = 255 - l;
						temp->G = 0;
						temp->B = 0 + l;

					}
					temp = temp->parent;
					k++;
				}
				maze.sNode->tile = 3;
				maze.eNode->tile = 3;
				bfsComplete = true;
				bfsRun = false;
			}
			return false;
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
			if (startup)
			{
				rComplete = true;
			}
			return false;
		}

		int x = current->loc.first + 1;
		int y = current->loc.second + 1;
		FillRect(x * 10, y * 10, 9, 9, olc::Pixel(olc::GREEN));
		//if (maze.graph[x - 1][y - 1].returnPaths().first)							//if it has an east connection, draw it
		//{
		//	DrawLine((x * 10) + 9, y * 10, (x * 10) + 9, (y * 10) + 8, olc::WHITE);
		//}
		//if (maze.graph[x - 1][y - 1].returnPaths().second)							//if it has a south connection, draw it
		//{
		//	DrawLine((x * 10), (y * 10) + 9, (x * 10) + 8, (y * 10) + 9, olc::WHITE);
		//}
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
					case 3:
					{
						FillRect(x * 10, y * 10, 9, 9, olc::GREEN);					//draws a green pixel
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
					case 4:	//to draw a color scale of the path
					{
						FillRect(x * 10, y * 10, 9, 9, olc::Pixel(maze.graph[x - 1][y - 1].R, maze.graph[x - 1][y - 1].G, maze.graph[x - 1][y - 1].B) );					//draws a pixel with the tiles RGB
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

	void clearMaze()
	{
		for (int x = 0; x < maze.w ; x++)
		{
			for (int y = 0; y<maze.h;y++)
			{
				maze.graph[x][y].parent = NULL;
				maze.graph[x][y].tile = 1;
			}
		}
		maze.eNode->tile = 3;
		maze.sNode->tile = 3;
		bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
		rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;
		dfsRun, bfsRun = 0;
		maze.visitedBFS.clear();
		maze.visitedDFS.clear();
		while (!maze.DFSs.empty())
		{
			maze.DFSs.pop();
		}
		while (!maze.BFSq.empty())
		{
			maze.BFSq.pop();
		}
	}

	bool OnUserReset()
	{
		this->maze = Maze();
		Maze::node* stackNode = NULL;
		randomize = 0, startup = 0, bfs = 0, dfs = 0, djs = 0, astar = 0, reset = 0;
		rComplete = 0, startupComplete = 0, dfsComplete = 0, bfsComplete = 0, djsComplete = 0, astarComplete = 0;
		dfsRun, bfsRun = 0;
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


		if (GetKey(olc::Key::S).bHeld && GetKey(olc::Key::SHIFT).bHeld && rComplete == false && randomize == false)
		{
			rComplete = true;
			if (!startup)
			{
				startup = 1;
			}
			finishRand();

		}
		else if (GetKey(olc::Key::S).bPressed && !randomize && maze.rStack.empty())
		{
			randomize = true;
			startup = true;
		}
		else if (GetKey(olc::Key::R).bPressed && startup)
		{
			OnUserReset();
		}
		else if (GetKey(olc::Key::D).bPressed && startup && rComplete && !dfsComplete && !bfsRun)
		{
			dfs = true;
		}
		else if (GetKey(olc::Key::B).bPressed && startup && rComplete && !dfsRun)
		{
			bfs = true;
		}
		else if (GetKey(olc::Key::Q).bPressed && startup)
		{
			djs = true;
		}
		else if (GetKey(olc::Key::NP4).bPressed && startup)
		{
			astar = true;
		}
		else if (GetKey(olc::Key::ESCAPE).bPressed)
		{
			exit(1);
		}
		else if (GetKey(olc::Key::Z).bPressed && startup)
		{
			clearMaze();
		}

		if (!rComplete && randomizeDraw(randomize))						
		{
			randomize = false;
		}

		if (!bfsComplete && BFS(bfs))
		{
			bfs = false;
		}
		if (!dfsComplete && DFS(dfs))
		{
			dfs = false;
		}

		return true;
	}

	
};

int main()
{
	Pathfinder demo;
	if (demo.Construct(512, 480, 10, 10, 1,0,1))
		demo.Start();

	return 0;
}