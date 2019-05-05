/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * AdjacencyMatrix.hpp
*/
#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1

#include "GraphAdjacencyBase.hpp"
#include "seqLinearList.hpp"

/*
 * 	Class AdjacencyMatrix
 *	Can be used to represent a Graph using adjacency-matrix.
 */
class AdjacencyMatrix : public GraphAdjacencyBase {
		int size, verts;

	public:
		LinearList< int > *graph;
		AdjacencyMatrix(int vertices)
		{
			verts = vertices;
			graph = new LinearList<int>[vertices];
			for(int i=0; i<vertices; ++i)
				graph[i].initialize(vertices);
			size = 0;
			// (graph[1])[2] = 3;
			// (graph[2])[3] = 5;
			// for(int i=0; i<vertices; ++i)
			// {
			// 	for(int j=0; j<vertices; ++j)
			// 		cout << (graph[i])[j] << " ";
			// 	cout << endl;
			// }
		}
		~AdjacencyMatrix()
		{
		}
		/*
		 * Function: edgeExists
		 * Returns true if an edge exists between vertices i and j, false otherwise.
		 */
	  virtual bool edgeExists(int i, int j)
		{
			if(graph[i][j]) return true;
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
			if(!graph[i][j])
			{
				size++;
			}
			graph[i][j]=1;
		}
		virtual void addWeightedEdge(int i, int j, int w)
		{
			if(!graph[i][j])
			{
				size++;
			}
			graph[i][j] = w;
		}
		/*
		 * Function: remove
		 * Deleted the edge between vertices i and j
		 */
	  virtual void remove(int i, int j)
		{
			if(graph[i][j])
			{
				size--;
			}
			graph[i][j]=0;
		}
		/*
		 * Function: degree
		 * Returns the degree of the vertex i
		 */
	  virtual int degree(int i)
		{
			int deg = 0;
			for(int j=0; j<verts; ++i)
			{
				if(graph[i][j]) deg++;
				if(graph[j][i]) deg++;
			}
			return deg;
		}

		virtual int getWeight(int i, int j)
		{
			return graph[i][j];
		}
};

#endif /* ifndef ADJACENCY_MATRIX */
