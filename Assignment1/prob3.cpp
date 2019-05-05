/*
 * CS202 LAB ASSIGNMENT 1
 * Author: Rishi Sharma (B17138)
 * Problem 3
 */

#include "seqLinearList.hpp"
#include "sorting.hpp"

template <class Item>
void swapHalves(LinearList<Item> &l, int start, int mid, int end)
{
  for(int i=0; i<=mid; ++i)
    swap(l[i], l[i+mid+1]);
}

template <class Item>
void arrangeList(LinearList<Item> &l, int start, int mid, int end)
{
  Item sum1=0, sum2=0;
  for(int i=0; i<=mid; ++i)
    sum1 += l[i];
  for(int i=mid+1; i<=end; ++i)
    sum2+=l[i];
  if(sum1>sum2)
    swapHalves(l, start, mid, end);
}

template <class Item>
Item solve(LinearList<Item> &l, int start, int mid, int end, int k)
{
  int i=mid, j=mid+1;
  while(k-- && i>=start && j<=end && l[i]>l[j])
    swap(l[i--], l[j++]);
  arrangeList(l, 0, mid, end);
  Item sum = 0;
  for(int i=mid+1; i<=end; ++i)
    sum+=l[i];
  return sum;
}

template <class Item>
void printList(LinearList<Item> &l, int start, int mid, int end)
{
  for(int i=mid+1; i<=end; ++i)
    cout << l[i] << " ";
  cout << endl;
  for(int i=start; i<=mid; ++i)
    cout << l[i] << " ";
  cout << endl;
}

int main()
{
        int n, k;
        cin >> n >> k;
        LinearList<long long> l(n);
        for(int i=0; i<n; ++i)
                cin >> l[i];
        Sort<long long> s;
        int mid = n/2 - 1;
        s.mergeSort(l, 0, mid);
        s.mergeSort(l, mid+1, n-1);
        LinearList<long long> r(n);
        for(int i=0; i<n; ++i) r[i]=l[i];
        long long sum1 = solve(l, 0, mid, n-1, k);
        swapHalves(r,0,mid,n-1);
        long long sum2 = solve(r, 0, mid, n-1, k);
        if(sum1>sum2)
          printList(l,0,mid,n-1);
        else
          printList(r,0,mid,n-1);
}
