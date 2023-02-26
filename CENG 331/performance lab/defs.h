/*
 * driver.h - Various definitions for the Performance Lab.
 * 
 * DO NOT MODIFY ANYTHING IN THIS FILE
 */
#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>

#define RIDX(i,j,n) ((i)*(n)+(j))

typedef struct {
  char *team_name;
    char *ID1, *name1;
    char *ID2, *name2;
    char *ID3, *name3;
} team_t;

typedef struct {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
} pixel;

typedef void (*lab_test_conv) (int, pixel*, pixel*, unsigned *);

typedef void (*lab_test_avpol) (int, pixel*, pixel*);


void convolution(int, pixel *,pixel *, unsigned *);

void average_pooling(int, pixel *,pixel *);


void register_conv_functions(void);

void register_average_pooling_functions(void);


void add_conv_function(lab_test_conv, char*);

void add_average_pooling_function(lab_test_avpol, char*);

#endif /* _DEFS_H_ */

