#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a token in LZ77
struct Token {
    int offset;
    int length;
    char nextChar;
};

// Function to perform LZ77 compression
void lz77_compress(const char *input, int windowSize, struct Token **compressedData, int *tokenCount);

// Function to perform LZ77 decompression
void lz77_decompress(const struct Token *tokens, int tokenCount);

int main() {
    // Example usage
    const char *input = "abababababab";
    int windowSize = 4;

    printf("Original string: %s\n", input);

    // Perform compression
    struct Token *compressedData;
    int tokenCount;
    lz77_compress(input, windowSize, &compressedData, &tokenCount);

    // Print the compressed data
    printf("Compressed data: ");
    for (int i = 0; i < tokenCount; ++i) {
        printf("<%d, %d, %c>", compressedData[i].offset, compressedData[i].length, compressedData[i].nextChar);
    }
    printf("\n");

    // Perform decompression using the compressed data
    lz77_decompress(compressedData, tokenCount);

    // Free the allocated memory
    free(compressedData);

    return 0;
}

void lz77_compress(const char *input, int windowSize, struct Token **compressedData, int *tokenCount) {
    int inputLength = strlen(input);
    *compressedData = (struct Token *)malloc(inputLength * sizeof(struct Token));
    *tokenCount = 0;

    int i = 0;
    while (i < inputLength) {
        int maxLength = 0;
        int maxOffset = 0;

        // Search for the longest match in the sliding window
        for (int j = i - windowSize; j < i; ++j) {
            int k = i;
            int len = 0;

            // Calculate the length of the match
            while (j + len < i && input[j + len] == input[k]) {
                len++;
                k++;
            }

            // Update the maximum match if needed
            if (len > maxLength) {
                maxLength = len;
                maxOffset = i - j - 1;
            }
        }

        // Add the token to the compressed data
        (*compressedData)[*tokenCount].offset = maxOffset;
        (*compressedData)[*tokenCount].length = maxLength;

        // Include the next character after the matched substring
        (*compressedData)[*tokenCount].nextChar = input[i + maxLength];

        // Move the input index
        i += (maxLength > 0) ? maxLength : 1;
        (*tokenCount)++;
    }
}

void lz77_decompress(const struct Token *tokens, int tokenCount) {
    // Allocate memory for the decompressed string
    char *output = (char *)malloc(tokenCount * sizeof(char) * 1000);
    int outputIndex = 0;

    for (int i = 0; i < tokenCount; ++i) {
        // Copy the repeated substring from the output
        for (int j = 0; j < tokens[i].length; ++j) {
            output[outputIndex] = output[outputIndex - tokens[i].offset + j];
            outputIndex++;
        }

        // Add the next character after the repeated substring
        output[outputIndex++] = tokens[i].nextChar;
    }

    // Null-terminate the output string
    output[outputIndex] = '\0';

    // Print the decompressed string
    printf("Decompressed string: %s\n", output);

    // Free the allocated memory
    free(output);
}

