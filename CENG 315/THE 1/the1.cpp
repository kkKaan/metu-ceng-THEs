#include "the1.h"
#include <climits>
#include <iostream>

using namespace std;

int isTheFirstBigger(int a, int b, long &comparison)
{
    comparison++;
    if (a > b)
        return 1;
    return 0;
}

int min(int a, int b)
{
    if(b < a) return b;
    return a;
}

void swapper(int &a, int &b, long &swap)
{
    swap++;
    int temp = a;
    a = b;
    b = temp;
}

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int i = 1;
    while (i < size)
    {
        int x = arr[i];
        int j = i - 1;
        
        while((j>=0) && isTheFirstBigger(arr[j], x, comparison))
        {
            arr[j+1] = arr[j];
            j = j-1;
            swap++;
        }
        arr[j+1] = x;
        i = i+1; 
    }
}

// checks if the heap is ordered or not
int isOrdered(int *heap, int K)
{
    for (int i = 0; (2*i + 2) < K; i++)
    {
        if ((heap[i] > heap[2*i + 1]) || heap[i] > heap[2*i + 2])
            return 0;
    }
    if(heap[(K-2)/2] > (heap[K-1]))
        return 0;
    return 1;
}

// sligtly modified heapify function
void heapify(int *heap, int K, long& comparison, long& swap)
{
    while(!(isOrdered(heap, K)))
    {
        int parent = 0;
        while((2*parent + 2) < K)
        {
            int left = 2*parent + 1;
            int right = 2*parent + 2;
            
            int minEle = min(heap[left], heap[right]); 

            if((heap[left] != INT_MAX) && (heap[right] != INT_MAX)) {comparison++;}
            
            int minIndex = minEle == heap[left] ? left : right;

            if(isTheFirstBigger(heap[parent], minEle, comparison))
            {
                int temp = heap[parent];
                heap[parent] = minEle;
                heap[minIndex] = temp;
                swap++;
            }
            parent++;
        }

        if((2*parent + 1) < K)
        {
            if(isTheFirstBigger(heap[parent], heap[2*parent + 1], comparison))
            {
                int temp = heap[parent];
                heap[parent] = heap[2*parent + 1];
                heap[2*parent + 1] = temp;
                swap++;
            }
        }
    }
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap)
{
    int number_of_calls = 1;
	
	if(size < K){insertionSort(arr, comparison, swap, size); return number_of_calls;}
    else
    {
        for(int i = 0; i < K; i++)
        {
            number_of_calls += kWayMergeSortWithHeap(arr + i*size/K, K, size/K, comparison, swap);
        }

        int *heap = new int(K);
        int *newArr = new int(size);

        for(int i = 0; i < K; i++)
        {
            if(size/K == 1)
            {
                heap[i] = arr[i*K];
            }
            else
            {
                heap[i] = arr[i*size/K];
            }
        }

        heapify(heap, K, comparison, swap);

        // add min of heap to new array and swap with the next element of the subarray from which the min was taken
        // heapify the heap again
        // repeat until all elements are added to the new array

        int *indexArray = new int(K);
        for(int i = 0; i < K; i++)
        {
            if(size/K == 1)
            {
                indexArray[i] = i*K;
            }
            else
            {
                indexArray[i] = i*size/K;
            }
        }

        for(int i = 0; i < size; i++)
        {
            if(heap[0] != INT_MAX)
            {
                newArr[i] = heap[0];
            }
            else
            {
                break;
            }

            for(int j = 0; j < K; j++)
            {
                if(heap[0] == arr[indexArray[j]])
                {
                    ++(indexArray[j]);
                    if((indexArray[j] % (size/K)) != 0)
                    {
                        heap[0] = arr[indexArray[j]];
                    }
                    else
                    {
                        heap[0] = INT_MAX;
                    }
                    break;
                }
            }
            heapify(heap, K, comparison, swap);
            for(int i = 0; i < K; i++)
            {
                cout << heap[i] << " ";
            }
            cout << endl;
            for(int i = 0; i < K; i++)
            {
                cout << indexArray[i] << " ";
            }
            cout << endl;
        }
        
        for(int a = 0; a < size; a++)
        {
            arr[a] = newArr[a];
        }
        return number_of_calls;
    }
}