#ifndef RANDOM_SORT
#define RANDOM_SORT

typedef struct {
    int i;
    int j;
} OrderedPair;

/*
 * Randomly sorts an array of ordered pairs in place.
 */
void RandomSort(OrderedPair pairs[], int length);

#endif
