void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int index = m + n - 1;
    int index1 = m - 1;
    int index2 = n -1;
    while (index1 >= 0 || index2 >= 0) {
        if (index1 < 0) {
            nums1[index] = nums2[index2--];
        } else if (index2 < 0) {
            return;
        } else {
            int elem1 = nums1[index1];
            int elem2 = nums2[index2];
            if (elem1 > elem2) {
                nums1[index] = elem1;
                index1--;
            } else {
                nums1[index] = elem2;
                index2--;
            }
        }
        index--;
    }
}
