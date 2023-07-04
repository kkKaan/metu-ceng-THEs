#ifndef HW2_OUTPUT_H_
#define HW2_OUTPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

// Call this at the start of your main function!
void hw2_init_output(void);

// The output function to show when a cell of a matrix is calculated. Matrix id is 0 for the first addition and 1 for the second addition. 
// Finally matrix id is 2 for the final result.
void hw2_write_output(unsigned matrix_id, unsigned row, unsigned col, int value);

#ifdef __cplusplus
}
#endif

#endif