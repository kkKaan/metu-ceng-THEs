/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
        "SEFIM",    /* Team Name */

        "e2",      /* First student ID */
        "Mert Uludoğan",

        "e2",
        "Kaan Karaçanta",

        "",
        ""
};

/********************
 * CONVOLUTION KERNEL
 ********************/

/***************************************************************
 * Your different versions of the convolution functions  go here
 ***************************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";

void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst) 
{
    int i,j,k,l;

    for(i = 0; i < dim-8+1; i++)
            for(j = 0; j < dim-8+1; j++) 
            {
                dst[RIDX(i, j, dim)] = 0;
                for(k = 0; k < 8; k++)  
                    for(l = 0; l < 8; l++) {
                        dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].red * ker[RIDX(k, l, 8)].red;
                        dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].green * ker[RIDX(k, l, 8)].green;
                        dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].blue * ker[RIDX(k, l, 8)].blue;
                    }

            }
    // convolution(dim, src, ker, dst);
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    unsigned short int i,j,s1,s2,s3,s4;
    int iDim_j, iDim_j_kDim, k8;
    int dim7 = dim-7;
    pixel *src_p1, *ker_p1;
    unsigned* dst_p;

    for(i = 0; i < dim7; i+=2)
    {
        for(j = 0; j < dim7; j+=2) 
        {
            iDim_j = i*dim + j; 
            dst_p = &dst[iDim_j];

            iDim_j_kDim = iDim_j;
            k8 = 0;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
            s1 = s2 = s3 = s4 = 0;
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;

            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            *dst_p = s1 + s2 + s3 + s4;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j = i*dim + j + 1;
            ++dst_p;

            iDim_j_kDim = iDim_j;
            k8 = 0;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
            s1 = s2 = s3 = s4 = 0;
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            *dst_p = s1 + s2 + s3 + s4;
        }









        for(j = 0; j < dim7; j+=2) 
        {
            iDim_j = i*dim + j + dim; 
            dst_p = &dst[iDim_j];

            iDim_j_kDim = iDim_j;
            k8 = 0;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
            s1 = s2 = s3 = s4 = 0;
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;

            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            *dst_p = s1 + s2 + s3 + s4;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j = i*dim + j + 1 + dim;
            ++dst_p;

            iDim_j_kDim = iDim_j;
            k8 = 0;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
            s1 = s2 = s3 = s4 = 0;
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];
 
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s1 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;
            
            ++src_p1;
            ++ker_p1; 
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s2 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1; 
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s3 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            ++src_p1;
            ++ker_p1;
            s4 += src_p1->red * ker_p1->red + src_p1->blue * ker_p1->blue + src_p1->green * ker_p1->green;

            iDim_j_kDim += dim;
            k8 += 8;
            src_p1 = &src[iDim_j_kDim];
            ker_p1 = &ker[k8];

            *dst_p = s1 + s2 + s3 + s4;
        }
    }
}


/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions() 
{
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}


/************************
 * AVERAGE POOLING KERNEL
 ************************/

/*********************************************************
 * Your different versions of the average pooling  go here
 *********************************************************/

/*
 * naive_average_pooling - The naive baseline version of average pooling
 */
char naive_average_pooling_descr[] = "Naive Average Pooling: Naive baseline implementation";
void naive_average_pooling(int dim, pixel *src, pixel *dst) 
{
    int i,j,k,l;

    for(i = 0; i < dim/2; i++)
        for(j = 0; j < dim/2; j++) {
            dst[RIDX(i, j, dim/2)].red = 0;
            dst[RIDX(i, j, dim/2)].green = 0;
            dst[RIDX(i, j, dim/2)].blue = 0;
            for(k = 0; k < 2; k++) {
                for (l = 0; l < 2; l++) {
                    dst[RIDX(i, j, dim/2)].red += src[RIDX(i*2 + k, j*2 + l, dim)].red;
                    dst[RIDX(i, j, dim/2)].green += src[RIDX(i*2 + k, j*2 + l, dim)].green;
                    dst[RIDX(i, j, dim/2)].blue += src[RIDX(i*2 + k, j*2 + l, dim)].blue;
                }
            }
            dst[RIDX(i, j, dim/2)].red /= 4;
            dst[RIDX(i, j, dim/2)].green /= 4;
            dst[RIDX(i, j, dim/2)].blue /= 4;
        }
    // average_pooling(dim, src, dst);
}


/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";
void average_pooling(int dim, pixel *src, pixel *dst)
{
    unsigned short int i, j, acmRed, acmGreen, acmBlue;
    int halfDim = dim >> 1;
    pixel *dstP, *srcP;
    
    for(i = 0; i < halfDim; ++i)
    {
        for(j = 0; j < halfDim; j+=8) 
        {
            dstP = &dst[RIDX(i, j, halfDim)];
            srcP = &src[RIDX((i << 1), (j << 1), dim)];
            ////// j = 0 //////////////////////////////////////////////////////////////////////////////////
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            
            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 1 //////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            
            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 2 ///////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            
            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 3 //////////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            
            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 4 ///////////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 5 ////////////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 6 //////////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

            ////// j = 7 ////////////////////////////////////////////////////////////////////////////////////////////
            ++dstP;
            srcP += 1-dim;
            acmRed = 0;
            acmGreen = 0;
            acmBlue = 0;

            // k = 0
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            // k = 1
            srcP += dim - 1;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;
            ++srcP;
            acmRed += srcP->red;
            acmGreen += srcP->green;
            acmBlue += srcP->blue;

            dstP->red = (acmRed >> 2);
            dstP->green = (acmGreen >> 2);
            dstP->blue = (acmBlue >> 2);

        }
    }
}

/******************************************************************************
 * register_average_pooling_functions - Register all of your different versions
 *     of the average pooling  with the driver by calling the
 *     add_average_pooling_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 ******************************************************************************/

void register_average_pooling_functions() {
    add_average_pooling_function(&naive_average_pooling, naive_average_pooling_descr);
    add_average_pooling_function(&average_pooling, average_pooling_descr);
    /* ... Register additional test functions here */
}