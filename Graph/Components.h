#pragma once
#include <iostream>
#include <cassert>
#include "SparseGraph.h"
#include "DenseGraph.h"
using namespace std;


template <typename Graph>
class Component
{
private:
	Graph& G;
	bool* visited;
	int ccount;
	int* id;

	void dfs(int v)
	{
		visited[v] = true;
		id[v] = ccount;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next())
			if (!visited[i])
				dfs(i);
	}

public:
	Component(Graph& graph) : G(graph)
	{
		visited = new bool[G.V()];
		id = new int[G.V()];
		ccount = 0;
		for (int i = 0; i < G.V(); i++)
		{
			visited[i] = false;
			id[i] = -1;
		}

		for (int i = 0; i < G.V(); i++)
		{
			if (!visited[i])
			{
				dfs(i);
				ccount++;
			}
		}
	}

	~Component()
	{
		delete[] visited;
		delete[] id;
	}

	int count() const
	{
		return ccount;
	}

	bool isConnected(int v, int w) { return id[v] == id[w];}

};