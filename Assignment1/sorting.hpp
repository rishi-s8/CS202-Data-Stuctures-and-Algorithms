#ifndef SORTING_HPP
#define SORTING_HPP
#include <iostream>
#include "seqLinearList.hpp"
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*x+2

template<class Item>
class Sort{
	private:
		void merge(LinearList<Item>& A, int low, int high);
		void buildHeap(LinearList<Item>& A, int length);
		void heapify(LinearList<Item>& A, int length, int x);
	public:
		void insertionSort(LinearList<Item>& A, int low, int high);
		void bubbleSort(LinearList<Item>& A, int low, int high);
	 	void rankSort(LinearList<Item>& A, int low, int high);
    void selectionSort(LinearList<Item>& A, int low, int high);
		void mergeSort(LinearList<Item>& A, int low, int high);
    void quickSort(LinearList<Item>& A, int low, int high);
		void heapSort(LinearList<Item>& A, int length);
};
#include "sorting.cpp"
#endif
