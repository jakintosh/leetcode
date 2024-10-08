#include <limits.h>

typedef struct {
    int size;
    int count;
    int* array;
} Heap;

void siftUp(Heap* heap, int index) {
    while (index > 0) {
        int parent_index = (index-1)/2;
        int parent = heap->array[parent_index];
        int child = heap->array[index];
        if (parent < child) break;

        heap->array[index] = parent;
        heap->array[parent_index] = child;
        index = parent_index;
    }
}

void siftDown(Heap* heap, int index) {
    int size = heap->size;
    int count = heap->count;
    for (int child_index = index * 2 + 1; child_index < size; child_index = index * 2 + 1) {
        int child = heap->array[child_index];
        if (count > child_index + 1 && heap->array[child_index + 1] < child) {
            child = heap->array[++child_index];
        }

        int parent = heap->array[index];
        if (parent <= child) break;

        heap->array[index] = child;
        heap->array[child_index] = parent;
        index = child_index;
    }
}

void insert(Heap* heap, int num) {
    int end = heap->count;
    if (end < heap->size) {
        heap->array[end] = num;
        siftUp(heap, end);
        heap->count++;
    } else if (heap->array[0] < num) {
        heap->array[0] = num;
        siftDown(heap, 0);
    }
}

int findKthLargest(int* nums, int numsSize, int k) {

    if (numsSize == 1) { 
        return nums[0];
    }

    if (k == 1) {
        int largest = INT_MIN;
        for (int i = 0; i < numsSize; i++) largest = nums[i] > largest ? nums[i] : largest;
        return largest;
    }

    int array[k];
    Heap seen = { .size = k, .count = 0, .array = array };
    for (int i = 0; i < numsSize; i++) insert(&seen, nums[i]);

    return array[0];
}
