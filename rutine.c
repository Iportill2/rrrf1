#include "rutine.h"
#include <limits.h>
#include <stdlib.h>

void *rutine(void *arg)
{
    t_args *a = (t_args*)arg;
    int i = 0;

    while (i < a->amount) 
    {
        int n = rand();                
        n ^= rand() << 16;             
        if (n % 2 == 0) 
            n = -n;       

        if (n >= 0)
            list_push(a->pos, n);
        else
            list_push(a->neg, n);
        i++;
    }
    return NULL;
}

