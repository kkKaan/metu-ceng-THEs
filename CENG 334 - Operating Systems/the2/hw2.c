#include "hw2_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int **m1, **m2, **m3, **m4, **j, **l, **r, row1 = 0, col1 = 0, row2 = 0, col2 = 0, *protected_array;
sem_t *sem_j, *sem_l_row, *sem_r, *sem_l_col, *sem_j_row, sem_protected_array;

typedef struct // thread data for add_matrices
{
    int row;
    int col;
    int **mat1;
    int **mat2;
    int **result;
    int matrix_id;
} thread_data;

typedef struct  // thread data for multiply_matrices
{
    int row;
    int col1;
    int col2;
    int **mat1;
    int **mat2;
    int **result;
} multiply_thread_data;

void take_inputs(int ***m1, int ***m2, int ***m3, int ***m4, int *size1X, int *size1Y, int *size2X, int *size2Y)
{
    int row, col;

    for(int i = 0; i < 4; ++i)
    {
        scanf(" %d %d", &row, &col);

        if (i == 0) // sizes of first 2 matrices
        {
            *size1X = row;
            *size1Y = col;
        }
        else if (i == 2) // sizes of last 2 matrices
        {
            *size2X = row;
            *size2Y = col;
        }

        switch (i)
        {
            case 0:
                *m1 = (int **)malloc(row * sizeof(int *));
                for(int j = 0; j < row; ++j)
                {
                    (*m1)[j] = (int *)malloc(col * sizeof(int));
                    for(int k = 0; k < col; ++k)
                    {
                        scanf(" %d", &(*m1)[j][k]);
                    }
                }
                break;
            case 1:
                *m2 = (int **)malloc(row * sizeof(int *));
                for(int j = 0; j < row; ++j)
                {
                    (*m2)[j] = (int *)malloc(col * sizeof(int));
                    for(int k = 0; k < col; ++k)
                    {
                        scanf(" %d", &(*m2)[j][k]);
                    }
                }
                break;
            case 2:
                *m3 = (int **)malloc(row * sizeof(int *));
                for(int j = 0; j < row; ++j)
                {
                    (*m3)[j] = (int *)malloc(col * sizeof(int));
                    for(int k = 0; k < col; ++k)
                    {
                        scanf(" %d", &(*m3)[j][k]);
                    }
                }
                break;
            case 3:
                *m4 = (int **)malloc(row * sizeof(int *));
                for(int j = 0; j < row; ++j)
                {
                    (*m4)[j] = (int *)malloc(col * sizeof(int));
                    for(int k = 0; k < col; ++k)
                    {
                        scanf(" %d", &(*m4)[j][k]);
                    }
                }
                break;
            default:
                break;
        }
    }
}

void print_matrix(int **m, int row, int col)
{
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j) printf("%d ", m[i][j]);
        printf("\n");
    }
}

void *add_matrices(void *args)
{
    // read thread data
    thread_data *data = (thread_data *)args;
    int row = data->row;
    int col = data->col;
    int **mat1 = data->mat1;
    int **mat2 = data->mat2;
    int **result = data->result;
    int matrix_id = data->matrix_id;

    sem_t *sem = (matrix_id == 0) ? &sem_j[row] : &sem_l_row[row]; // determine which matrices are being added
    sem_wait(sem);

    for(int j = 0; j < col; ++j)
    {
        result[row][j] = mat1[row][j] + mat2[row][j];
        hw2_write_output(matrix_id, row+1, j+1, result[row][j]);
        
        if (matrix_id == 1)
        {
            sem_wait(&sem_protected_array);
            protected_array[j]++;
            sem_post(&sem_protected_array);
        }
    }

    if (matrix_id == 0)
    {
        sem_post(&sem_j_row[row]);
    }
    else if (matrix_id == 1)
    {
        for(int i = 0; i < col2; ++i)
        {
            if(protected_array[i] == row2) // if all elements in column are added
            {
                sem_post(&sem_l_col[i]);
            }
        }
    }
    sem_post(sem);
    free(args);
}

void *multiply_matrices(void *args)
{
    // read thread data
    multiply_thread_data *data = (multiply_thread_data *)args;
    int row = data->row;
    int col1 = data->col1;
    int col2 = data->col2;
    int **mat1 = data->mat1;
    int **mat2 = data->mat2;
    int **result = data->result;

    sem_wait(&sem_r[row]);  // wait for result row to be ready
    sem_wait(&sem_j_row[row]); // wait for j row to be ready

    for(int j = 0; j < col2; ++j)
    {
        sem_wait(&sem_l_col[j]);

        result[row][j] = 0;
        for(int k = 0; k < col1; ++k)
        {
            result[row][j] += mat1[row][k] * mat2[k][j];
        }
        hw2_write_output(2, row+1, j+1, result[row][j]);

        sem_post(&sem_l_col[j]);
    }
    sem_post(&sem_j_row[row]);
    sem_post(&sem_r[row]);  
    free(args);
}

