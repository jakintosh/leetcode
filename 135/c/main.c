#include <stdbool.h>

int candy(int* ratings, int ratingsSize) {

    int accumulator = 0;
    int surplus[ratingsSize];
    for (int i = 0; i < ratingsSize; i++) {
        if (i > 0) {
            bool biggerThanPrev = ratings[i] > ratings[i-1];
            accumulator = (biggerThanPrev) ? accumulator + 1 : 0;
        }
        surplus[i] = accumulator;
    }

    accumulator = 0;
    int candy = ratingsSize;
    for (int i = ratingsSize - 1; i >= 0; i--) {
        if (i < ratingsSize - 1) {
            bool biggerThanNext = ratings[i] > ratings[i+1];
            accumulator = (biggerThanNext) ? accumulator + 1 : 0;
        }
        candy += (surplus[i] > accumulator) ? surplus[i] : accumulator;
    }

    return candy;
}
