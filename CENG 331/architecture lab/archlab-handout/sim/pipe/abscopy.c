#include <stdio.h>

typedef long word_t;

word_t src[8], dst[8];

/* $begin abscopy */
/*
 * abscopy - copy the absolute values of elements contained in src to dst array, 
 * return the sum of copied (absolute) values.
 */
word_t abscopy(word_t *src, word_t *dst, word_t n)
{
    word_t sum = 0;
    word_t val;
    word_t absval;

    while (n > 0) {
        val = *src++;
        absval = val > 0 ? val : -val;
        sum += absval;
        *dst++ = absval;
        n--;
    }
    return sum;
}
/* $end abscopy */

int main()
{
    word_t i, count;

    for (i = 0; i < 8; i++)
        src[i] = (i + 1) * (i % 2 ? -1 : 1);
    count = abscopy(src, dst, 8);
    printf ("sum=%ld\n", count);
    for (i = 0; i < 8; i++)
        printf("%ld ", dst[i]);
    putchar('\n');
    return 0;
}



