#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int containsWord(char** words, int wordsSize, char* word) {
    for (int i = 0; i < wordsSize; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int containsSubstring(char** words, int wordsSize, char* s, int offset, int len) {
    for (int i = 0; i < wordsSize; i++) {
        bool match = true;
        for (int j = 0; j < len; j++) {
            if (words[i][j] != s[offset + j]) {
                match = false;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}

int countWords(char** input, int inputSize, char** words, int* count) {
    int len = 0;
    for (int i = 0; i < inputSize; i++) {
        char* inputWord = input[i];
        int index = containsWord(words, len, inputWord);
        if (index >= 0)
            count[index]++;
        else {
            words[len] = inputWord;
            count[len] = 1;
            len++;
        }
    }
    return len;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {

    int num_words = wordsSize;
    int len_s = strlen(s);
    int word_len = strlen(words[0]);
    int window_size = num_words * word_len;
    int num_windows = len_s - window_size + 1;

    if (num_windows < 1) {
        *returnSize = 0;
        return (int*) malloc(sizeof(int) * 1);
    }

    char** count_words = (char**) malloc(sizeof(char*) * num_words);
    int* count_count = (int*) malloc(sizeof(int) * num_words);
    int count_len = countWords(words, num_words, count_words, count_count);
    int found[count_len];

    int num_concatenations = 0;
    int* concatenations = (int*) malloc(sizeof(int) * num_windows);

    for (int i = 0; i < num_windows; i++) {
        memset(found, 0, sizeof found);
        bool ok = true;
        for (int j = 0; j < num_words; j++) {
            int offset = i + (j * word_len);
            int index = containsSubstring(count_words, count_len, s, offset, word_len);
            if (index == -1) {
                ok = false;
                break;
            }
            else {
                found[index] += 1;
                if (found[index] > count_count[index]) {
                    ok = false;
                    break;
                }
            }
        }
        if (!ok) {
            continue;
        }

        for (int j = 0; j < count_len; j++)
            if (count_count[j] != found[j])
                continue;
        concatenations[num_concatenations++] = i;
    }

    free(count_words);
    free(count_count);

    *returnSize = num_concatenations;
    return concatenations;
}

