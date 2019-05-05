/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * prob1.cpp - Solution to Problem-2
  * Input:
  *         n - Number of vertices
  *         z - Number of edges
  *           z edge descriptions
*/
#include "UndirectedGraph.hpp"
#include <iostream>
using namespace std;

void print(int &x)
{
  cout << x << " ";
}

int main()
{

  int n; cin >> n;
  UndirectedGraph g(n, 'l');
  int x, y;
  int z;
  cin >> z;
  while(z--)
  {
    cin >> x >> y;
    g.add(x,y);
  }
  g.dfs(&print);
  cout << endl;
}
