/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * prob1.cpp - Solution to Problem-1
  * Input File: input1.in
  * Output File: output1.out
*/
#include <iostream>
#include <fstream>
#include "helper.hpp"

const int maxCol = 1000, maxRow = 1000;
int n=0, m=0;
char graph[maxRow][maxCol];
int ans[maxRow][maxCol];
int movex[] = {0,0,1,-1};
int movey[] = {1,-1,0,0};

bool inBounds(int x, int y)
{
  return ((x>=0 && x<n) && (y>=0 && y<m));
}

void floodFill()
{
  List< PAIR<int,int> > Queue;
  for(int i=0; i<n; ++i)
    for(int j=0; j<m; ++j)
      if(graph[i][j]=='G')
      {
        PAIR<int,int> temp = {i,j};
        Queue.push(temp);
        ans[i][j] = 0;
        graph[i][j] = 'X';
      }
  while(!Queue.isEmpty())
  {
    PAIR<int,int> current = Queue.front();
    Queue.pop();
    for(int i=0; i<4; ++i)
    {
      int x =  current.first + movex[i], y = current.second + movey[i];
      if(inBounds(x,y))
        if((graph[x][y]) != 'X')
        {
          if(graph[x][y]=='O')
          {
            ans[x][y] = ans[current.first][current.second]+1;
            PAIR<int,int> z = {x,y};
            Queue.push(z);
          }
          else if(graph[x][y]=='W')
            ans[x][y]=-1;
          graph[x][y] = 'X';
        }
    }
  }
}


void extractLine(string line)
{
  for(int i=0; i<line.size(); i+=2)
    graph[n][i/2] = line[i];
  if(line.size())
    ++n;
}



int main()
{
    fstream inf, of;
    inf.open("input1.in", ios::in);
    of.open("output1.out", ios::out);
    if(!inf.is_open() || !of.is_open())
    {
      cerr << "I/O Error" << endl;
      return -1;
    }
    string line;
    getline(inf, line);
    extractLine(line);
    m = (line.size()+1)/2;
    while(inf.good())
    {
      getline(inf, line);
      extractLine(line);
    }
    floodFill();
    for(int i=0; i<n; ++i)
    {
      for(int j=0; j<m; ++j)
        of << ans[i][j] << " ";
      of << endl;
    }
    of.close();
    inf.close();

}