int main()
{
    hw2_init_output();
    take_inputs(&m1, &m2, &m3, &m4, &row1, &col1, &row2, &col2);

    // initialize matrices
    j = (int **)malloc(row1 * sizeof(int *));
    l = (int **)malloc(row2 * sizeof(int *));
    r = (int **)malloc(row1 * sizeof(int *));
    protected_array = (int *)malloc(col2 * sizeof(int));

    for (int i = 0; i < row1; ++i)
    {
        j[i] = (int *)malloc(col1 * sizeof(int));
        r[i] = (int *)malloc(col2 * sizeof(int));

        for (int k = 0; k < col2; ++k)
        {
            r[i][k] = 0;
        }

        for (int k = 0; k < col1; ++k)
        {
            j[i][k] = 0;
        }
    }

    for (int i = 0; i < row2; ++i)
    {
        l[i] = (int *)malloc(col2 * sizeof(int));

        for (int j = 0; j < col2; ++j)
        {
            l[i][j] = 0;
        }
    }

    for(int j = 0; j < col2; ++j)
    {
        protected_array[j] = 0;
    }

    // initialize semaphores
    sem_j = (sem_t *)malloc(sizeof(sem_t) * row1);
    sem_l_row = (sem_t *)malloc(sizeof(sem_t) * row2);
    sem_l_col = (sem_t *)malloc(sizeof(sem_t) * col2);
    sem_j_row = (sem_t *)malloc(row1 * sizeof(sem_t));
    sem_r = (sem_t *)malloc(row1 * sizeof(sem_t));

    for(int i = 0; i < row1; ++i)
    {
        sem_init(&sem_j[i], 0, 1);
        sem_init(&sem_j_row[i], 0, 0);
        sem_init(&sem_r[i], 0, 1);  
    }

    for(int i = 0; i < row2; ++i)
    {
        sem_init(&sem_l_row[i], 0, 1);
    }

    for(int i = 0; i < col2; ++i)
    {
        sem_init(&sem_l_col[i], 0, 0);
    }

    sem_init(&sem_protected_array, 0, 1);

    // create threads
    pthread_t *j_threads = (pthread_t *)malloc(sizeof(pthread_t) * row1);
    pthread_t *l_threads = (pthread_t *)malloc(sizeof(pthread_t) * row2);
    pthread_t *r_threads = (pthread_t *)malloc(sizeof(pthread_t) * row1);

    for(int i = 0; i < row1 || i < row2; ++i)
    {
        if (i < row1)
        {
            thread_data *j_data = (thread_data *)malloc(sizeof(thread_data));
            j_data->row = i;
            j_data->col = col1;
            j_data->mat1 = m1;
            j_data->mat2 = m2;
            j_data->result = j;
            j_data->matrix_id = 0;

            pthread_create(&(j_threads[i]), NULL, add_matrices, (void *)j_data);
        }

        if (i < row2)
        {
            thread_data *l_data = (thread_data *)malloc(sizeof(thread_data));
            l_data->row = i;
            l_data->col = col2;
            l_data->mat1 = m3;
            l_data->mat2 = m4;
            l_data->result = l;
            l_data->matrix_id = 1;

            pthread_create(&(l_threads[i]), NULL, add_matrices, (void *)l_data);
        }

        if (i < row1)
        {
            multiply_thread_data *r_data = (multiply_thread_data *)malloc(sizeof(multiply_thread_data));
            r_data->row = i;
            r_data->col1 = col1;
            r_data->col2 = col2;
            r_data->mat1 = j;
            r_data->mat2 = l;
            r_data->result = r;

            pthread_create(&(r_threads[i]), NULL, multiply_matrices, (void *)r_data);
        }
    }

    // wait for threads to finish
    for (int i = 0; i < row1 || i < row2; ++i)
    {
        if(i < row1) pthread_join(j_threads[i], NULL);
        if(i < row2) pthread_join(l_threads[i], NULL);
        if(i < row1) pthread_join(r_threads[i], NULL);
    }
    
    // destroy semaphores
    for(int i = 0; i < row1; ++i)
    {
        sem_destroy(&sem_j[i]);
        sem_destroy(&sem_j_row[i]);
        sem_destroy(&sem_r[i]);
    }

    for(int i = 0; i < row2; ++i)
    {
        sem_destroy(&sem_l_row[i]);
    }

    for(int i = 0; i < col2; ++i)
    {
        sem_destroy(&sem_l_col[i]);
    }
    sem_destroy(&sem_protected_array);
 
    print_matrix(r, row1, col2);

    // free memory
    for (int i = 0; i < row1; ++i)
    {
        free(m1[i]);
        free(m2[i]);
        free(j[i]);
        free(r[i]);
    }

    for (int i = 0; i < row2; ++i)
    {
        free(m3[i]);
        free(m4[i]);
        free(l[i]);
    }

    free(protected_array);

    free(m1);
    free(m2);
    free(m3);
    free(m4);
    free(j);
    free(l);
    free(r);

    free(sem_j);
    free(sem_l_row);
    free(sem_l_col);
    free(sem_j_row);
    free(sem_r);

    free(j_threads);
    free(l_threads);
    free(r_threads);

    return 0;
}
