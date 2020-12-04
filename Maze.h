#pragma once
#include "olcPixelGameEngine.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Maze																			
{

	struct node {																	//each nodes need to store its neighbors and whether is a flag or wall
		int tile = 1;																// 0 - wall, 1 - empty, 2 - flag
		vector<node*> adj;
	};

	
	vector<vector<node>> graph;														//stores our out-degree edges, each non-border node connects to its adj neighbor
	int w = 0;
	int h = 0;
	pair<int,int> start = make_pair(0,0);
	pair<int,int> end = make_pair(0, 0);

	Maze();
	void randomize();
	void addVx(int x, int y, int val);
	int getVertex(int x, int y);
	void GenerateMaze(int width, int height);
	int Djikstra();
	int DFS();
};