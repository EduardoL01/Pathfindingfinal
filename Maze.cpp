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

}

int Maze::getVertex(int x, int y)
{
	return 0;
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