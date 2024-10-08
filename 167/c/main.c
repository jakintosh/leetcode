#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {

    *returnSize = 0;
    int* result = malloc(sizeof(int) * 2);

    int i = 0;                  // front index
    int j = numbersSize - 1;    // rear index
    while (i < j) {
        int sum = numbers[i] + numbers[j];
        if (sum == target) {
            // found correct indices
            *returnSize = 2;
            result[0] = i + 1; // +1 because array is 1-indexed
            result[1] = j + 1; // same
            return result;
        } else if (sum < target) {
            // if our sum is too small, increment the smaller number
            i++;
        } else {
            // if sum is too big, decrement the larger number
            j--;
        }
    }

    // we never found a matching pair
    exit(1);
}
