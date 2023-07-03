// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "the3.h"

char getRandomEnd(){
	int r = rand()%3;
	if (r == 0)
	    return 'I';
	if (r == 1)
	    return 'O';
	return 'S';
}

void randomArray(char**& array, int*& len, int size)
{
	array = new char* [size];
	len = new int[size];
	for (int i = 0; i < size; i++)
	{
	    char* stick = new char[2];
		char left = getRandomEnd();
		stick[0] = left;
		char right = getRandomEnd();
		stick[1] = right;
		array[i] = stick;
		len[i] = rand() % 10 + 1;
	}
}


void printArrayInLine(char** arr, int* len, int arraySize){
	std::cout << "[";
	for(int i = 0; i < arraySize; i++){
		std::cout << "[" << arr[i][0] << ", " << arr[i][1] << "]";
		if (i == arraySize - 1){
			continue;
		}
		else{
			std::cout << ", \n";
		}
	}
	std::cout << "]" << std::endl;
	
	std::cout << "{";
	for(int i = 0; i < arraySize; i++) {
	    std::cout << len[i] << ", ";
	    if (i == arraySize - 1){
			continue;
		}
		else{
			std::cout << ", \n";
		}
	}
	std::cout << "}" << std::endl;
}


void printMemInLine(int** arr, int arraySize){
	std::cout << "[";
	for(int i = 0; i < arraySize; i++){
		std::cout << "[" << arr[i][0] << ", " << arr[i][1] << ", " << arr[i][2] << "]";
		if (i == arraySize - 1){
			continue;
		}
		else{
			std::cout << ", \n";
		}
	}
	std::cout << "]" << std::endl;
}



void test(){
    clock_t begin, end;
    double duration;
    int max_length_rec;
    int max_length_mem;
    int max_length_dp;


    int size = 10;      // max 1000
    char** arr;
    int* len;
    randomArray(arr, len, size);
    std::cout << "Array:" << std::endl;
    printArrayInLine(arr, len, size);



    std::cout << "_____________RECURSIVE IMPLEMENTATION:_____________" << std::endl;

    int number_of_calls_rec = 0;

    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    max_length_rec = recursive_sln(size-1, arr, len, number_of_calls_rec);

    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Max length: " << max_length_rec << std::endl;
    std::cout << "Number of recursive calls: " << number_of_calls_rec << std::endl;

    std::cout << "---------------------------------------------------";
    std::cout << "\n" << std::endl;



    int** mem = new int*[size];


    std::cout << "______________________MEMOIZATION:__________________" << std::endl;

    for(int i = 0; i < size; i++) {
        mem[i] = new int[3];
        for (int j = 0; j < 3; j++)
            mem[i][j] = -1;
    }


    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    max_length_mem = memoization_sln(size-1, arr, len, mem);
    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Max length: " << max_length_mem << std::endl;
    std::cout << "Final mem: " << std::endl;
    printMemInLine(mem, size);

    std::cout << "----------------------------------------------------";
    std::cout << "\n" << std::endl;




    std::cout << "__________________DYNAMIC PROGRAMMING:______________" << std::endl;

    for(int i = 0; i < size; i++)
        for (int j = 0; j < 3; j++)
            mem[i][j] = -1;


    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    max_length_dp = dp_sln(size, arr, len, mem);

    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Max length: " << max_length_dp << std::endl;
    std::cout << "Final mem: " << std::endl;
    printMemInLine(mem, size);

    std::cout << "----------------------------------------------------";
    std::cout << "\n" << std::endl;

}

int main()
{
    srand(time(0));
    test();
    return 0;
}
