/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * DirectedGraph.hpp
*/
#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1

#include "AbstractGraph.hpp"

/*
* A class to represent a directed graph.
*/
class DirectedGraph : AbstractGraph {

	GraphAdjacencyBase *base;
	char rep;


	public:
	/*
	 * Constructor: DirectedGraph
	 *
	 * Parameters: mode
	 * Used to decide which representation to use
	 * 'm' for AdjacencyMatrix
	 * 'l' for AdjacencyList
	 */
	DirectedGraph(int numVertices, char rep)
	{
		this->rep = rep;
		if(rep == 'm')
			base = new AdjacencyMatrix(numVertices);
		else
			base = new AdjacencyList(numVertices);
	}
	/*
	 * Destructor
	 */
		//~DirectedGraph();
  /*
   * Function: edgeExists
   * Returns true if an edge exists between vertices i and j, false otherwise.
   */
  virtual bool edgeExists(int i, int j)
	{
		return base->edgeExists(i,j);
	}
  /*
   * Function: edges
   * Returns the number of edges in the adjacency structure.
   */
  virtual int edges()
	{
		return base->edges();
	}
  /*
   * Function: vertices
   * Returns the number of vertices in the adjacency structure.
   */
  virtual int vertices()
	{
		return base->vertices();
	}
  /*
   * Function add:
   * Adds an edge between vertices i and j
   */
  virtual void add(int i, int j)
	{
		base->add(i,j);
	}
	virtual void addWeightedEdge (int i, int j, int w)
	{
		base->addWeightedEdge(i,j, w);
	}
  /*
   * Function: remove
   * Deleted the edge between vertices i and j
   */
  virtual void remove(int i, int j)
	{
		base->remove(i,j);
	}
  /*
   * Function dfs:
   * Does a depth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  virtual void dfs(void (*work)(int&))
	{
		int verts = vertices();
		LinearList<bool> visited(verts);
		for(int i=0; i<verts; ++i)
			visited[i] = false;
		int component = 0;
		if(rep=='m')
		{
			for(int i=0; i<verts; ++i)
				if(!visited[i])
				{
					cout << "Connected Component " << component++ << ": ";
					dfsHelperM(work, i, visited);
					cout << endl;
				}
		}
		else
		{
			for(int i=0; i<verts; ++i)
			{
				for(int i=0; i<verts; ++i)
					if(!visited[i])
					{
						cout << "Connected Component " << component++ << ": ";
						dfsHelperL(work, i, visited);
						cout << endl;
					}
			}
		}
	}

	virtual void dfsHelperM(void (*work)(int&), int v, LinearList<bool> &visited)
	{
		visited[v] = true;
		(*work)(v);
		int verts = vertices();
		for(int i=0; i<verts; ++i)
			if(!visited[i] && ((AdjacencyMatrix *)base)->graph[v][i]) dfsHelperM(work, i, visited);
	}

	virtual void dfsHelperL(void (*work)(int&), int v, LinearList<bool> &visited)
	{
		visited[v] = true;
		(*work)(v);
		node<int> *temp = ((AdjacencyList *)base)->graph[v].head;
		while(temp!=nullptr)
		{
			if(!visited[temp->adj]) dfsHelperL(work, temp->adj, visited);
			temp = temp->next;
		}
	}
  /*
   * Function bfs:
   * Does a breadth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  virtual void bfs(void (*work)(int&))
	{
		int verts = vertices();
		LinearList<bool> visited(verts);
		for(int i=0; i<verts; ++i)
			visited[i] = false;
		for(int i=0; i<verts; ++i)
			if(!visited[i]) bfsHelper(work, i, visited);
	}

	virtual void bfsHelper(void (*work)(int&), int v, LinearList<bool> &visited)
	{
		int verts = vertices();
		List<int> Queue;
		Queue.push(v);
		visited[v] = true;
		while(!Queue.isEmpty())
		{
				int x = Queue.front();
				Queue.pop();
				(*work)(x);
				if(rep=='m')
				{
					for(int i=0; i<verts; ++i)
					{
						if(!visited[i] && ((AdjacencyMatrix *)base)->graph[x][i])
						{
							visited[i] = true;
							Queue.push(i);
						}
					}
				}
				else
				{
					node<int> *temp = ((AdjacencyList *)base)->graph[v].head;
					while(temp!=nullptr)
					{
						if(!visited[temp->adj])
						{
							visited[temp->adj] = true;
							Queue.push(temp->adj);
						}
						temp = temp->next;
					}
				}
		}
	}

	virtual int getWeight(int i, int j)
	{
		return base->getWeight(i,j);
	}

};

#endif /* ifndef DIRECTED_GRAPH */
