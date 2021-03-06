#include "Maze.h"

Maze::Maze()
{
	w = 100;														//TODO: BUG FOUND if h < w, subscript error
	h = 95;

	start = make_pair(w/2, h/2);
	int dir = rand() % 4;								//randomly chooses a corner upon creation of maze
	switch (dir)
	{
	default:
		break;
	case 0:
		end = make_pair(w - 1, h - 1);
		break;
	case 1:
		end = make_pair(0, 0);
		break;
	case 2:
		end = make_pair(0, h - 1);
		break;
	case 3:
		end = make_pair(w - 1, 0);
		break;
	}
	//end = make_pair(w - 1, h - 1);

	

	graph.resize(w);
	for (int i = 0; i < w; i++)
	{
		graph[i].resize(h);
	}

	graph[start.first][start.second].tile = 3;							//sets ending and start nodes
	graph[end.first][end.second].tile = 3;
	sNode = &graph[start.first][start.second];
	eNode = &graph[end.first][end.second];

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			visitedBFS.emplace(&graph[x][y], false);
			graph[x][y].tile = 0;									//sets default tiles to closed
			graph[x][y].loc = make_pair(x, y);
			graph[x][y].hScore = calcDist(graph[x][y], *eNode);		//sets default hscore values equal to the distance to the end node
			if (x == 0 && y == 0)									//top left edgecase
			{
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x][y + 1]);
			}																
			else if (x == 0 && y == h - 1)							//bot left edgecase
			{
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x][y - 1]);
			}
			else if (x == w - 1 && y == 0)							//top right edgecase
			{
				graph[x][y].adj.push_back(&graph[x - 1][y]);
				graph[x][y].adj.push_back(&graph[x][y + 1]);
			}
			else if (x == w - 1 && y == h - 1)						//bot right edgecase
			{
				graph[x][y].adj.push_back(&graph[x - 1][y]);
				graph[x][y].adj.push_back(&graph[x][y - 1]);
			}
			else if (x == 0 && (y > 0 && y < h - 1) )				//leftside edge
			{
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x][y + 1]);
				graph[x][y].adj.push_back(&graph[x][y - 1]);
			}
			else if (x == w - 1 && (y > 0 && y < h - 1) )			//rightside edge
			{
				graph[x][y].adj.push_back(&graph[x - 1][y]);
				graph[x][y].adj.push_back(&graph[x][y + 1]);
				graph[x][y].adj.push_back(&graph[x][y - 1]);
			}
			else if (y == 0 && (x > 0 && x < w - 1))				//topside edge
			{
				graph[x][y].adj.push_back(&graph[x][y + 1]);
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x - 1][y]);
			}
			else if (y == h - 1 && (x > 0 && x < w - 1))			//botside edge
			{
				graph[x][y].adj.push_back(&graph[x][y - 1]);
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x - 1][y]);
			}
			else
			{
				graph[x][y].adj.push_back(&graph[x][y + 1]);
				graph[x][y].adj.push_back(&graph[x][y - 1]);
				graph[x][y].adj.push_back(&graph[x + 1][y]);
				graph[x][y].adj.push_back(&graph[x - 1][y]);
			}
		}
	}


}



void Maze::randomize()
{
	node* current = NULL;
	node* chosen = NULL;
	//initialize random seed
	srand(1);
	//push starting node onto rstack and mark as visited
	rStack.push(sNode);
	sNode->visited = true;
	//while the stack is not empty
	while (!rStack.empty())
	{
		//pop node from stack and make it current node
		current = rStack.top();

		vector<node*> unvisit = current->returnAdj();

		if (!unvisit.empty())
		{
			//choose a random unvisited neighbor
			chosen = unvisit[rand() % unvisit.size()];

			//process chosen
			chosen->tile = 1;
			chosen->visited = 1;
			current->neighbors.push_back(chosen);
			chosen->neighbors.push_back(current);
			rStack.push(chosen);
		}
		else
		{
			rStack.pop();
		}
	}

	eNode->tile = 2;
}


double Maze::calcDist(Maze::node& a, Maze::node& b)
{
	double dx = pow(a.loc.first - b.loc.first, 2.0);
	double dy = pow(a.loc.second - b.loc.second, 2.0);

	return sqrt(dx + dy);
}