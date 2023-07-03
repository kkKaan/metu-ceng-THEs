// this file is for you for testing purposes, it won't be included in evaluation.

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "the4.h"

char getRandomChar(){
	char r = rand() % 5 + 65;
	return r;
}


void randomArray(char**& box1, char**& box2, int nrow, int ncol1, int ncol2)
{
	box1 = new char* [nrow];
	box2 = new char* [nrow];
	std::vector<char> column;
	
	for (int i = 0; i < nrow; i++) {
	   box1[i] = new char [ncol1];
	   box2[i] = new char [ncol2];
	}
	
	for (int i = 0; i < ncol1; i++)
	{
	    int nfull = rand() % nrow + 1;
	    for (int j = 0; j < nfull; j++) {
		    char r = getRandomChar();
		    column.push_back(r);
	    }
	    for (int j = nfull; j < nrow; j++) {
		    column.push_back('-');
	    }
	    std::random_shuffle(column.begin(), column.end());
	    for (int j = 0; j < nrow; j++) 
	        box1[j][i] = column[j];
        column.clear();
	}
	
	for (int i = 0; i < ncol2; i++)
	{
	    int nfull = rand() % nrow + 1;
	    for (int j = 0; j < nfull; j++) {
		    char r = getRandomChar();
		    column.push_back(r);
	    }
	    for (int j = nfull; j < nrow; j++) {
		    column.push_back('-');
	    }
	    std::random_shuffle(column.begin(), column.end());
	    for (int j = 0; j < nrow; j++) 
	        box2[j][i] = column[j];
	}
}



void printArrayInLine(char** arr, int nrow, int ncol){
	std::cout << "[ ";
	for(int i = 0; i < nrow; i++){
	    std::cout << "[";
	    for (int j = 0; j < ncol; j++) {
		    std::cout << arr[i][j];
		    if (j == ncol - 1)
			    std::cout << "]";
		    else
			    std::cout << ", ";
	    }
	    if (i == nrow - 1)
	        std::cout << " ]" << std::endl;
	    else
	        std::cout << ",\n";
	}
}


void printMemInLine(int** arr, int nrow, int ncol){
	std::cout << "[ ";
	for(int i = 0; i < nrow; i++){
	    std::cout << "[";
	    for (int j = 0; j < ncol; j++) {
		    std::cout << arr[i][j];
		    if (j == ncol - 1)
			    std::cout << "]";
		    else
			    std::cout << ", ";
	    }
	    if (i == nrow - 1)
	        std::cout << " ]" << std::endl;
	    else
	        std::cout << ",\n";
	}
}


