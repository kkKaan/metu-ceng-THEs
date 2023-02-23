#include "the3.h"

int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) 
{ 
    //direct recursive
    number_of_calls+=1;

    int temp=0;
    int max=0;
    int curSize=len[i];

    if(i==0){return len[0];}
    else
    {
        if(number_of_calls==1)
        {
            for(int a=i-1; a>=0; a--)
            {
                temp = recursive_sln(a, arr, len, number_of_calls);
                if(temp > max){max=temp;}
            }

            for(int b=i-1; b>=0; b--)
            {
                if((arr[i][0]=='S' && arr[b][1]=='S') || (arr[i][0]=='I' && arr[b][1]=='O') || (arr[i][0]=='O' && arr[b][1]=='I'))
                {
                    temp = curSize + recursive_sln(b, arr, len, number_of_calls);
                    if(temp > max){max=temp;}
                    break;
                }
            }
        }
        else
        {
            for(int a=i-1; a >= 0; a--)
            {
                if(arr[i][1] == arr[a][1])
                {
                    temp = recursive_sln(a, arr, len, number_of_calls);
                    if(temp>max) {max=temp;}
                    break;
                }
            }

            for(int b=i-1; b>=0; b--)
            {
                if((arr[i][0]=='S' && arr[b][1]=='S') || (arr[i][0]=='I' && arr[b][1]=='O') || (arr[i][0]=='O' && arr[b][1]=='I'))
                {
                    temp = curSize + recursive_sln(b,arr,len,number_of_calls);
                    if(temp>max) {max=temp;}
                    break;
                }
            }
        }
    }
    
    if(len[i] > max)
    {
        max=len[i];
    }
    return max; 
}

int memoization_sln(int i, char**& arr, int*& len, int**& mem)
{ 
    //memoization
    // mem[i][0] represents terminating by 'I'
    // mem[i][1] represents terminating by 'O'
    // mem[i][2] represents terminating by 'S'
    
    if (i == 0)
    {
        if (arr[0][1] == 'I')
        {
            mem[0][0] = len[0];
            mem[0][1] = 0;
            mem[0][2] = 0;
        }
        else if (arr[0][1] == 'O')
        {
            mem[0][1] = len[0];
            mem[0][0] = 0;
            mem[0][2] = 0;
        }
        else
        {
            mem[0][2] = len[0];
            mem[0][0] = 0;
            mem[0][1] = 0;
        }
    }
    else
    {
        if (mem[i - 1][0] == -1 || mem[i - 1][1] == -1 || mem[i - 1][2] == -1) memoization_sln(i - 1, arr, len, mem);
        mem[i][0] = mem[i-1][0];
        mem[i][1] = mem[i-1][1];
        mem[i][2] = mem[i-1][2]; 

        // starts with what?    
        int update;
        if (arr[i][0] == 'I') update = mem[i-1][1] + len[i];
        else if (arr[i][0] == 'O') update = mem[i-1][0] + len[i];
        else update = mem[i-1][2] + len[i];
            
        // ends with what?
        if (arr[i][1] == 'I') mem[i][0] = mem[i][0] > update ? mem[i][0] : update;
        else if (arr[i][1] == 'O') mem[i][1] = mem[i][1] > update ? mem[i][1] : update;
        else mem[i][2] = mem[i][2] > update ? mem[i][2] : update; 
    }

    int max = mem[i][0] > mem[i][1] ? mem[i][0] : mem[i][1];
    max = max > mem[i][2] ? max : mem[i][2];
    return max;
}

int dp_sln(int size, char**& arr, int*& len, int**& mem)
{ 
    mem[0][0] = 0;
    mem[0][1] = 0;
    mem[0][2] = 0;
    
    if (arr[0][1] == 'I') mem[0][0] = len[0];
    else if (arr[0][1] == 'O') mem[0][1] = len[0];
    else mem[0][2] = len[0];
    
    for (int i = 1; i < size; i++)
    {
        mem[i][0] = mem[i-1][0];
        mem[i][1] = mem[i-1][1];
        mem[i][2] = mem[i-1][2];
        
        // starts with what?
        int update;
        if (arr[i][0] == 'I') update = mem[i-1][1] + len[i];
        else if (arr[i][0] == 'O') update = mem[i-1][0] + len[i];
        else update = mem[i-1][2] + len[i];
        
        // ends with what?
        if (arr[i][1] == 'I') mem[i][0] = mem[i][0] > update ? mem[i][0] : update;
        else if (arr[i][1] == 'O') mem[i][1] = mem[i][1] > update ? mem[i][1] : update;
        else mem[i][2] = mem[i][2] > update ? mem[i][2] : update;
    }
    
    int max = mem[size-1][0] > mem[size-1][1] ? mem[size-1][0] : mem[size-1][1];
    max = max > mem[size-1][2] ? max : mem[size-1][2];
    return max;
}