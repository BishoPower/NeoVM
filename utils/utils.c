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

#pragma GCC diagnostic pop