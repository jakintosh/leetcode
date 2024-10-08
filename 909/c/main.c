#include <stdbool.h>
#include <string.h>

int lookup_tile(int** board, int n, int tile) {
    int cap = n - 1;
    int index = tile - 1;
    int column = index % n;
    int row = cap - ( index / n );
    if ((cap-row) % 2) {
        column = cap - column;
    }
    int dest = board[row][column];
    if (dest == -1) {
        return tile;
    } else {
        return dest;
    }
}

int snakesAndLadders(int** board, int boardSize, int* boardColSize) {
    int n = boardSize;
    int end = n * n;
    int turn = 1;
    int next_turn_len = 1;
    int next_turn[end];
    next_turn[0] = 1;
    int next_turn_alt[end];
    bool seen[end];
    memset(seen, 0, sizeof seen);

    int* nt = next_turn;
    int* nt_ = next_turn_alt;

    while (next_turn_len > 0) {
        int nt_len = 0;
        for (int i = 0; i < next_turn_len; i++) {
            int tile = nt[i];
            for (int next = tile + 1; next <= tile + 6; next++) {
                if (next == end) { return turn; }
                if (next > end) { continue; }
                int dest = lookup_tile(board, n, next);
                if (dest == end) { return turn; }
                if (!seen[dest]) {
                    seen[dest] = true;
                    nt_[nt_len++] = dest;
                }
            }
        }

        // swap array pointers
        int* shim = nt;
        nt = nt_;
        nt_ = shim;
        next_turn_len = nt_len;

        turn++;
    }
    return -1;
}
