#include "hw2_output.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

static struct timeval g_start_time;

void hw2_init_output(void)
{
    gettimeofday(&g_start_time, NULL);
}

static long get_timestamp(void)
{
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
    return (cur_time.tv_sec - g_start_time.tv_sec) * 1000000 
           + (cur_time.tv_usec - g_start_time.tv_usec);
}

void hw2_write_output(unsigned matrix_id, unsigned row, unsigned col, int value)
{
    static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    if (g_start_time.tv_sec == 0 && g_start_time.tv_usec == 0) {
        fprintf(stderr, "You must call hw2_init_output() at the start of your main()!");
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_lock(&mut);

    printf("t: %9ld | ", get_timestamp());

    printf("(T%lu) ", pthread_self());

    printf("Matrix%u (%u,%u):%d\n", matrix_id, row, col, value);

    pthread_mutex_unlock(&mut);
}