#include "Maze.h"

Maze::Maze()
{
	width = 9;
	height = 9;
	//creates default maze as a line
	theMaze[1][0] = 2;
	theMaze[1][8] = 2;
	for (int i = 1; i < 8; i++)
	{
		theMaze[1][i] = 1;
	}
}

void Maze::GenerateMaze(int width, int height)
{

}

int Maze::Djikstra()
{

}

int Maze::DFS()
{

}