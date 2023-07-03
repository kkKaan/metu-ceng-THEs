//This file is entirely for your test purposes.
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "the1.h"

// the1.h only contains declaration of the function:
// int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap) ;

using namespace std;

void randomFill(int*& arr, int size, int minval, int interval){
	arr = new int [size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = minval + (rand() % interval);
	}
}

void print_to_file(int* arr, int size){
	ofstream ofile;
	ofile.open("sorted.txt");
	for(int i = 0; i < size; i++)
		ofile << arr[i] << endl;
}

void read_from_file(int*& arr, int& K, int& size){

	char addr[]= "input01.txt";
	ifstream infile (addr);
	if (!infile.is_open())
	{
		cout << "File \'"<< addr
			<< "\' can not be opened. Make sure that this file exists." <<endl;
		return;
	}
  infile >> K;
  infile >> size;
	arr = new int [size];

	for (int i=0; i<size;i++) {

		infile >> arr[i];
	}
}


void test(int* arr, int K, int array_size){

	clock_t begin, end;
	double duration;

	//data generation and initialization- you may test with your own data
	long comparison = 0;
	long swap = 0;
	int calls;




	// Print initial array
    cout << "Array size: " << array_size << ", K: " << K << endl << endl;
    cout << "Initial Array: {";
    for(int i=0; i<array_size; i++){
        cout << arr[i];
        if(i != array_size-1) cout << ", ";
    }
    cout << "}" << endl;
    
    // Function call and and calculate the duration
    if ((begin = clock() ) ==-1)
		cerr << "clock error" << endl;
		
    calls = kWayMergeSortWithHeap(arr, K, array_size, comparison, swap);
    
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
	cout << "Number of comparison: " << comparison << endl <<
            "Number of swap: " << swap << endl <<
            "Number of calls: " << calls << endl;
	print_to_file(arr, array_size);
	// Calculation and output end
}

int main(){
    int size = 15;
	int K = 5;
	int minval = 0;
	int interval = 100;
	int *arr;
    // Randomly generate initial array:
	randomFill(arr, size, minval, interval);
    // Read the test inputs. input01.txt through input04.txt exists.
    // read_from_file(arr, K, size);
	srand(time(0));
	test(arr, K, size);
	cout << endl;
	return 0;
}
