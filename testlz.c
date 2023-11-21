#include <ft/string.h>
#include <ft/mem.h>
#include <ft/print.h>  // Assuming ft_asprintf is declared in this header
#include <stdlib.h>

typedef struct {
    int offset;
    int length;
    char next;
} LZ77Token;

static size_t estimate_compressed_size(char *str);
static void add_token_to_compressed_str(char **compressed_str, size_t *compressed_index, LZ77Token token);
static LZ77Token find_longest_match(char *str, int i);

char *mt_compress_lz77(char *str) {
    size_t str_len = ft_strlen(str);
    size_t compressed_size = estimate_compressed_size(str);

    char *compressed_str = NULL;
    if (ft_asprintf(&compressed_str, "%s", "") < 0) {
        return NULL;
    }

    size_t i = 0;
    size_t compressed_index = 0;

    while (i < str_len) {
        LZ77Token token = find_longest_match(str, i);
        add_token_to_compressed_str(&compressed_str, &compressed_index, token);
        i += token.length - 1; // Move to the next character after the matched substring
    }

    return compressed_str;
}

static size_t estimate_compressed_size(char *str) {
    size_t str_len = ft_strlen(str);
    size_t compressed_size = 0;

    size_t i = 0;
    while (i < str_len) {
        LZ77Token token = find_longest_match(str, i);
        compressed_size += (token.length > 0) ? 5 : 1; // 5 for <offset,length> or 1 for <0,0,character>
        i += token.length;
    }

    return compressed_size;
}

static void add_token_to_compressed_str(char **compressed_str, size_t *compressed_index, LZ77Token token) {
    if (token.length > 0) {
        // Add <offset, length> to compressed string
        ft_asprintf(compressed_str, "%s<%d,%d>", *compressed_str, token.offset, token.length);
    } else {
        // Add <0,0,character> to compressed string
        ft_asprintf(compressed_str, "%s%c", *compressed_str, token.next);
    }
}

static LZ77Token find_longest_match(char *str, int i) {
    LZ77Token token = {0, 0, str[i]};

    int offset = 0;
    int str_len = ft_strlen(str);

    if (i == 0) {
        // Handle the case when i is 0 separately
        while (offset < i && i + offset < str_len) {
            int length = 0;
            while (str[i + length] == str[offset + length] && str[i + length] != '\0') {
                ++length;
            }

            if (length > token.length) {
                token.offset = offset;
                token.length = length;
                token.next = str[i + length];
            }

            ++offset;
        }
    } else {
        // Handle the general case
        while (i + offset < str_len) {
            int length = 0;
            while (str[i + length] == str[offset + length] && str[i + length] != '\0') {
                ++length;
            }

            if (length > token.length) {
                token.offset = offset;
                token.length = length;
                token.next = str[i + length];
            }

            ++offset;
        }
    }

    return token;
}


static size_t estimate_decompressed_size(char *str);
static void copy_substring(char *decompressed_str, size_t *decompressed_index, int offset, int length);

char *mt_decompress_lz77(char *str) {
    size_t decompressed_size = estimate_decompressed_size(str);
    char *decompressed_str = ft_calloc(decompressed_size + 1, sizeof(char));

    if (!decompressed_str) {
        return NULL;
    }

    size_t i = 0;
    size_t decompressed_index = 0;

    while (str[i] != '\0') {
        if (str[i] == '<') {
            i++;
            int offset = atoi(&str[i]);
            while (str[i] != ',') {
                i++;
            }
            i++;
            int length = atoi(&str[i]);
            while (str[i] != '>') {
                i++;
            }
            i++;

            copy_substring(decompressed_str, &decompressed_index, offset, length);
        } else {
            decompressed_str[decompressed_index++] = str[i++];
        }
    }

    return decompressed_str;
}

static size_t estimate_decompressed_size(char *str) {
    size_t i = 0;
    size_t len = 0;

    while (str[i] != '\0') {
        if (str[i] == '<') {
            i++;
            while (str[i] != '>') {
                i++;
            }
            i++;
        } else {
            len++;
            i++;
        }
    }

    return len;
}

static void copy_substring(char *decompressed_str, size_t *decompressed_index, int offset, int length) {
    for (int j = 0; j < length; ++j) {
        decompressed_str[(*decompressed_index)++] = decompressed_str[*decompressed_index - offset + j];
    }
}

int main(void) {
    // Example usage
    char input[] = "Then God said, “Let the land produce vegetation: seed-bearing plants and trees on the land that bear fruit with seed in it, according to their various kinds.” And it was so. 12 The land produced vegetation: plants bearing seed according to their kinds and trees bearing fruit with seed in it according to their kinds. And God saw that it was good. 13 And there was evening, and there was morning—the third day.";
    char *compressed = mt_compress_lz77(input);
    char *decompressed = mt_decompress_lz77(compressed);

    // Display results
    ft_putstr("Original: ");
    ft_putstr(input);
    ft_putstr("\nCompressed: ");
    ft_putstr(compressed);
    ft_putstr("\nDecompressed: ");
    ft_putstr(decompressed);
    ft_putstr("\n");

    // Cleanup
    free(compressed);
    free(decompressed);

    return 0;
}

