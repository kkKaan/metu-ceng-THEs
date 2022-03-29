#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps)  // A function to read the input that will be used.
{
    int a, b, i, j;
    float ***sector_times;

    scanf(" %u %u", n_drivers, n_laps);

    sector_times = (float***) malloc(sizeof(float**)*(n_drivers[0]));

    for(i = 0; i < (*n_drivers); ++i) // Allocating memory for 3d array.
    {
        sector_times[i] = (float**) malloc(sizeof(float*)*(n_laps[0]));

        for(j = 0; j < (*n_laps); ++j){sector_times[i][j] = (float*) malloc(sizeof(float)*(n_sector));}
    }

    for(a = 0; a < (*n_drivers); ++a)
    {
        for(b = 0; b < (*n_laps); ++b){scanf(" %f %f %f", &sector_times[a][b][0], &sector_times[a][b][1], &sector_times[a][b][2]);}
    }
    return sector_times;
}

unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races)  // Reads input for another kind of information
{
    unsigned int** positions, a, b, c;

    scanf(" %u %u", p_drivers, n_races);

    positions = (unsigned int**) malloc(sizeof(unsigned int*)*(*p_drivers));

    for(a = 0; a < (*p_drivers); ++a){positions[a]=(unsigned int*)malloc(sizeof(unsigned int)*(*n_races));} // Allocating memory for 2d array.

    for(b = 0; b < (*p_drivers); ++b)
    {
        for(c = 0; c < (*n_races); ++c){scanf(" %u", &positions[b][c]);}
    }
    return positions;
}

float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps)
{
    float** lapTimes;
    int a,b,c,x;

    lapTimes = (float**) malloc(sizeof(float*)*n_drivers);

    for(x = 0; x < n_drivers; ++x){lapTimes[x] = (float*) malloc(sizeof(float)*n_laps);} // Allocating memory for 2d array.

    for(a = 0; a < n_drivers; ++a)
    {
        for(b = 0; b < n_laps; ++b)
        {
            for(c = 0; c < n_sector; ++c){lapTimes[a][b] += sector_times[a][b][c];}
        }
    }
    return lapTimes;
}

unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps)
{
    unsigned int fastest_driver, tempWin = 0;
    int a,b;
    float tempTime = 0;

    for(a = 0; a < n_drivers; ++a) // Basic "find max/min element" of a 2d array loop.
    {
        for(b = 0; b < n_laps; ++b)
        {
            if(!tempTime || 0.0001 < tempTime - lap_times[a][b]) // This is a check for the error that might occur, due to floating point numbers.
            {
                tempWin = a;
                tempTime = lap_times[a][b];
            }
        }
    }
    fastest_driver = tempWin;
    return fastest_driver;
}

unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps)
{
    unsigned int lapNum;
    int a, b;
    float tempSum, minSum=0;

    for(a = 0; a < n_laps; ++a)
    {
        tempSum=0;
        for(b = 0; b < n_sector; ++b){tempSum += sector_times_of_driver[a][b];}

        if(0.0001 < (minSum - tempSum) || !minSum) // The same epsilon check for floating sum values
        {
            minSum = tempSum;
            lapNum = a;
        }
    }
    return lapNum;
}

float* reversed(float* arr, unsigned int len)
{
    int a, b = len-1;

    for(a = 0; a < len/2; ++a, --b)
    {
        arr[a] = arr[a] - arr[b]; //  This is an idea for swapping the values of 2 variables without using a temporary one.
        arr[b] = arr[a] + arr[b];
        arr[a] = arr[b] - arr[a];
    }
    return arr;
}

float* selection_sort(float* arr, unsigned int len, char ord)
{
    float* sorted = (float *) malloc(sizeof(float)*len);
    int* checklist = (int*) malloc(sizeof(int)*len);
    int min_ind, x, a, len_new = 0;
    float min = 0;

    for(x = 0; x < len; ++x){checklist[x] = 0;}

    while(len_new != len) // Always finding in ascending order, if the change is needed, reversed function will be used.
    {
        for(a = 0; a < len; ++a)
        {
            if(!min || 0.0001 < (min-arr[a]))
            {
                if(checklist[a]){continue;}
                min = arr[a];
                min_ind = a;
            }
        }
        checklist[min_ind] = 1;
        sorted[len_new++] = min;
        min=0;
    }

    if(ord == 'D'){return reversed(sorted, len);}
    return sorted;
}

unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps)
{
    unsigned int* positions = (unsigned int*) malloc(sizeof(unsigned int)*n_drivers);
    float* race_times = (float*) malloc(sizeof(float)*n_drivers);
    int x, a, b, positions_ind = 0, min_ind;
    int* checklist = (int*) malloc(sizeof(int)*n_drivers);
    float min = 0;

    for(x = 0; x < n_drivers; ++x){checklist[x] = 0;}

    for(a = 0; a < n_drivers; ++a) // Finds total times of the racers.
    {
        for(b = 0; b < n_laps; ++b){race_times[a] += lap_times[a][b];}
    }

    while(positions_ind != n_drivers)
    {
        for(x = 0; x < n_drivers; ++x)
        {
            if(!min || 0.0001 < (min - race_times[x]))
            {
                if(checklist[x]){continue;}
                min = race_times[x];
                min_ind = x;
            }
        }
        checklist[min_ind] = 1;
        positions[positions_ind++] = min_ind;
        min = 0;
    }
    return positions;
}

// The last 3 of them are basic implementations that can be understood from THE file.
float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1, unsigned int driver2)
{
    float* time_diff = (float *) malloc(sizeof(float)*n_laps);
    int a;

    for(a = 0; a < n_laps; ++a){time_diff[a] = !a ? (lap_times[driver1][a] - lap_times[driver2][a]) : (time_diff[a] = time_diff[a-1] + lap_times[driver1][a] - lap_times[driver2][a]);}
    return time_diff;
}

unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races)
{
    unsigned int* total_points = (unsigned int *) malloc(sizeof(unsigned int)*p_drivers);
    unsigned int* points = (unsigned int *) malloc(sizeof(unsigned int)*p_drivers);
    int a,b,x;

    for(x = 0; x < p_drivers; ++x){scanf(" %u", &points[x]);}

    for(a = 0; a < p_drivers; ++a)
    {
        for(b = 0; b < n_races; ++b){total_points[a] += points[positions[a][b]-1];}
    }
    return total_points;
}

unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id)
{
    unsigned int rank=1;
    int a;

    for(a = 0; a < p_drivers; ++a)
    {
        if(a == id){continue;}
        else if(total_points[a] == total_points[id] && a > id){continue;}
        else if(total_points[a] >= total_points[id]){rank++;}
    }
    return rank;
}
