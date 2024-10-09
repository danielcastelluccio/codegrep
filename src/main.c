#include <stdio.h>
#include "string.h"

#include <tree_sitter/api.h>

#include "languages/c.h"
#include "parser.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: codegrep [LANGUAGE] [FILES...]\n");
    }

    char *language = argv[1];
    char **files = argv + 2;
    int file_count = argc - 2;

    for (int i = 0; i < file_count; i++) {
        ParseResult parse_result = parse_file(language, files[i]);
        if (parse_result.tree == NULL) {
            printf("Failed to parse file: %s\n", files[i]);
        }

        if (strcmp(language, "c") == 0) {
            if (!print_functions_c(parse_result)) {
                printf("Failed to parse file: %s\n", files[i]);
            }
        } else {
            printf("Language '%s' not supported\n", language);
        }
    }
}