void fillArray(char**& box1, char**& box2, int nrow, int ncol1, int ncol2)
{
        
	box1 = new char* [nrow];
	box2 = new char* [nrow];
	
	for (int i = 0; i < nrow; i++) {
	   box1[i] = new char [ncol1];
	   box2[i] = new char [ncol2];
	}

    // "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"	
	// EXAMPLE (a)
    
    box1[0][0] = 'M';
	box1[1][0] = 'R';
	box1[2][0] = 'V';
	box1[3][0] = '-';
	
	box2[0][0] = '-'; box2[0][1] = 'M'; box2[0][2] = 'V';
	box2[1][0] = 'M'; box2[1][1] = '-'; box2[1][2] = 'M';
	box2[2][0] = 'R'; box2[2][1] = '-'; box2[2][2] = 'R';
	box2[3][0] = 'V'; box2[3][1] = 'R'; box2[3][2] = '-';
	
	
	// "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"   
	// EXAMPLE (b)
    /*
    box1[0][0] = '-'; box1[0][1] = 'B'; box1[0][2] = 'C';
	box1[1][0] = 'B'; box1[1][1] = '-'; box1[1][2] = 'C';
	
	box2[0][0] = 'A'; box2[0][1] = '-'; box2[0][2] = 'C'; box2[0][3] = 'A'; box2[0][4] = 'B';
	box2[1][0] = '-'; box2[1][1] = 'C'; box2[1][2] = 'C'; box2[1][3] = 'A'; box2[1][4] = '-';
	*/
	
	// "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
	// EXAMPLE (c)
    /*
    box1[0][0] = 'A'; box1[0][1] = 'A'; box1[0][2] = 'C'; box1[0][3] = 'B'; box1[0][4] = '-';
	box1[1][0] = 'B'; box1[1][1] = 'C'; box1[1][2] = '-'; box1[1][3] = '-'; box1[1][4] = 'A';
	box1[2][0] = 'A'; box1[2][1] = 'C'; box1[2][2] = '-'; box1[2][3] = 'A'; box1[2][4] = '-';
	box1[3][0] = '-'; box1[3][1] = 'C'; box1[3][2] = '-'; box1[3][3] = '-'; box1[3][4] = 'C';
	
	box2[0][0] = 'A'; box2[0][1] = 'C'; box2[0][2] = 'B'; box2[0][3] = '-'; box2[0][4] = 'A'; box2[0][5] = 'B'; box2[0][6] = 'A';
	box2[1][0] = 'B'; box2[1][1] = 'A'; box2[1][2] = 'B'; box2[1][3] = '-'; box2[1][4] = 'C'; box2[1][5] = '-'; box2[1][6] = 'C';
	box2[2][0] = 'B'; box2[2][1] = '-'; box2[2][2] = '-'; box2[2][3] = 'A'; box2[2][4] = 'C'; box2[2][5] = 'A'; box2[2][6] = 'B';
	box2[3][0] = 'C'; box2[3][1] = '-'; box2[3][2] = 'B'; box2[3][3] = '-'; box2[3][4] = 'B'; box2[3][5] = 'A'; box2[3][6] = 'B';
	*/
	
	// "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
	// EXAMPLE (d)
	/*
	box1[0][0] = '-'; box1[0][1] = 'Y'; box1[0][2] = 'W'; box1[0][3] = 'Y'; box1[0][4] = '-'; box1[0][5] = '-';
	box1[1][0] = '-'; box1[1][1] = 'Z'; box1[1][2] = 'Y'; box1[1][3] = 'Y'; box1[1][4] = '-'; box1[1][5] = 'W';
	box1[2][0] = 'W'; box1[2][1] = 'Y'; box1[2][2] = 'Z'; box1[2][3] = 'Y'; box1[2][4] = '-'; box1[2][5] = '-';
	box1[3][0] = 'W'; box1[3][1] = 'W'; box1[3][2] = '-'; box1[3][3] = 'Y'; box1[3][4] = '-'; box1[3][5] = 'Y';
	box1[4][0] = '-'; box1[4][1] = 'Z'; box1[4][2] = '-'; box1[4][3] = '-'; box1[4][4] = 'Z'; box1[4][5] = 'Z';
	
	box2[0][0] = 'Z'; box2[0][1] = 'W'; box2[0][2] = '-';
	box2[1][0] = 'W'; box2[1][1] = 'Y'; box2[1][2] = '-';
	box2[2][0] = 'Y'; box2[2][1] = 'Z'; box2[2][2] = 'Y';
	box2[3][0] = '-'; box2[3][1] = 'Z'; box2[3][2] = '-';
	box2[4][0] = '-'; box2[4][1] = '-'; box2[4][2] = '-';
    */
    
    // "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
    // EXAMPLE (e)
    /*
    box1[0][0] = 'A'; box1[0][1] = 'B'; box1[0][2] = 'C'; box1[0][3] = 'A'; box1[0][4] = 'B'; box1[0][5] = 'C';
	box1[1][0] = 'B'; box1[1][1] = 'C'; box1[1][2] = 'C'; box1[1][3] = 'A'; box1[1][4] = '-'; box1[1][5] = 'A';
	
	box2[0][0] = 'A'; box2[0][1] = 'B'; box2[0][2] = 'B'; box2[0][3] = 'A';
	box2[1][0] = 'B'; box2[1][1] = 'A'; box2[1][2] = '-'; box2[1][3] = 'C';
	*/

    // "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
    // EXAMPLE (f)
    /*
    box1[0][0] = '-'; box1[0][1] = 'M'; box1[0][2] = 'V'; box1[0][3] = 'R';
	box1[1][0] = 'M'; box1[1][1] = '-'; box1[1][2] = 'R'; box1[1][3] = '-';
	box1[2][0] = 'R'; box1[2][1] = 'M'; box1[2][2] = 'M'; box1[2][3] = '-';
	box1[3][0] = 'V'; box1[3][1] = 'M'; box1[3][2] = '-'; box1[3][3] = 'R';
	
	box2[0][0] = 'M'; box2[0][1] = '-'; box2[0][2] = '-'; box2[0][3] = 'V';
	box2[1][0] = 'V'; box2[1][1] = 'R'; box2[1][2] = 'R'; box2[1][3] = 'M';
	box2[2][0] = '-'; box2[2][1] = '-'; box2[2][2] = '-'; box2[2][3] = '-';
	box2[3][0] = '-'; box2[3][1] = 'M'; box2[3][2] = '-'; box2[3][3] = 'R';
    */
    
}


void test(){
    clock_t begin, end;
    double duration;
    int min_cost_dp;


    int nrow = 4;      // max 100
    int ncol1 = 1;     // max 100
    int ncol2 = 3;     // max 100
    char** box1, ** box2;
	//randomArray(box1, box2, nrow, ncol1, ncol2);
	fillArray(box1, box2, nrow, ncol1, ncol2);
    std::cout << "BOX-1:" << std::endl;
    printArrayInLine(box1, nrow, ncol1);
    std::cout << "\nBOX-2:" << std::endl;
    printArrayInLine(box2, nrow, ncol2);
    std::cout << "\n\n";

    int** mem = new int*[ncol1+1];

    for(int i = 0; i <= ncol1; i++){
	    mem[i] = new int [ncol2+1];
	    for (int j = 0; j <= ncol2; j++)
		    mem[i][j] = -1;
	}



    std::cout << "__________________DYNAMIC PROGRAMMING:______________" << std::endl;

    for(int i = 0; i <= ncol1; i++){
	    for (int j = 0; j <= ncol2; j++)
		    mem[i][j] = -1;
	}


    if ((begin = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    min_cost_dp = dp_sln(box1, box2, nrow, ncol1, ncol2, mem);

    if ((end = clock() ) ==-1)
        std::cerr << "clock error" << std::endl;

    duration = ((double) end - begin) / CLOCKS_PER_SEC;
    std::cout << "Duration: " << duration << " seconds." << std::endl;

    std::cout << "Min cost: " << min_cost_dp << std::endl;
    std::cout << "Final mem: " << std::endl;
    printMemInLine(mem, ncol1+1, ncol2+1);

    std::cout << "----------------------------------------------------";
    std::cout << "\n" << std::endl;

}

int main()
{
    srand(time(0));
    test();
    return 0;
}
