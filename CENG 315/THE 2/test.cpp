//This file is entirely for your test purposes.
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "the2.h"

// the2.h only contains declaration of the function:
// int multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)

using namespace std;

void randomFill(int*& arr, int size, int minval, int interval){
	arr = new int [size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = minval + (rand() % interval);
	}
}

void print_to_file(int* arr, int size, long numberOfIterations){
	ofstream ofile;
	ofile.open("outsol01.txt");
    ofile << numberOfIterations << endl;
    ofile << size << endl;
	for(int i = 0; i < size; i++)
		ofile << arr[i] << endl;
}

void read_from_file(int*& arr, int& size, bool& ascending, int& groupSize, int& maxDigitLength){

	char addr[]= "hugeArray.txt";
	ifstream infile (addr);
	if (!infile.is_open())
	{
		cout << "File \'"<< addr
			<< "\' can not be opened. Make sure that this file exists." <<endl;
		return;
	}
  infile >> ascending;
  infile >> groupSize;
  infile >> maxDigitLength;
  infile >> size;
	arr = new int [size];

	for (int i=0; i<size;i++) {

		infile >> arr[i];
	}
}


void test(int* arr, bool ascending, int groupSize, int maxDigitLength, int array_size){

	clock_t begin, end;
	double duration;
    long iterations=0;
	// Print initial array
    cout << "Array size: " << array_size << endl
         << "Group size: : " << groupSize << endl
         << "Max Digit Length: " << maxDigitLength << endl 
         << "Ascending: ";
    if(ascending){
        cout << "True" << endl << endl;
    }else{
        cout << "False" << endl << endl;
    }
    cout << "Initial Array: {";
    for(int i=0; i<array_size; i++){
        cout << arr[i];
        if(i != array_size-1) cout << ", ";
    }
    cout << "}" << endl;
    
    // Function call and and calculate the duration
    if ((begin = clock() ) ==-1)
		cerr << "clock error" << endl;
		
    iterations = multiDigitRadixSort(arr, ascending, array_size, groupSize, maxDigitLength);
    
    if ((end = clock() ) ==-1)
		cerr << "clock error" << endl;

    
	cout << "Sorted Array: {";
    for(int i=0; i<array_size; i++){
        cout << arr[i];
        if(i != array_size-1) cout << ", ";
    }
    cout << "}" << endl << endl;
    
	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	cout << "Duration: " << duration << " seconds." <<endl;
	cout << "Number of iterations: " << iterations << endl;
	print_to_file(arr, array_size, iterations);
	// Calculation and output end
}

int main(){
    int size = 5;
	int groupSize = 1;
	int maxDigitLength = 3;
	int minval = 0;
	int interval = 900;
	int *arr;
	bool ascending = true;
    // Randomly generate initial array:
	srand(time(0));
	// randomFill(arr, size, minval, interval);
    // Read the test inputs. input01.txt through input04.txt exists.
    read_from_file(arr, size, ascending, groupSize, maxDigitLength);
	test(arr, ascending, groupSize, maxDigitLength, size);
	cout << endl;
	return 0;
}