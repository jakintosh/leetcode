void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int s = matrixSize - 1;
    for (int y = 0; y < matrixSize / 2; y++) {
        for (int x = y; x < s - y; x++) {
            int temp = matrix[x][y];
            matrix[x][y] = matrix[s-y][x];
            matrix[s-y][x] = matrix[s-x][s-y];
            matrix[s-x][s-y] = matrix[y][s-x];
            matrix[y][s-x] = temp;
        }
    }
}
