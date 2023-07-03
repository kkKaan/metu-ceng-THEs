#include "the4.h"

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem)
{ 
    //dynamic programming

    for (int i = 0; i <= ncol1; i++) // initialize mem with 0
    {
        for (int j = 0; j <= ncol2; j++)
        {
            mem[i][j] = 0;
        }
    }

    for(int i = 1; i <= ncol2; ++i) // for the first row
    {
        mem[0][i] = mem[0][i-1];
        for(int k = 0; k < nrow; ++k)
        {
            if(arr2[k][i-1] != '-') ++mem[0][i];
        }
    }

    for(int j = 1; j <= ncol1; ++j) // for the first column
    {
        mem[j][0] = mem[j-1][0];
        for(int k = 0; k < nrow; ++k)
        {
            if(arr1[k][j-1] != '-') ++mem[j][0];
        }
    }

    for(int a = 1; a <= ncol2; ++a)
    {
        for(int b = 1; b <= ncol1; ++b) // change mem[b][a]
        {
            int replace = 0; 
            int reorder = 1000000; 
            int del = 0;
            int ins = 0;

            for(int i = 0; i < nrow; ++i) // replace
            {
                if(arr1[i][b-1] == arr2[i][a-1]) continue;
                else if((arr1[i][b-1] != '-') && (arr2[i][a-1] != '-')) ++replace;
                else replace += 2;
            }

            int compare = 1; // reorder
            int *tempArr1 = new int[nrow];
            int *tempArr2 = new int[nrow];

            for(int a1 = 0; a1 < nrow; ++a1) // add elements of arrays to temp arrays
            {
                tempArr1[a1] = arr1[a1][b-1];
                tempArr2[a1] = arr2[a1][a-1];
            }

            for(int i = 0; i < nrow; ++i) // sort tempArr1 and tempArr2 with bubble sort
            {
                for(int j = 0; j < nrow - 1; ++j)
                {
                    if(tempArr1[j] > tempArr1[j+1])
                    {
                        int temp = tempArr1[j];
                        tempArr1[j] = tempArr1[j+1];
                        tempArr1[j+1] = temp;
                    }

                    if(tempArr2[j] > tempArr2[j+1])
                    {
                        int temp = tempArr2[j];
                        tempArr2[j] = tempArr2[j+1];
                        tempArr2[j+1] = temp;
                    }
                }
            }

            for(int i = 0; i < nrow; ++i) // compare 2 arrays
            {
                if(tempArr1[i] != tempArr2[i]) compare = 0;
            }

            if(compare == 1) 
            {
                reorder = 0;
                for(int i = 0; i < nrow; ++i)
                {
                    if(arr1[i][b-1] != arr2[i][a-1]) ++reorder;
                }
            }
            
            for(int i = 0; i < nrow; ++i) // delete
            {
                if(arr1[i][b-1] != '-') ++del;
            }

            for(int i = 0; i < nrow; ++i) // insert
            {
                if(arr2[i][a-1] != '-') ++ins;
            }
            
            int o1, o2, o3;
            o1 = mem[b-1][a-1] + fmin(replace, reorder); 
            o2 = mem[b-1][a] + del; // delete of that col
            o3 = mem[b][a-1] + ins; // ins that row 
            mem[b][a] = fmin(fmin(o1, o2), o3);

            delete[] tempArr1;
            delete[] tempArr2;
        }
    }
    return mem[ncol1][ncol2]; 
}

int main()
{
    int nrow = 4;      // max 100
    int ncol1 = 1;     // max 100
    int ncol2 = 3;     // max 100
    char** box1, ** box2;

    box1 = new char* [nrow];
	box2 = new char* [nrow];
	
	for (int i = 0; i < nrow; i++)
    {
	   box1[i] = new char [ncol1];
	   box2[i] = new char [ncol2];
	}

    box1[0][0] = 'M';
	box1[1][0] = 'R';
	box1[2][0] = 'V';
	box1[3][0] = '-';
	
	box2[0][0] = '-'; box2[0][1] = 'M'; box2[0][2] = 'V';
	box2[1][0] = 'M'; box2[1][1] = '-'; box2[1][2] = 'M';
	box2[2][0] = 'R'; box2[2][1] = '-'; box2[2][2] = 'R';
	box2[3][0] = 'V'; box2[3][1] = 'R'; box2[3][2] = '-';

    int** mem = new int*[ncol1+1];

    for(int i = 0; i <= ncol1; i++)
    {
	    mem[i] = new int [ncol2+1];
	    for (int j = 0; j <= ncol2; j++) mem[i][j] = -1; 
	}

    int min_cost_dp = dp_sln(box1, box2, nrow, ncol1, ncol2, mem);

    for(int i = 0; i <= ncol1; i++)
    {
	    for (int j = 0; j <= ncol2; j++)
        {
            std::cout << mem[i][j] << ' ';
        }
		std::cout << std::endl;
	}
    return 0;
}