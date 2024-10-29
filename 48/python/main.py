from typing import List


class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        """
        each index has a single destination, and each transformation has
        four components. each row will work on [0+i ,m-i). each "move"
        will cycle through the respective indices around the matrix,
        meaning that four movements will happen in each iteration

        m is num cols
        n is num rows

        the outer loop will be 0 < i < n/2
        the inner loop will be i < j < m-i

        the first axis is   x, y
        the second axis is  y, (m-x)
        the third axis is   m-x, n-y
        the fourth axis is  n-y, x
        """

        m = len(matrix[0])
        n = len(matrix)

        s = m - 1

        for y in range(0, n // 2):
            for x in range(y, s - y):
                buffer = matrix[x][y]
                matrix[x][y] = matrix[s - y][x]
                matrix[s - y][x] = matrix[s - x][s - y]
                matrix[s - x][s - y] = matrix[y][s - x]
                matrix[y][s - x] = buffer
