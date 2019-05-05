/*
  * CS202 Assignment 4
  * Author: Rishi Sharma (B17138)
  * helper.hpp
	*	Contains:
	*					PAIR
	*					node
	*					List
	*					element
	*					priorityQueue
*/
#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include "seqLinearList.hpp"
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*x+2
#define PARENT(x) x/2
using namespace std;

int inf = 1000000007;

template <class T1, class T2>
struct PAIR
{
	T1 first;
	T2 second;
};


template <typename Item>
struct node
{
	Item adj;
	int weight;
	node* next;
};

template <typename Item>
class List
{
	int size;
public:
  node<Item> *head, *tail;
	List()
	{
		head=tail=nullptr;
		size = 0;
	}
	node<Item>* createNode(Item adj, int w)
	{
		node<Item> *temp = new node<Item>;
		temp->adj = adj;
		temp->next=NULL;
		temp->weight = w;
		return temp;
	}

	bool isEmpty()
	{
		if(head==nullptr)
			return true;
		else
			return false;
	}

	void push(Item adj, int w = 1)
	{
		node<Item>* temp = createNode(adj, w);
		if(head==nullptr)
		{
			head=tail=temp;
		}
		else
		{
			tail->next=temp;
			tail=temp;
		}
		++size;
	}

	void remove(Item adj)
	{
		if(head->adj == adj)
		{
			node<Item>* toBeDeleted = head;
			head = head->next;
			if(head==nullptr) tail=nullptr;
			delete toBeDeleted;
			--size;
			return;
		}
		node<Item> *temp = head->next, *parent = head;
		while(temp!=nullptr)
		{
			if(temp->adj == adj)
			{
				parent->next = temp->next;
				delete temp;
				--size;
				return;
			}
			parent = temp;
			temp = temp->next;
		}
	}

	Item front()
	{
			return head->adj;
	}

	void pop()
	{
		if(isEmpty())
			return;
		node<Item> *temp = head;
		if(head->next==nullptr)
		{
			head=tail=nullptr;
		}
		else
		{
			head=head->next;
		}
		--size;
		delete temp;
	}
	void printList()
	{
		node<Item> * temp = head;
		while(temp!=nullptr)
		{
			cout << temp->adj << " ";
			temp=temp->next;
		}
		cout << endl;
	}
	int getSize()
	{
		return size;
	}
};



struct element
{
	int vertex;
	int weight;
};


class priorityQueue
{
	element *list;
	int maxSize, length;

public:
	priorityQueue(int maxSize)
	{
		this->maxSize = maxSize;
		list = new element[maxSize+2];
		length = 0;
	}

	void insert(element x)
	{
		++length;
		list[length] = x;
		int i;
		for(i=length; i>1 && x.weight < list[PARENT(i)].weight; i=PARENT(i))
			list[i] = list[PARENT(i)];
		list[i] = x;
	}

	element extractMin()
	{
		element temp = list[1];
		list[1] = list[length--];
		heapify(1);
		return temp;
	}

	void heapify(int x)
	{
	        if(LEFT(x)>=length)
	                return;
	        int min=LEFT(x);
	        if(RIGHT(x)<length && list[RIGHT(x)].weight < list[LEFT(x)].weight) min = RIGHT(x);
	        if(list[x].weight>list[min].weight)
	        {
	                Swap(list[x], list[min]);
	                heapify(min);
	        }
	}

	bool isEmpty()
	{
		if(length) return false;
		return true;
	}
};

#endif
