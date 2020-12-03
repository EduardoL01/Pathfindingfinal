#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
using namespace std;

class Maze
{
	//Maze where 0 represents a wall, 1 represents a path, 2 represents the start/end
	vector<vector<int>> theMaze;
	int width = 0;
	int height = 0;

public:
	Maze();
	void setVertex(int x, int y, int val);
	int getVertex(int x, int y);
	void GenerateMaze(int width, int height);
	int Djikstra();
	int DFS();
};