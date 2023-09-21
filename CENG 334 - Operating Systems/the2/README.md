# Multi-Threaded Matrix Operation

This assignment focuses on developing multi-threaded applications and synchronization techniques using C or C++. There are two different matrix operations with multiple threads performing them on four matrices. The results will be printed after synchronization using mutexes, semaphores, and condition variables.

## Project Code Overview

The provided code includes the necessary libraries and data structures to get you started with the assignment. Below is a brief overview of the key components:

### Data Structures

- `int **m1`, `int **m2`, `int **m3`, `int **m4`: Pointers to four matrices.
- `int **j`, `int **l`, `int **r`: Result matrices for addition and multiplication.
- `int row1`, `int col1`, `int row2`, `int col2`: Sizes of the matrices.
- `int *protected_array`: Array for tracking column additions.
- `sem_t *sem_j`, `sem_t *sem_l_row`, `sem_t *sem_r`, `sem_t *sem_l_col`, `sem_t *sem_j_row`, `sem_t sem_protected_array`: Semaphores for synchronization.

### Threads

- `add_matrices`: Function to add two matrices concurrently.
- `multiply_matrices`: Function to multiply two matrices concurrently.
- `thread_data`: Struct to hold thread-specific data for addition.
- `multiply_thread_data`: Struct to hold thread-specific data for multiplication.

### Input and Output

- `take_inputs`: Function to read matrix data from standard input.
- `print_matrix`: Function to print a matrix.

### Initialization and Thread Management

- Memory allocation for matrices, semaphores, and threads.
- Thread creation and joining.
- Semaphore initialization and destruction.

## Implementation Steps

1. **Data Input**: Modify the `take_inputs` function if necessary to read matrices and their sizes from standard input.

2. **Matrix Operations**: Implement the `add_matrices` and `multiply_matrices` functions to perform the addition and multiplication of matrices concurrently using multiple threads. Ensure proper synchronization using semaphores and mutexes.

3. **Thread Management**: Create and manage threads for matrix operations. Ensure that threads are synchronized correctly to produce accurate results.

4. **Output**: Print the resulting matrices once the operations are complete.

## Usage

1. Compile the code using a C or C++ compiler.

2. Run the executable. It should take matrix input from standard input, perform the matrix operations concurrently using multiple threads, and display the results.

## Cleanup

Make sure to deallocate memory and destroy semaphores to prevent resource leaks.

---

