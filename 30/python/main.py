class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        
        def countWords(words: List[str]):
            count = {}
            for word in words:
                if word in count:
                    count[word] += 1
                else:
                    count[word] = 1
            return count

        def compareCount(l, r):
            for word in l:
                if word not in r:
                    return False
                elif r[word] != l[word]:
                    return False
            return True

        def readWords(window, count, size):
            found = []
            for word_idx in range(count):
                start = word_idx * size
                end = start + size
                word = window[start:end]
                found.append(word)
            return found

        def getWindow(string, index, size):
            start = index
            end = start + size
            return string[start:end]

        if not s or not words:
            return []

        concatenations = []

        base_count = countWords(words)
        num_words = len(words)
        word_len = len(words[0])
        window_size = num_words * word_len
        num_windows = len(s) - window_size + 1

        for i in range(num_windows):
            window = getWindow(s, i, window_size)
            words = readWords(window, num_words, word_len)
            count = countWords(words)
            if compareCount(base_count, count):
                concatenations.append(i)

        return concatenations

