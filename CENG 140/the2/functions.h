#ifndef functions
#define functions
#include <stdlib.h>
#include <stdio.h>

/* Do not modify this file */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps);
unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races);
float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps);
unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps);
unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps);
float* selection_sort(float* arr, unsigned int len, char ord);
unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps);
float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2);
unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races);
unsigned int find_season_ranking(int* total_points, unsigned int p_drivers, unsigned int id);

#endif
