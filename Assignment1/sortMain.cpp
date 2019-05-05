/*
 * CS202 LAB ASSIGNMENT 1
 * Author: Rishi Sharma (B17138)
 * Sorting Algorithms Test Run
 */

#include "seqLinearList.hpp"
#include "sorting.hpp"

int main()
{
        int n;
        cin >> n;
        LinearList<int> l(n), r(n);
        for(int i=0; i<n; ++i)
                cin >> r[i];
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        Sort<int> s;
        cout << "insertionSort: " << endl;
        s.insertionSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "bubbleSort: " << endl;
        s.bubbleSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "rankSort: " << endl;
        s.rankSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "selectionSort: " << endl;
        s.selectionSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "mergeSort: " << endl;
        s.mergeSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "quickSort: " << endl;
        s.quickSort(l, 0, n-1);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
        for(int i=0; i<n; ++i)
                l[i]=r[i];
        cout << "heapSort: " << endl;
        s.heapSort(l, n);
        for(int i=0; i<n; ++i)
                cout << l[i] << " ";
        cout << endl;
}
