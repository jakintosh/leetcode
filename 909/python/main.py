class Solution:
    def snakesAndLadders(self, board: List[List[int]]) -> int:
        n = len(board)
        end = n * n
        turn = 1
        seen = [False] * end
        next_turn = [1]
        while len(next_turn) > 0:
            for tile in next_turn[:]:
                next_turn.remove(tile)
                for next in range(tile + 1, tile + 7):
                    if next == end:
                        return turn
                    if next > end:
                        continue
                    dest = lookup_tile(board, n, next)
                    if dest == end:
                        return turn
                    if not seen[dest]:
                        seen[dest] = True
                        next_turn.append(dest)
            turn += 1
        return -1

def lookup_tile(board, n, tile):
    cap = n - 1
    index = tile - 1
    column = index % n
    row = cap - ( index // n )
    if (cap - row) % 2:
        column = cap - column # reverse
    dest = board[row][column]
    if dest != -1:
        return dest
    else:
        return tile

