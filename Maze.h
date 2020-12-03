#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
using namespace std;

class Maze
{
	struct Node
	{
		bool isStart = false;
		bool isEnd = false;
		bool isObj = false;
		vector<Node*> adjacent;

		Node();
	};

	Node theMaze[500][500];

public:
	Maze();
	int Djikstra();
	int DFS();
};