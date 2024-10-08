#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
    int count;
    bool isEnd;
    bool deleted;
    struct node_* node[26];
} TrieNode;

TrieNode* initNode() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++) {
        node->node[i] = NULL;
    }
    node->count = 0;
    node->deleted = false;
    node->isEnd = false;
    return node;
}

void freeNode(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        TrieNode* next = node->node[i];
        if (next) freeNode(next);
    }
    free(node);
}

/*
    Recursively set all children from 'node' as deleted, and
    reduce all counts respectively.
*/
void deleteNode(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        TrieNode* next = node->node[i];
        if (next) {
            deleteNode(next);
            node->count -= 1;
        }
    }
    node->deleted = true;
}

/*
    Add new node (or undelete it) for char 'c', updating
    count as needed, and returning the node for that char.
*/
TrieNode* addChar(TrieNode* node, char c) {
    int index = c - 'a';
    TrieNode* next = node->node[index];
    if (next == NULL) {
        next = node->node[index] = initNode();
        node->count += 1;
    } else if (next->deleted) {
        next->deleted = false;
        node->count += 1;
    }
    return next;
}

/*
    Follow link to 'c' from 'node', returning the next node,
    or NULL if not valid.
*/
TrieNode* followChar(TrieNode* node, char c) {
    int index = c - 'a';
    TrieNode* next = node->node[index];
    if (next != NULL && next->deleted)
        return NULL;
    return next;
}

/*
    Delete the node at 'c' if it exists, decrement count
    as needed.
*/
void removeChar(TrieNode* node, char c) {
    int index = c - 'a';
    TrieNode* next = node->node[index];
    if (next) {
        deleteNode(next);
        node->count -= 1;
    }
}

/*
    Add word starting at the given 'node'
*/
void addWord(TrieNode* node, char* word, int len) {
    for (int i = 0; i < len; i++) {
        node = addChar(node, word[i]);
    }
    node->isEnd = true;
}

/*
    Remove a word from the trie
*/
bool removeWord(TrieNode* trie, char* word, int len) {
    if (len == 0)
        return false;

    int top = 0;
    TrieNode* stack[11] = { NULL };
    stack[0] = trie;

    // walk to the end of the word
    while (top < len) {
        TrieNode* node = followChar(stack[top], word[top]);
        stack[++top] = node;
        if (stack[top] == NULL) {
            return false; // word wasn't present
        }
    }

    // remove the end flag
    if (!stack[top]->isEnd) {
        return false; // word wasn't present
    }
    stack[top]->isEnd = false;

    // if there's nothing beyond (count == 0),
    // unwind stack to where the word branches (count > 1)
    if (stack[top]->count == 0) {
        while (top > 0) {
            top--;
            if (stack[top]->count > 1) {
                removeChar(stack[top], word[top]);
                break;
            }
        }
    }

    return true;
}

bool hasVisited(int* visited, int visitedSize, int cellNum) {
    for (int i = (visitedSize - 1); i >= 0; i--)
        // check backwards, most likely conflicts are at the top of the stack
        if (visited[i] == cellNum)
            return true;
    
    return false;
}

void checkCell(char** board, int rows, int cols, int row, int col, int* visited, int depth, TrieNode* root, TrieNode* node, char** foundWords, int* returnSize) {

    char c = board[row][col];
    TrieNode* next = followChar(node, c);
    if (next == NULL)
        return;

    if (hasVisited(visited, depth, row * cols + col))
        return;

    // --- not deleted, valid char, have not visited ---

    // mark cell as visited
    visited[depth++] = row * cols + col;

    // check end of a word
    if (next->isEnd) {
        char* word = (char*) malloc(sizeof(char) * (depth + 1));
        for (int i = 0; i < depth; i++) {
            int index = visited[i];
            word[i] = board[index / cols][index % cols];
        }
        word[depth] = '\0';
        foundWords[(*returnSize)++] = word;
        removeWord(root, word, depth);
    }

    if (row > 0) {          // up
        checkCell(board, rows, cols, row - 1, col, visited, depth,
            root, next, foundWords, returnSize);
    }
    if (next->deleted) return;

    if (col + 1 < cols) {   // right
        checkCell(board, rows, cols, row, col + 1, visited, depth,
            root, next, foundWords, returnSize);
    }
    if (next->deleted) return;
    
    if (row + 1 < rows) {   // down
        checkCell(board, rows, cols, row + 1, col, visited, depth,
            root, next, foundWords, returnSize);
    }
    if (next->deleted) return;
    
    if (col > 0) {          // left
        checkCell(board, rows, cols, row, col - 1, visited, depth,
            root, next, foundWords, returnSize);
    }
    if (next->deleted) return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize) {

    int m = boardSize;
    int n = *boardColSize;

    /*
        good trade off because max board cells is 144, but max num of words
        is 30,000 (x 10 char each). Instead of potentially doing 144 * 300,000,
        we pre-filter and do 144 + 300,000, with lots of early exits. 
    */
    // how many of each letter on the board
    int contents[26] = { 0 };
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int index = board[i][j] - 'a';
            contents[index]++;
        }
    }

    // create trie of input, only add possible words
    int wordContents[26] = { 0 };
    int trieSize = 0;
    TrieNode* trie = initNode();
    for (int i = 0; i < wordsSize; i++) {
        memset(wordContents, 0, sizeof(int) * 26);
        char* word = words[i];
        bool legal = true;
        int len;
        for (len = 0; len <= 10; len++) {
            char c = word[len];

            // break early for smaller words
            if (c == '\0') {
                break;
            }

            // break and mark illegal if requires 'c' not on board
            int index = c - 'a';
            wordContents[index]++;
            if (wordContents[index] > contents[index]) {
                legal = false;
                break;
            }
        }
        if (legal) {
            addWord(trie, word, len);
            trieSize++;
        }
    }

    // check each cell for word (recursive)
    int visited[10];
    *returnSize = 0;
    char** foundWords = (char**) malloc(sizeof(char*) * trieSize);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            checkCell(board, m, n, i, j, visited, 0, trie, trie, foundWords, returnSize);
            if (trie->deleted) break; // found all the words
        }
    }

    // cleanup data
    freeNode(trie);

    return foundWords;
}
