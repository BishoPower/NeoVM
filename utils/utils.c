#include "utils.h"

void copy(int8 *dst, int8 *src, int16 size)
{
    int8 *d, *s;
    int16 i;

    for (i = size, d = dst, s = src; i; i--, d++, s++)
    {
        *d = *s;
    }

    return;
}

void zero(int8 *dst, int16 size)
{
    int8 *d;
    int16 i;

    for (i = size, d = dst; i; i--, d++)
    {
        *d = 0;
    }

    return;
}

void printhex(int8 *buf, int16 size, int8 delimater)
{
    int8 *p;
    int16 i;

    for (p = buf, i = size; i; i--, p++)
    {
        printf("%.02x", *p);
        if (delimater)
            printf("%c", delimater);
        fflush(stdout);
    }
    printf("\n");

    return;
}

#pragma GCC diagnostic pop