/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * prob1.cpp - Solution to Problem-4
  * Input:
  *         n - Number of vertices
  *         m - Number of Edges
  *           m edge descriptions
*/
#include <iostream>
#include "DirectedGraph.hpp"
#include "helper.hpp"



int n;
void dijkstra(DirectedGraph &g, int source, int destination)
{
  int distance[n+1], parent[n+1];
  bool visited[n+1];
  for(int i=1; i<=n; ++i)
    distance[i]=inf, visited[i] = false, parent[i] = -1;
  distance[source] = 0;
  priorityQueue q(n*n);
  element temp = {source, 0};
  q.insert(temp);
  while(!q.isEmpty())
  {
    temp = q.extractMin();
    if(visited[temp.vertex]) continue;
    visited[temp.vertex] = true;
    for(int i = 1; i<=n; ++i)
    {
      if(g.edgeExists(temp.vertex, i))
      {
        int w = g.getWeight(temp.vertex, i);
        if(distance[i] > distance[temp.vertex]+w)
        {
          distance[i] = distance[temp.vertex]+w;
          parent[i] = temp.vertex;
          element p = {i, distance[i]};
          q.insert(p);
        }

      }
    }
  }

  int cur = destination;
  int path[n+1], counter = 0;
  while(cur != -1)
  {
    path[counter++]=cur;
    cur = parent[cur];
  }
  cout << "The path is: ";
  for(int i = counter-1; i>0; --i)
    cout << path[i] << "− > ";
  cout << path[0] << endl;
  cout << "Total Time is: " << distance[destination] << endl;
}


int main()
{
  int m;
  cin >> n >> m;
  DirectedGraph g(n+1, 'l');
  int x, y, w;
  while(m--)
  {
    cin >> x >> y >> w;
    g.addWeightedEdge(x,y,w);
  }
  dijkstra(g,1,n);
}
