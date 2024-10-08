class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:    
        # "contains"
        # r      s----------e
        # i      |e-> && <-s|

        # check early exits
        count = len(intervals)
        if count < 2:
            return intervals
            
        # sort by interval start
        def arr_sort(arr):
            return arr[0]
        intervals.sort(key=arr_sort)

        result = []
        lowest = intervals[0][0]
        highest = intervals[0][1]
        for index in range(count - 1):
            this = intervals[index]
            next = intervals[index + 1]
            if highest < next[0]:
                result.append([lowest, highest])
                lowest = next[0]
                highest = next[1]
            else:
                highest = max(highest, next[1])
            
        result.append([lowest, highest])

        return result
