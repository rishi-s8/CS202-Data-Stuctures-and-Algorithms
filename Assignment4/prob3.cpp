/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * prob1.cpp - Solution to Problem-3
  * Argument: Dictionary File
  * Input:
  *         start - Start Word
  *         end - Target Word
*/
#include <iostream>
#include <fstream>
#include <ctype.h>
#include "helper.hpp"
#include "AVL.hpp"

char increment(char ch)
{
  if(isupper(ch))
    ch = (ch-'A'+1)%26 + 'A';
  else
    ch = (ch-'a'+1)%26 + 'a';
  return ch;
}

void BFS(string start, string end, int count, string dict[], AVL<string, int> &dictionary)
{
  int infinite = 1000000007;
  List<int> Queue;
  bool visited[count+1];
  int distance[count+1], parent[count+1];
  for(int i=0; i<=count; ++i) visited[i]=false, distance[i] = -1, parent[i]=-1;
  int startIndex = dictionary.get(start);
  Queue.push(startIndex);
  distance[startIndex] = 0;
  visited[startIndex] = true;
  while(!Queue.isEmpty())
  {
    int curIndex = Queue.front();
    Queue.pop();
    string current = dict[curIndex];
    for(int i=0; i<current.size(); ++i)
    {
      for(int j=1; j<26; ++j)
      {
        current[i] = increment(current[i]);
        if(dictionary.has(current))
        {
          int newIndex = dictionary.get(current);
          if(!visited[newIndex])
          {
            visited[newIndex] = true;
            Queue.push(newIndex);
            distance[newIndex] = 1 + distance[curIndex];
            parent[newIndex] = curIndex;
          }
        }
      }
      current[i] = increment(current[i]);
    }
  }
  int i = dictionary.get(end), ans = distance[i] + 1, j=ans-1;
  int path[ans];
  while(i!=-1)
  {
    path[j--] = i;
    i = parent[i];
  }
  cout << endl;
  cout << "The path is:\n";
  for(i=0; i<ans; ++i)
    cout << dict[path[i]] << endl;
  cout << "The Length is: " << ans << endl ;
}


int main(int argc, char* argv[])
{
  if(argc!=2)
  {
    cerr << "Wrong arguments" << endl;
    cout << "USAGE: ./prob3 <dictionaryFile>" << endl;
    return -1;
  }
  fstream d;
  d.open(argv[1], ios::in);
  string start, end;
  cout << "The start word is: "; cin >> start;
  cout << "The target word is: "; cin >> end;
  string dict[10000];
  int count = 0;
  AVL<string,int> dictionary;
  while(d.good())
  {
    ++count;
    d >> dict[count];
    if(!dict[count].size()) break;
    dictionary.put(dict[count], count);
  }
  if(!dictionary.has(start))
  {
    dictionary.put(start,0);
    dict[0] = start;
  }

  BFS(start, end, count, dict, dictionary);
}
