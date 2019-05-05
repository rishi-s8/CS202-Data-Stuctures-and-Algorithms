template<class Item>
void Sort<Item>::insertionSort(LinearList<Item>& A, int low, int high)
{
        for(int i=low+1; i<=high; ++i)
        {
                Item val = A[i];
                int j=i-1;
                while(j>=low && A[j]>val)
                {
                        A[j+1]=A[j];
                        j--;
                }
                A[j+1]=val;
        }
}

template<class Item>
void Sort<Item>::bubbleSort(LinearList<Item>& A, int low, int high)
{
        for(int i=low; i<=high; ++i)
                for(int j=low; j<high-i; ++j)
                        if(A[j]>A[j+1]) Swap(A[j], A[j+1]);
}

template<class Item>
void Sort<Item>::rankSort(LinearList<Item>& A, int low, int high)
{
        int length = high-low+1;
        LinearList<Item> ranks(length);
        for(int i=0; i<length; ++i)
                ranks[i]=0;
        for(int i=low+1; i<=high; ++i)
        {
                for(int j=low; j<i; ++j)
                {
                        if(A[j]>A[i]) ranks[j-low]++;
                        else ranks[i-low]++;
                }
        }
        LinearList<Item> sortedRanks(length);
        for(int i=0; i<length; ++i)
                sortedRanks[ranks[i]]= A[i];
        for(int i=low; i<=high; ++i)
                A[i]=sortedRanks[i-low];
}

template<class Item>
void Sort<Item>::selectionSort(LinearList<Item>& A, int low, int high)
{
        for(int i=low; i<=high; ++i)
        {
                int minIndex = i;
                for(int j=i+1; j<=high; ++j)
                        if(A[j]<A[minIndex]) minIndex=j;
                Swap(A[minIndex], A[i]);
        }
}

template<class Item>
void Sort<Item>::mergeSort(LinearList<Item>& A, int low, int high)
{
        if(low>=high) return;
        int mid = (low+high)/2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, low, high);
}

template<class Item>
void Sort<Item>::merge(LinearList<Item>& A, int low, int high)
{
        int mid = (low+high)/2;
        int lowA = low, highA = mid, lowB=mid+1, highB=high;
        LinearList<Item> Z(high-low+1);
        int i=0;
        while(lowA<=highA && lowB<=highB)
                if(A[lowA]<A[lowB]) Z[i++]=A[lowA++];
                else Z[i++]=A[lowB++];
        while(lowA<=highA)
                Z[i++]=A[lowA++];
        while(lowB<=highB)
                Z[i++]=A[lowB++];
        i=0;
        for(int j=low; j<=high; ++i, ++j)
                A[j]=Z[i];
}

template<class Item>
void Sort<Item>::heapSort(LinearList<Item>& A, int length)
{
        buildHeap(A, length);
        for(int i=length-1; i>0; --i)
        {
                swap(A[i], A[0]);
                heapify(A, i, 0);
        }
}

template<class Item>
void Sort<Item>::buildHeap(LinearList<Item>& A, int length)
{
        int mid = length/2;
        for(int i = mid; i>=0; --i)
                heapify(A, length, i);
}

template<class Item>
void Sort<Item>::heapify(LinearList<Item>& A, int length, int x)
{
        if(LEFT(x)>=length)
                return;
        int max=LEFT(x);
        if(RIGHT(x)<length && A[LEFT(x)] < A[RIGHT(x)]) max = RIGHT(x);
        if(A[x]<A[max])
        {
                Swap(A[x], A[max]);
                heapify(A, length, max);
        }
}



template<class Item>
void Sort<Item>::quickSort(LinearList<Item>& A, int low, int high)
{
        int i=low, j=low;
        while(j<high)
        {
                if(A[j]<=A[high]) Swap(A[i++], A[j]);
                j++;
        }
        Swap(A[i], A[high]);
        if(i-1>low)
                quickSort(A, low, i-1);
        if(i+1 < high)
                quickSort(A, i+1, high);
}
