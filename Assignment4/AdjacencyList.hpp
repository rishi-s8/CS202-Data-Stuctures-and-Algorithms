/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * AdjacencyList.hpp
*/


#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1

#include "GraphAdjacencyBase.hpp"
#include "helper.hpp"
#include "seqLinearList.hpp"
/*
 * 	Class AdjacencyList
 *	Can be used to represent a Graph using adjacency-list.
 */
class AdjacencyList : public GraphAdjacencyBase {
	int size, verts;
	LinearList< int > incoming;
	public:
	List<int> *graph;
	AdjacencyList(int vertices)
	{
		incoming.initialize(vertices);
		graph = new List<int>[vertices];
		verts = vertices;
		size = 0;
	}
	~AdjacencyList()
	{
		for(int i=0; i<verts; ++i)
		{
			while(!graph[i].isEmpty())
				graph[i].pop();
		}
		delete graph;
	}

	/*
	 * Function: edgeExists
	 * Returns true if an edge exists between vertices i and j, false otherwise.
	 */
  virtual bool edgeExists(int i, int j)
	{
		node<int> *temp = graph[i].head;
		while(temp!=nullptr)
		{
			if(temp->adj == j) return true;
			temp = temp->next;
		}
		return false;
	}
	/*
	 * Function: vertices
	 * Returns the number of vertices in the adjacency structure.
	 */
  virtual int vertices()
	{
		return verts;
	}
	/*
	 * Function: edges
	 * Returns the number of edges in the adjacency structure.
	 */
  virtual int edges()
	{
		return size;
	}
	/*
	 * Function add:
	 * Adds an edge between vertices i and j
	 */
  virtual void add(int i, int j)
	{
		if(!edgeExists(i,j))
		{
			graph[i].push(j);
			++size;
			incoming[j]++;
		}

	}
	virtual void addWeightedEdge(int i, int j, int w)
	{
		if(!edgeExists(i,j))
		{
			graph[i].push(j, w);
			++size;
			incoming[j]++;
		}
	}
	/*
	 * Function: remove
	 * Deleted the edge between vertices i and j
	 */
  virtual void remove(int i, int j)
	{
		if(edgeExists(i,j))
		{
			graph[i].remove(j);
			size--;
			incoming[j]--;
		}
	}
	/*
	 * Function: degree
	 * Returns the degree of the vertex i
	 */
  virtual int degree(int i)
	{
		return graph[i].getSize() + incoming[i];
	}

	virtual int getWeight(int i, int j)
	{
		node<int> * temp = graph[i].head;
		while(temp!=nullptr)
		{
			if(temp->adj == j) return temp->weight;
			temp = temp->next;
		}
		return inf;
	}
};
#endif /* ifndef ADJACENCY_LIST */
