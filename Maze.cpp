#include "Maze.h"

Maze::Maze()
{
	w = 25;
	h = 25;

	start = make_pair(0, 0);
	end = make_pair(w - 1, w - 1);

	graph.resize(w);
	for (int i = 0; i < w; i++)
	{
		graph[i].resize(h);
	}

	for (auto i : graph) 
	{
		for (auto j : i)
		{
			j.tile = 1;
		}
	}

	for (int i = 0; i < h; i++)
	{
		graph[0][i].tile = 1;
	}

	graph[start.first][start.second].tile = 2;
	graph[end.first][end.second].tile = 2;
}

void Maze::addVx(int x, int y, int val)
{

}

void Maze::randomize()
{
	node* current = NULL;
	node* choosen = NULL;
	//initialize random seed
	srand(time(NULL));
	//intitialize a stack
	stack<node*> s;
	//push starting node onto stack and mark as visited
	s.push(sNode);
	sNode->visited = true;
	//while the stack is not empty
	while (!s.empty())
	{
		//pop node from stack and make it current node
		current = s.top();
		s.pop();
		//if the node has any unvisited neighbors
		for (int i = 0; i < current->adj.size(); i++)
		{
			if (!current->adj[i]->visited)
			{
				//push current node onto stack
				s.push(current);
				//choose a random unvisited neighbor
				choosen = current->adj[rand() % current->adj.size()];
				//connect the path between current node and choosen neighbor
				addEdge(choosen, current);
				//mark chosen node as visited and push it onto stack
				choosen->visited = true;
				s.push(choosen);
				//get out of for loop
				break;
			}
		}
	}
}

int Maze::getVertex(int x, int y)
{
	return 0;
}

void Maze::addEdge(node* from, node* to)
{

}

void Maze::GenerateMaze(int width, int height)
{
	
}

int Maze::Djikstra()
{
	return 0;
}

int Maze::DFS()
{
	return 0;
}