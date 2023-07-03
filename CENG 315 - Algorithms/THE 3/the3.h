#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cmath>

int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls);
int memoization_sln(int i, char**& arr, int*& len, int**& mem);
int dp_sln(int size, char**& arr, int*& len, int**& mem);