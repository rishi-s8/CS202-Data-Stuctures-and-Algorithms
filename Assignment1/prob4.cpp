/*
 * CS202 LAB ASSIGNMENT 1
 * Author: Rishi Sharma (B17138)
 * Problem 4
 */
#include "seqLinearList.hpp"
#include "sorting.hpp"
#define maxStudents 1000000

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int Max(int x, int y)
{
  if(x<y) return y;
  else return x;
}

int Min(int x, int y)
{
  if(x>y) return y;
  else return x;
}

bool isPrime(int x)
{
  for(int y=2; y*y<=x; ++y)
    if(x%y==0) return false;
  return true;
}

bool isFriend(int x, int y)
{
  int g = gcd(Max(x,y),Min(x,y));
  if(g==1)
  {
    return false;
  }
  else if(isPrime(g))
  {
    return false;
  }
  return true;
}

struct node
{
  int roll;
  double height;
  node* next;
};

class LinkedList
{
private:
  node* head;
  int len;
  node* createNode(int roll, double height)
  {
    node* temp = new node;
    temp->next = NULL;
    temp->roll = roll;
    temp->height = height;
    return temp;
  }
public:
  LinkedList()
  {
    head=NULL;
    len=0;
  }
  void insert(int roll, double height)
  {
    node* temp = createNode(roll, height);
    if(len==0)
    {
      head = temp;
      ++len;
      return;
    }
    else
    {
      node* current = head;
      while(current->next!=NULL && (!isFriend(roll, current->roll)))
        current=current->next;
      temp->next=current->next;
      current->next=temp;
      ++len;
    }
  }
  void printList()
  {
    if(head==NULL)
      return;
    node *temp = head;
    while(temp!=NULL)
    {
      cout << temp->roll << " ";
      temp=temp->next;
    }
    cout << endl;
  }
  int calculateSwaps()
  {
    if(len<=1)
      return 0;
    int ans = 0;
    node* init = head;
    while(init!=NULL)
    {
      node* minAddress = init, *current=init->next;
      while(current!=NULL)
      {
        if(current->height < minAddress->height)
          minAddress = current;
        current=current->next;
      }
      if(minAddress!=init)
      {
        Swap(minAddress->roll, init->roll);
        Swap(minAddress->height, init->height);
        ans++;
      }
      init=init->next;
    }
    return ans;
  }
};

int main()
{
  int n, m, k;
  cin >> n >> m >> k;
  LinearList<double> heights(maxStudents+1);
  for(int i=0; i<k; ++i)
  {
    int x; double y;
    cin >> x >> y;
    heights[x]=y;
  }
  LinearList<LinkedList> l(27);
  char ch; int roll;
  for(int i=0; i<k; ++i)
  {
    scanf("%c", &ch);
    scanf("%c%d", &ch, &roll);
    ch-='A';
    l[(int)ch].insert(roll, heights[roll]);
  }
  double swaps = 0;
  for(int i=0; i<26; ++i)
    swaps += (l[i].calculateSwaps());
  cout << swaps/2 << endl;

}
