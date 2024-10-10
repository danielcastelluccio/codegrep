#include <stdio.h>
#include "string.h"

#include <tree_sitter/api.h>

#include "action.h"
#include "parser.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: codegrep [LANGUAGE] [FILES...]\n");
    }

    char *language = argv[1];
    char **files = argv + 2;
    int file_count = argc - 2;

    for (int i = 0; i < file_count; i++) {
        ParseResult parse_result = parse(language, files[i]);
        if (parse_result.tree == NULL) {
            printf("Failed to parse file: %s\n", files[i]);
        }

        if (!print_functions(language, parse_result)) {
            printf("Language '%s' not supported\n", language);
        }
    }
}
