class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        
        # we are checking pairs, if the smaller one is in nums1, its good, if its in nums 2
        # we need to "save" the val in nums1, move val from nums2 into nums1

        index = m + n - 1
        index1 = m - 1
        index2 = n - 1
        while index1 >= 0 or index2 >= 0:
            elem: int
            if index1 < 0:
                elem = nums2[index2]
                index2 -= 1
            elif index2 < 0:
                # if nums2 is empty, the rest of nums1 is sorted
                return
            else:
                elem1 = nums1[index1]
                elem2 = nums2[index2]
                if elem1 > elem2:\
                    # bias towards emptying nums2 so alg can quit sooner
                    elem = elem1
                    index1 -= 1
                else:
                    elem = elem2
                    index2 -= 1
            
            nums1[index] = elem
            index -= 1
