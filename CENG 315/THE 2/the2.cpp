#include "the2.h"
#include <cmath>
#include <iostream>

// a slightly modified version of the radix sort algorithm
void radixSort(int* arr, bool ascending, int arraySize, int maxDigitLength, int groupSize, long &numberOfIterations)
{
    int *newArr = new int[arraySize];
    int *count = new int[((int) pow(10, groupSize))];
    int *temp = new int[arraySize];

    int i = 0;
    int digit = 1;
    int digitCount = 0;
    int digitIndex = 0;
    int digitValue = 0;
    int remains = maxDigitLength % groupSize;
    
    for (i = 0; i < (maxDigitLength / groupSize); ++i)
    {
        for (int j = 0; j < pow(10, groupSize); j++)
        {
            count[j] = 0;
        }

        for (int j = 0; j < arraySize; j++)
        {
            digit = arr[j] / (int) pow(10, i*groupSize);
            digitCount = digit % ((int) pow(10, groupSize));
            count[digitCount]++;
            numberOfIterations++;
        }

        for (int j = 1; j < pow(10, groupSize); j++)
        {
            count[j] = count[j] + count[j - 1];
            numberOfIterations++;
        }

        for (int j = arraySize-1; j >= 0; --j)
        {
            digit = arr[j] / (int) pow(10, i*groupSize);
            digitCount = digit % ((int) pow(10, groupSize));
            digitIndex = count[digitCount];
            temp[digitIndex-1] = arr[j];
            count[digitCount]--;
            numberOfIterations++;
        }

        for (int j = 0; j < arraySize; j++)
        {
            arr[j] = temp[j];
            numberOfIterations++;
        }
    }

    if(remains)
    {
        int *newCount = new int[((int) pow(10, remains))];

        for (int j = 0; j < pow(10, remains); j++)
        {
            newCount[j] = 0;
        }

        for (int j = 0; j < arraySize; j++)
        {
            digit = arr[j] / (int) pow(10, (i*groupSize));
            digitCount = digit % ((int) pow(10, remains));
            newCount[digitCount]++;
            numberOfIterations++;
        }

        for (int j = 1; j < pow(10, remains); j++)
        {
            newCount[j] = newCount[j] + newCount[j - 1];
            numberOfIterations++;
        }

        for (int j = arraySize-1; j >= 0; --j)
        {
            digit = arr[j] / (int) pow(10, (i*groupSize));
            digitCount = digit % ((int) pow(10, remains));
            digitIndex = newCount[digitCount];
            temp[digitIndex-1] = arr[j];
            newCount[digitCount]--;
            numberOfIterations++;
        }

        for (int j = 0; j < arraySize; j++)
        {
            arr[j] = temp[j];
            numberOfIterations++;
        }
        delete[] newCount;
    }

    if (ascending == false)
    {
        for (int i = 0; i < arraySize / 2; i++)
        {
            digitValue = arr[i];
            arr[i] = arr[arraySize - i - 1];
            arr[arraySize - i - 1] = digitValue;
        }
    }
    delete[] newArr;
    delete[] count;
    delete[] temp;
}

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)
{
    long numberOfIterations = 0;
    radixSort(arr, ascending, arraySize, maxDigitLength, groupSize, numberOfIterations); return numberOfIterations;
}