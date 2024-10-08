#include <stdlib.h>

void append(int** result, int* size, int lowest, int highest) {
    int* element = (int*) malloc(sizeof(int[2]));
    element[0] = lowest;
    element[1] = highest;
    result[(*size)++] = element;
}

int compare(const void* a, const void* b) {
    int** left = a;
    int** right = b;
    return (*left)[0] - (*right)[0];
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int** result = (int**) malloc(sizeof(int*) * intervalsSize);

    if (intervalsSize == 0) {
        return result;
    }
    if (intervalsSize == 1) {
        append(result, returnSize, intervals[0][0], intervals[0][1]);
        *returnColumnSizes = (int*) malloc(sizeof(int) * *returnSize);
        for (int i = 0; i < *returnSize; i++) {
            (*returnColumnSizes)[i] = 2;
        }
        return result;
    }

    // sort the array
    qsort(intervals, intervalsSize, sizeof(int[2]), compare);

    int lowest = intervals[0][0];
    int highest = intervals[0][1];
    for (int i = 0; i < intervalsSize - 1; i++) {
        int* this = intervals[i];
        int* next = intervals[i+1];
        if (highest < next[0]) {
            append(result, returnSize, lowest, highest);
            lowest = next[0];
            highest = next[1];
        } else {
            highest = max(highest, next[1]);
        }
    }
    append(result, returnSize, lowest, highest);
    *returnColumnSizes = (int*) malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return result;
}
