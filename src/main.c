#include <stdio.h>
#include "string.h"

#include <tree_sitter/api.h>

#include "parser.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: codegrep [LANGUAGE] [FILES...]\n");
    }

    char *parser_name = argv[1];
    char **files = argv + 2;
    int file_count = argc - 2;

    for (int i = 0; i < file_count; i++) {
        ParseResult parse_result = parse_file(parser_name, files[i]);
        if (parse_result.tree == NULL) {
            printf("Failed to parse file: %s\n", files[i]);
        }

        TSNode root = ts_tree_root_node(parse_result.tree);
        size_t root_child_count = ts_node_child_count(root);
        for (size_t j = 0; j < root_child_count; j++) {
            TSNode declaration = ts_node_child(root, j);
            if (strcmp(ts_node_type(declaration), "function_definition") == 0) {
                TSNode declarator = ts_node_child_by_field_name(declaration, "declarator", 10);
                TSNode name = ts_node_child_by_field_name(declarator, "declarator", 10);

                size_t name_start = ts_node_start_byte(name);
                size_t name_end = ts_node_end_byte(name);
                size_t name_size = name_end - name_start;

                char *name_reallocated = malloc(name_size + 1);
                if (name_reallocated == NULL) {
                    printf("Failed to parse file: %s\n", files[i]);
                }

                name_reallocated[name_size] = '\0';
                memcpy(name_reallocated, parse_result.source + name_start, name_size);

                printf("%s\n", name_reallocated);
            }
        }
    }
}
