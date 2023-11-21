# lz77 compression/decompression reimplementation

import sys
import os
import math
import time

# lz77 compression/decompression reimplementation

class LZ77Token:
    def __init__(self, offset, length, char):
        self.offset = offset
        self.length = length
        self.char = char

    def __str__(self):
        return "<%d, %d, %s>" % (self.offset, self.length, self.char)

    def __repr__(self):
        return str(self)


def lz77_compress(data: str, window_size: int) -> list[LZ77Token]:
    """
    Compresses the data using the given window size.
    """
    window_start = 0
    window_end = 0
    tokens = []

    while window_end < len(data):
        # Find the longest match
        match_offset = 0
        match_length = 0
        for i in range(window_start, window_end):
            length = 0
            while data[i + length] == data[window_end + length]:
                length += 1
                if window_end + length >= len(data):
                    break
                if length > match_length:
                    match_offset = i
                    match_length = length

        # Add the token to the list
        if match_length > 0:
            tokens.append(LZ77Token(match_offset, match_length, data[window_end + match_length]))
            window_end += match_length + 1
            window_start = max(0, window_end - window_size)
        else:
            tokens.append(LZ77Token(0, 0, data[window_end]))
            window_end += 1
            window_start = max(0, window_end - window_size)

    return tokens


def lz77_decompress(tokens: list) -> str:
    """
    Decompresses the tokens into the original data.
    """
    data = ""
    for token in tokens:
        if token.length == 0:
            data += token.char
        else:
            start = len(data) - token.offset
            for i in range(token.length):
                # IndexError: string index out of range

                # data += data[start + i]
                if start + i < len(data):
                    data += data[start + i]
                else:
                    data += data[start + i - len(data)]
            data += token.char
    return data

if __name__ == "__main__":
    string = "abracadabra"
    print(string)
    tokens = lz77_compress(string, 4)
    print(tokens)
    print(lz77_decompress(tokens))
    print("match" if string == lz77_decompress(tokens) else "no match")
