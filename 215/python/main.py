class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        seen = Heap(k)
        for num in nums:
            seen.insert(num)
        return seen.top()

class Heap:
    def __init__(self, size: int):
        self.size = size
        self.count = 0
        self.array = [None] * size

    def top(self) -> int:
        return self.array[0]

    def insert(self, num: int):
        if self.count < self.size:
            self.array[self.count] = num
            self.sift_up(self.count)
            self.count += 1
        else:
            if self.array[0] < num:
                self.array[0] = num
                self.sift_down(0)

    def sift_up(self, index: int):
        while index > 0:
            swap_index = (index-1)//2
            parent = self.array[swap_index]
            child = self.array[index]
            if parent < child:
                break

            self.array[index] = parent
            self.array[swap_index] = child
            index = swap_index
            
    def sift_down(self, index: int):
        while index*2+1 < self.size:
            child_index = (index*2)+1
            child = self.array[child_index]
            if self.count > (child_index + 1) and self.array[child_index+1] < child:
                child_index += 1
                child = self.array[child_index]

            parent = self.array[index]
            if parent > child:
                self.array[index] = child
                self.array[child_index] = parent
                index = child_index
            else:
                break
