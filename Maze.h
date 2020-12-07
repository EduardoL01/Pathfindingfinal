#pragma once
#include "olcPixelGameEngine.h"
#include <vector>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

struct Maze																			
{

	struct node {																	//each nodes need to store its neighbors and whether is a flag or wall
		int tile = 1;																// 0 - wall, 1 - empty, 2 - flag
		vector<node*> neighbors;
		vector<node*> adj;
		bool visited = false;
		pair<int, int> loc;
		vector<node*> returnAdj()
		{
			vector<node*> nVisit;
			for (auto n : adj)
			{
				if (!n->visited)
				{
					nVisit.push_back(n);
				}
			}
			return nVisit;
		}
		pair<bool,bool> returnPaths()
		{
			pair<bool, bool> paths = make_pair(0,0);
			for (auto n : neighbors)
			{
				if ( (loc.second == n->loc.second) && (loc.first < n->loc.first))
				{
					paths.first = 1;
				}

				if ( (loc.first == n->loc.first) && (loc.second < n->loc.second))
				{
					paths.second = 1;
				}

			}
			return paths;
		}
 	};

	
	vector<vector<node>> graph;														//stores our out-degree edges, each non-border node connects to its adj neighbor
	int w = 0;
	int h = 0;
	node* sNode;
	node* eNode;
	pair<int,int> start = make_pair(0,0);
	pair<int,int> end = make_pair(0, 0);

	Maze();
	void randomize();
	void addVx(int x, int y, int val);
	int getVertex(int x, int y);
	void addEdge(node* from, node* to);
	void GenerateMaze(int width, int height);
	int Djikstra();
	int DFS();
};