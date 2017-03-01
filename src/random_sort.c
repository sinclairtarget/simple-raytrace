#include <time.h>
#include <stdlib.h>

#include "random_sort.h"

static int seeded = 0;

void RandomSort(OrderedPair pairs[], int length)
{
    if (seeded == 0) {
        srand(time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < length; i++) {
        int j = rand() % length;
        OrderedPair temp = pairs[j];
        pairs[j] = pairs[i];
        pairs[i] = temp;
    }
}
